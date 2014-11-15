#include <stdio.h>
#include <string.h>

const char *infilename = "rframe_image.bin";
const char *outfilename = "parsed_recv_frame.txt";

typedef enum {
    DESTINATION_ADDRESS_SIZE = 6,
    SOURCE_ADDRESS_SIZE = 6,
    IPV4_SIZE = 2,
    IP_STRUCTURE_SIZE = 20,
    UDP_STRUCTURE_SIZE = 8,
    MAX_PAYLOAD_SIZE = 1418,
    SN_SIZE = 1,
    CRC_SIZE = 4
} DOMAIN_SIZE;

typedef struct {
    int frame_size;
    char destination_address[DESTINATION_ADDRESS_SIZE + 1];
    char source_address[SOURCE_ADDRESS_SIZE + 1];
    char ipv4[IPV4_SIZE + 1];
    char ip_structure[IP_STRUCTURE_SIZE + 1];
    char udp_structure[UDP_STRUCTURE_SIZE + 1];
    char afdxES_payload[MAX_PAYLOAD_SIZE];
    char sn[SN_SIZE + 1];
    int crc;
} Frame_Package;

int main(int argc, char *argv[]) {
    FILE *in = fopen(infilename, "rb");
    FILE *out = fopen(outfilename, "w");

    int i = 0;
    while (!feof(in)) {
        fprintf(stdout, "eheh!\n");
        Frame_Package frame;
        memset(&frame, 0, sizeof(Frame_Package));
        for (i = 0; i < sizeof(int); ++i) {
            fread((char*)&frame.frame_size + i, sizeof(char), 1, in);
        }

        for (i = 0; i < DESTINATION_ADDRESS_SIZE; ++i) {
            fread((char*)&frame.destination_address + i, sizeof(char), 1, in);
        }

        for (i = 0; i < SOURCE_ADDRESS_SIZE; ++i) {
            fread(frame.source_address + i, sizeof(char), 1, in);
        }

        for (i = 0; i < IPV4_SIZE; ++i) {
            fread(frame.ipv4, sizeof(char), 1, in);
        }

        for (i = 0; i < IP_STRUCTURE_SIZE; ++i) {
            fread(frame.ip_structure + i, sizeof(char), 1, in);
        }

        for (i = 0; i < UDP_STRUCTURE_SIZE; ++i) {
            fread(frame.udp_structure + i, sizeof(char), 1, in);
        }

        if (frame.frame_size == 0) {
            break;
        }
        
        for (i = 0; i < frame.frame_size - DESTINATION_ADDRESS_SIZE -
                 SOURCE_ADDRESS_SIZE - IPV4_SIZE - IP_STRUCTURE_SIZE -
                 UDP_STRUCTURE_SIZE - SN_SIZE - CRC_SIZE; ++i) {
            fread(frame.afdxES_payload + i, sizeof(char), 1, in);
        }

        for (i = 0; i < SN_SIZE; ++i) {
            fread(frame.sn + i, sizeof(char), 1, in);
        }

        for (i = 0; i < sizeof(int); ++i) {
            fread((char*)&frame.crc + i, sizeof(char), 1, in);
        }

        fprintf(out, "####################### Frame size: %u\n", frame.frame_size);

        fprintf(out, "Destination Address: ");
        for (i = 0; i < DESTINATION_ADDRESS_SIZE; ++i) {
            fprintf(out, "%u", frame.destination_address[i]);
        }
        fprintf(out, "\n");

        fprintf(out, "Source Address: ");
        for (i = 0; i < SOURCE_ADDRESS_SIZE; ++i) {
            fprintf(out, "%u", frame.source_address[i]);
        }
        fprintf(out, "\n");
 
        fprintf(out, "IPv4: ");
        for (i = 0; i < IPV4_SIZE; ++i) {
            fprintf(out, "%u", frame.ipv4[i]);
        }
        fprintf(out, "\n");

        fprintf(out, "IP Structure: ");
        for (i = 0; i < IP_STRUCTURE_SIZE; ++i) {
            fprintf(out, "%u", frame.ipv4[i]);
        }
        fprintf(out, "\n");
        
        fprintf(out, "IP Structure: ");
        for (i = 0; i < IP_STRUCTURE_SIZE; ++i) {
            fprintf(out, "%u", frame.ip_structure[i]);
        }
        fprintf(out, "\n");

        fprintf(out, "UDP Structure: ");
        for (i = 0; i < UDP_STRUCTURE_SIZE; ++i) {
            fprintf(out, "%u", frame.udp_structure[i]);
        }
        fprintf(out, "\n");

        fprintf(out, "AFDX Payload: ");
        for (i = 0; i < frame.frame_size - DESTINATION_ADDRESS_SIZE -
                 SOURCE_ADDRESS_SIZE - IPV4_SIZE - IP_STRUCTURE_SIZE -
                 UDP_STRUCTURE_SIZE - SN_SIZE - CRC_SIZE; ++i) {
            fprintf(out, "%u", frame.afdxES_payload[i]);
        }
        fprintf(out, "\n");

        fprintf(out, "SN: ");
        for (i = 0; i < SN_SIZE; ++i) {
            fprintf(out, "%u", frame.sn[i]);
        }
        fprintf(out, "\n");

        fprintf(out, "CRC: %u", frame.crc);
        fprintf(out, "\n\n\n");

    }
    
    return 0;
}
