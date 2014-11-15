#include <stdio.h>
#include <sys/stat.h>

typedef unsigned int uint32;

typedef enum {
    SEND,
    RECV
} FRAME_TYPE;

FILE *frame_image[2];

const char *filename[] = {
    "sframe_image.bin",
    "rframe_image.bin"
};

const int max_file_size = 4096 * 1024;

static int get_file_size(int frame_type) {
    struct stat file_stats;
    int file_size = 0;
    
    if (stat(filename[frame_type], &file_stats)) {
        fprintf(stderr, "File doesn't exsit.\n");
        file_size = -1;
    } else {
        file_size = file_stats.st_size;
    }

    return file_size;
}

void save_frame_into_disk(void *frame, void *frame_size, int frame_type) {
    int file_size = get_file_size(frame_type);

    if ((file_size != -1) && (file_size >= max_file_size)) {
        fseek(frame_image[frame_type], 0, SEEK_SET);
    } else {
        fseek(frame_image[frame_type], 0, SEEK_END);
    }

    fwrite(frame_size, sizeof(*(uint32*)frame_size), 1, frame_image[frame_type]);
    fwrite(frame, *(uint32*)frame_size, 1, frame_image[frame_type]);
    fflush(frame_image[frame_type]);
}

void init_frame_image(void) {
    frame_image[0] = fopen(filename[0], "wb");
    frame_image[1] = fopen(filename[1], "wb");
}

void fini_frame_image(void) {
    fclose(frame_image[0]);
    fclose(frame_image[1]);
}
