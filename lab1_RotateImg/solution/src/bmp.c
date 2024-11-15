#include "../include/bmp.h"
#include <stdlib.h>

// тут паддинг, который говорили проверять в readme
size_t get_padding(uint64_t width) {
    return (4 - (width * 3) % 4) % 4;
}

enum read_status from_bmp(FILE* in, struct image* img) {
    struct bmp_header header;
    fread(&header, sizeof(struct bmp_header), 1, in);

    if (header.bfType != 0x4D42 || header.biBitCount != 24) {
        return READ_INVALID_SIGNATURE;
    }

    img->width = header.biWidth;
    img->height = header.biHeight;

    size_t padding = get_padding(img->width);
    img->data = malloc(img->width * img->height * sizeof(struct pixel));

    for (uint64_t y = 0; y < img->height; ++y) {
        fread(&img->data[y * img->width], sizeof(struct pixel), img->width, in);
        fseek(in, padding, SEEK_CUR);
    }

    return READ_OK;
}

enum write_status to_bmp(FILE* out, struct image const* img) {
    struct bmp_header header = {
        .bfType = 0x4D42,
        .bfileSize = sizeof(struct bmp_header) + img->width * img->height * sizeof(struct pixel),
        .bOffBits = sizeof(struct bmp_header),
        .biSize = 40,
        .biWidth = img->width,
        .biHeight = img->height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage = img->width * img->height * sizeof(struct pixel)
    };

    fwrite(&header, sizeof(struct bmp_header), 1, out);
    size_t padding = get_padding(img->width);

    for (uint64_t y = 0; y < img->height; ++y) {
        fwrite(&img->data[y * img->width], sizeof(struct pixel), img->width, out);
        fwrite("\0\0\0", 1, padding, out);
    }

    return WRITE_OK;
}