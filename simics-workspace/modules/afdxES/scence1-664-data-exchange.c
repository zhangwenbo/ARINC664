#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hwa_aes_klib.h"

static int cardnum;

/*
int get_a664_cardnum(void) {
    return cardnum;
}
*/
static unsigned char inject_packet_header[16] = {
	0x14,/* res 1: enable CRC and IP checksum */
    0x00,/*res  2*/
    0x00, 0x00, /* 这个需要修改 */
    0x03, /*5 net*/
    0x00, 0x00, 0x0, /*time 6-8，计算时间间隔 */
    0x18, /*res, 9*/
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*10-16 RES*/    
};

static int flag = 0;

#define MAX_RECV_BUFFER_LENGTH    1024 * 1024

static unsigned char recv_buf[MAX_RECV_BUFFER_LENGTH];

typedef enum {
    READY_TO_RECV_FRAME = 1,
    BEGIN_TO_HANDLE_FRAME
} RECV_STATE;

static HwaPackInfo packInfo = {0};
static unsigned char *curpos = NULL;
static int len = -1;

void init_664_card(void) {
	int card_count;

    card_count = hwa_aes_find_card();
	if (card_count <= 0) {
		printf("No Card : %d\n", card_count);
		hwa_aes_free_card();
		getchar();
        exit(1);
	}

    cardnum = 0;                /* 可以从文件中获得 */
    hwa_aes_set_mode(cardnum, mode_inject); /* 设置成故障注入模式 */

	printf("Opening Card...\n");
	if (hwa_aes_open_card(cardnum) != HWA_AES_OK) {
		printf("open failed\n");	
		getchar();
        exit(1);
	}
	printf ("open card OK!\n");

    hwa_aes_inject_start_send(cardnum, 100); /* 第二个参数是BAG */

    flag = READY_TO_RECV_FRAME;    
}


void a664module_send_to_a664card(void *_buf, int len) {
    /* 1、准备故障注入头 */
    /* 2、准备一个大的buffer，然后将头拷贝到buffer中 */
    unsigned char *buf = (unsigned char*)_buf;
    unsigned char packet[16+1518] = {0};

    inject_packet_header[3] = len;
    
    /* 3、将传入的有效载荷加载进来 */
    memcpy(packet, inject_packet_header, sizeof(inject_packet_header));
    memcpy(packet + 16, buf, len);
    
    /* 4、计算发送包的长度 */
    int packet_len = len + sizeof(inject_packet_header);
    int portID = 0;

    int ret = hwa_aes_send(cardnum, portID, packet, packet_len);

    if (ret < 0) {
        printf("hwa_aes_send failed, error code: %d\n", ret);
        exit(1);
    }
}

int a664module_recv_from_a664card(void *_buf) {
    unsigned char **buf = (unsigned char **)_buf;
    
    if (flag == READY_TO_RECV_FRAME) {
        HwaPktSrc info;
        hwa_aes_monitor_start_recv(cardnum);
        len = hwa_aes_recv_ex(cardnum, 0, recv_buf, 8388608, 200, &info);
        if (len > 0) {
            flag = BEGIN_TO_HANDLE_FRAME;
            return a664module_recv_from_a664card(buf);
        } else {
            return -1;
        }
    } else if (flag == BEGIN_TO_HANDLE_FRAME) {
        if (hwa_aes_packet_find_next(recv_buf,
                                     len,
                                     buf,
                                     &packInfo,
                                     &curpos) != HWA_AES_FINISHED_FIND) {
            return packInfo.packet_len;
        } else {
            memset(&packInfo, 0, sizeof(HwaPktSrc));
            //memset(recv_buf, 0, MAX_RECV_BUFFER_LENGTH);
            curpos = NULL;
            len = -1;
            flag = READY_TO_RECV_FRAME;
            return a664module_recv_from_a664card(buf);            
        }        
    }

    return -1;
}
