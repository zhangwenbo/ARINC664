#include <op_429_card.h>
#include <untils.h>

#define __DEBUG__

static A429Handle board;

static channel_conf_t g_channel_conf[MAX_CHANNELS] = {
    {1, 17},
    {2, 18},
    {3, 19},
    {4, 20},
    {5, 21},
    {6, 22},
    {7, 23},
    {8, 24},
    {9, 25},
    {10, 26},
    {11, 27},
    {12, 28},
    {13, 29},
    {14, 30},
    {15, 31},
    {16, 32}
};

static channel_state_t inited_channel[MAX_CHANNELS] = {
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
    {0, {0}, {0}, 0, {0}, &construct_channel_state_t, NULL},
};

#ifndef __DEBUG__
static void configure_tx(const A429Handle* const board, uint8_t channel_num, A429Handle* tx) {
    A429Return rc = A429_SUCCESS;

    /* create the transmit channel */
    rc = a429BoardConfigTxChannel(*board, channel_num, A429_CHANNEL_SPEED_LOW, tx, 1);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Failed to configure transmit channel: %s\n", a429UtilsErrorString(rc));
        exit(1);
    }
}
#else
static void configure_tx(const A429Handle* const board, uint8_t channel_num, A429Handle* tx) {
}
#endif

#ifndef __DEBUG__
static void configure_rx(const A429Handle* const board, uint8_t channel_num, A429Handle* rx) {
    A429Return rc = A429_SUCCESS;

    /* create the receive channel */
    rc = a429BoardConfigRxChannel(*board, channel_num, A429_CHANNEL_SPEED_LOW, rx);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Failed to configure receive channel: %s\n", a429UtilsErrorString(rc));
        exit(1);
    }
}
#else
static void configure_rx(const A429Handle* const board, uint8_t channel_num, A429Handle* rx) {
}
#endif

#ifndef __DEBUG__
static void construct_channel_state_t(struct _channel_state_t *this, const A429Handle* const board, OwUInt32 nr, const channel_conf_t* const conf) {
    A429Return rc = A429_SUCCESS;
    
    this->nr = nr;

    configure_tx(board, conf->tx_nr, &this->tx_channel);
    rc = a429BoardStartChannel(*board, conf->tx_nr); /* notice the second param, I'am not true */
    if (rc != A429_SUCCESS) {
        fprintf(stderr, "Failed to start transmit channel %d: %s\n", conf->tx_nr, a429UtilsErrorString(rc));
        exit(1);
    }

    configure_rx(board, conf->rx_nr, &this->rx_channel);
    rc = a429BoardStartChannel(*board, conf->rx_nr); /* notice the second param, I'am not true */
    if (rc != A429_SUCCESS) {
        fprintf(stderr, "Failed to start receive channel %d: %s\n", conf->rx_nr, a429UtilsErrorString(rc));
        exit(1);
    }    
}
#else
static void construct_channel_state_t(struct _channel_state_t *this, const A429Handle* const board, OwUInt32 nr, const channel_conf_t* const conf) {
}
#endif

#ifndef __DEBUG__
static A429Handle init_board(uint64_t aSerialNumber) {
    A429Return rc = A429_SUCCESS;
    A429Handle board = { 0 };
    A429BoardDetails details = { 0 };
    
#if 1
    /* enable debug output */
    a429UtilsSetDebugLevel(A429_DEBUG_ERROR);
#endif

    /* no serial?  grab the 0th board. */
    if (0 == aSerialNumber) {
        rc = a429BoardInitializeByIndex(0, &board);
    } else {
        rc = a429BoardInitializeBySerialNumber(aSerialNumber, &board);
    }

    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Unable to find a board: %s\n", a429UtilsErrorString(rc));
        exit(1);
    }

    /* print a little detail about the board */
    rc = a429BoardGetBoardDetails(board, &details);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Failed to retrieve board details: %s\n", a429UtilsErrorString(rc));
        a429BoardClose(&board);
        exit(1);
    }

    fprintf(stdout, "Found '%s' (serial #%" PRIu64 ")\n", details.model_string, details.serial_number);
    return board;
}
#else
static A429Handle init_board(uint64_t aSerialNumber) {
}
#endif

#ifndef __DEBUG__
static void init_channel_state(const A429Handle *board, const channel_conf_t* const chan_conf, int chan_conf_size) {
    A429Return rc = A429_SUCCESS;

    int i = 0;
    for (; i < chan_conf_size; i++) {
        /* set the expected channel directions */
        rc = a429BoardSetChannelDirection(*board, chan_conf[i].tx_nr, A429_CHANNEL_TX);
        if (A429_SUCCESS != rc) {
            fprintf(stderr, "Failed to set tx channel direction: %s\n", a429UtilsErrorString(rc));
            a429BoardClose(board);
            exit(1);
        }
        
        rc = a429BoardSetChannelDirection(*board, chan_conf[i].rx_nr, A429_CHANNEL_RX);
        if (A429_SUCCESS != rc) {
            fprintf(stderr, "Failed to set rx channel direction: %s\n", a429UtilsErrorString(rc));
            a429BoardClose(board);
            exit(1);
        }
    }

    for (i = 0; i < chan_conf_size; i++) { /* can be merged? */
        (inited_channel[i].constructor)(&inited_channel[i], board, i, &chan_conf[i]);
    }
}
#else
static void init_channel_state(const A429Handle *board, const channel_conf_t* const chan_conf, int chan_conf_size) {
}
#endif

static uint64_t get_serialNumber(void) {
    FILE* fp;  
    char lineBuf[129];  
    char* delim = ":";  //分隔符为：空格  
    int num = 0;    //文件中总的字符串个数  
    int count = 0;  //一行中的字符串个数  
  
    char** dest  = (char**)calloc(2, sizeof(char*));

    int i = 0;
    for (; i < 2; ++i) {
        dest[i] = (char*)calloc(64, sizeof(char));
    }
    char** tmpDest = dest;
    
    if (NULL != (fp = fopen("a664card.txt", "r"))) {
        while(fgets(lineBuf, 128, fp) != NULL) {
            split(lineBuf, delim, tmpDest, &count);  
            num  = num + count;
            tmpDest += count;
        }  
    }  
    fclose(fp);

    return atoi(dest[1]);
}

#ifndef __DEBUG__
void init_429_middleware(void) {
    uint64_t aSerialNumber = get_serialNumber();
    
    board = init_board(aSerialNumber);
    init_channel_state(&board, g_channel_conf, MAX_CHANNELS);
}
#else
void init_429_middleware(void) {
}
#endif

#ifndef __DEBUG__
static send_to_429_card(const channel_state_t* const channel_state) {
    A429Return rc = A429_SUCCESS;
    uint32_t transmitWords = 1;
    
    rc = a429TxSendAsynchronousData(channel_state->tx_channel, &channel_state->tx_data, transmitWords, &transmitWords);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Failed to transmit data: %s\n", a429UtilsErrorString(rc));
        exit(1);
    }
}
#else
static send_to_429_card(const channel_state_t* const channel_state) {
}
#endif

#ifndef __DEBUG__
void send_to_429(void *channel_nr, void *word) {
    channel_data_t chan_stat;
    chan_stat.channel_nr = *(OwUInt8*)channel_nr;
    chan_stat.word = *(OwUInt32*)word;
    inited_channel[chan_stat.channel_nr - 1].tx_data = chan_stat.word;
    send_to_429_card(&inited_channel[chan_stat.channel_nr - 1]);
   // fprintf(stdout, "Transmit from channel %d, data is %x\n", chan_stat.channel_nr, inited_channel[chan_stat.channel_nr - 1].tx_data);
}
#else
void send_to_429(void *channel_nr, void *word) {
}
#endif

#ifndef __DEBUG__
void recv_from_429(void *channels) {
    recv_from_429_card(channels);
}
#else
void recv_from_429(void *channels) {
}
#endif

#ifndef __DEBUG__
static recv_from_429_card(void *channels) {
    A429Return rc = A429_SUCCESS;
    uint32_t receiveWords = 0;

    int i = 0;
    for (; i < MAX_CHANNELS; i++) {
        rc = a429RxRead(inited_channel[i].rx_channel, &inited_channel[i].rx.rx_data, sizeof(inited_channel[i].rx.rx_data), &receiveWords);
        if (A429_SUCCESS != rc) {
            fprintf(stderr, "Failed to recieve data: %s\n", a429UtilsErrorString(rc));
        } else {
            if (receiveWords != 0) {
                inited_channel[i].rx.is_vaild = 1;
              //  fprintf(stdout, "driver recv  %d, data is %x\n", i + 1, inited_channel[i].rx.rx_data);
            } else {
                inited_channel[i].rx.is_vaild = 0;
            }
        }

        memmove(channels + i * sizeof(Rx_Data), &inited_channel[i].rx, sizeof(Rx_Data));
    }
}
#else
static recv_from_429_card(void *channels) {
    
}
#endif

#ifndef __DEBUG__
void close_429_card(void) {
    A429Return rc = A429_SUCCESS;

    rc = a429BoardStopBoard(board);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Stop 429 card failed, %s\n", a429UtilsErrorString(rc));
        exit(1);
    }

    rc = a429BoardClose(&board);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Close 429 card failed, %s\n", a429UtilsErrorString(rc));
        exit(1);
    }
}
#else
void close_429_card(void) {
}
#endif
