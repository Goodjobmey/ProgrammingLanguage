#include "../include/rotate.h"
#include <stdlib.h>

struct image rotate(struct image const source) {
    struct image rotated;
    rotated.width = source.height;
    rotated.height = source.width;
    rotated.data = malloc(rotated.width * rotated.height * sizeof(struct pixel));

    for (uint64_t y = 0; y < source.height; ++y) {
        for (uint64_t x = 0; x < source.width; ++x) {
            rotated.data[x * rotated.width + (rotated.width - y - 1)] = source.data[y * source.width + x];
        }
    }

    return rotated;
}
