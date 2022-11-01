#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

#include <stdint.h>

typedef struct
{
    int16_t w, h;
    int16_t *data;
}int16_2d_tensor;

typedef int16_2d_tensor int16_matrix;

typedef struct
{
    int16_t ch, w, h;
    int16_t *data;
}int16_3d_tensor;



#endif
