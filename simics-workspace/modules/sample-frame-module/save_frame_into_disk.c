#include <stdio.h>
#include <sys/stat.h>

typedef unsigned int uint32;

FILE *frame_image;
const char *filename = "frame_image.bin";
const int max_file_size = 4096 * 1024;

static int get_file_size(void) {
    struct stat file_stats;
    int file_size = 0;
    
    if (stat(filename, &file_stats)) {
        fprintf(stderr, "File doesn't exsit.\n");
        file_size = -1;
    } else {
        file_size = file_stats.st_size;
    }

    return file_size;
}

void save_frame_into_disk(void *frame, void *frame_size) {
    int file_size = get_file_size();

    if ((file_size != -1) && (file_size >= max_file_size)) {
        fseek(frame_image, 0, SEEK_SET);
    } else {
        fseek(frame_image, 0, SEEK_END);        
    }

    fwrite(frame_size, sizeof(*(uint32*)frame_size), 1, frame_image);
    fwrite(frame, *(uint32*)frame_size, 1, frame_image);
}

void init_frame_image(void) {
    frame_image = fopen(filename, "wb");
}

void fini_frame_image(void) {
    fclose(frame_image);
}
