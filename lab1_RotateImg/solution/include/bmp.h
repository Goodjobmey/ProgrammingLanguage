#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdio.h>
#include "../include/image.h"


//Тут я взяла данные из readme: хедер для bmp и подсказки функций для оперирования
#pragma pack(push, 1)
struct bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bOffBits;
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
};

enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum read_status from_bmp(FILE* in, struct image* img);
enum write_status to_bmp(FILE* out, struct image const* img);

#endif // BMP_H