#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

// Взяла из readme
struct pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel* data;
};

#endif // IMAGE_H
