#include <stdio.h>
#include <stdlib.h>
#include "../include/bmp.h"
#include "../include/rotate.h"
#include "../include/image.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source BMP> <output BMP>\n", argv[0]);
        return 1;
    }

    FILE *in_file = fopen(argv[1], "rb");
    if (!in_file) {
        perror("Error opening source file");
        return 1;
    }

    struct image img;
    if (from_bmp(in_file, &img) != READ_OK) {
        fprintf(stderr, "Failed to read BMP file\n");
        fclose(in_file);
        return 1;
    }
    fclose(in_file);

    struct image rotated_img = rotate(img);
    FILE *out_file = fopen(argv[2], "wb");
    if (!out_file) {
        perror("Error creating output file");
        free(img.data);
        return 1;
    }

    if (to_bmp(out_file, &rotated_img) != WRITE_OK) {
        fprintf(stderr, "Failed to write BMP file\n");
        fclose(out_file);
        free(img.data);
        free(rotated_img.data);
        return 1;
    }

    fclose(out_file);
    free(img.data);
    free(rotated_img.data);

    printf("Image rotated and saved successfully!\n");
    return 0;
}
