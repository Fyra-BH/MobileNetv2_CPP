#ifndef __MAT_MUL_H__
#define __MAT_MUL_H__

#include "data_type.h"
#include "nice_port.h"

// 固定尺寸矩阵乘 一律使用二维数组
void matmul_32x32(int16_t a[32][32], int16_t b[32][32], int16_t c[32][32]);
void matmul_32x32_c(int16_t a[32][32], int16_t b[32][32], int16_t c[32][32]);

// 不定尺寸矩阵乘 一律使用结构体
void matmul_32xN(int16_matrix *a, int16_matrix *b, int16_matrix *c);
void matmul_32xN_c(int16_matrix *a, int16_matrix *b, int16_matrix *c);
#endif
