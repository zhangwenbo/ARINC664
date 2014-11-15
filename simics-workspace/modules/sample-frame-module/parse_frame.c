#include <stdio.h>
#include <string.h>

const char *infilename = "";
const char *outfilename = "";

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
    char crc[CRC_SIZE + 1];
} Frame_Package;

int main(int argc, char *argv[]) {
    FILE *in = fopen(infilename, "rb");
    FILE *out = fopen(outfilename, "w");

    while (feof(in)) {
        Frame_Package frame;
        memset(&frame, 0, sizeof(Frame_Package));
        fread(&frame.frame_size, sizeof(int), 1, in);
        fread(frame.destination_address, DESTINATION_ADDRESS_SIZE, 1, in);
        fread(frame.source_address, SOURCE_ADDRESS_SIZE, 1, in);
        fread(frame.ipv4, IPV4_SIZE, 1, in);
        fread(frame.ip_structure, IP_STRUCTURE_SIZE, 1, in);
        fread(frame.udp_structure, UDP_STRUCTURE_SIZE, 1, in);
        fread(frame.afdxES_payload, frame.frame_size - DESTINATION_ADDRESS_SIZE -
              SOURCE_ADDRESS_SIZE - IPV4_SIZE - IP_STRUCTURE_SIZE -
              UDP_STRUCTURE_SIZE - SN_SIZE - CRC_SIZE, 1, in);
        fread(frame.sn, SN_SIZE, 1, in);
        fread(frame.crc, CRC_SIZE, 1, in);

        fprintf(out, "####################### Frame size: %d\n", frame.frame_size);
        fprintf(out, "Destination Address: %s\n", frame.destination_address);
        fprintf(out, "Source Address: %s\n", frame.source_address);
        fprintf(out, "IPv4: %s\n", frame.ipv4);
        fprintf(out, "IP Structure: %s\n", frame.ip_structure);
        fprintf(out, "UDP Structure: %s\n", frame.udp_structure);
        fprintf(out, "AFDX Payload: %s\n", frame.afdxES_payload);
        fprintf(out, "SN: %s\n", frame.sn);
        fprintf(out, "CRC: %s\n\n\n", frame.crc);        
    }
    
    return 0;
}

