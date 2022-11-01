#include "matmul.h"

void matmul_32x32(int16_t a[32][32], int16_t b[32][32], int16_t c[32][32])
{
    nice_set_len(32);
    for (int i = 0; i < 32; i++) // 向A端口FIFO输入数据
        for (int j = 0; j < 32; j++)
            nice_en_a((int)a[i][j], 1<<i);

    for (int i = 0; i < 32; i++) // 向B端口FIFO输入数据
        for (int j = 0; j < 32; j++)
            nice_en_b((int)b[i][j] << 8, 1<<j);
    nice_start();
    nice_wait();

    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
        	c[j][i] = nice_read();
}


void matmul_32x32_c(int16_t a[32][32], int16_t b[32][32], int16_t c[32][32])
{
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < 32; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

/**
 * @brief 本函数用于计算维度为[32, N]和[N, 32]的矩阵相乘
 * 
 * @param a [32, N]
 * @param b [N, 32]
 * @param c [32, 32]
 */
void matmul_32xN(int16_matrix *a, int16_matrix *b, int16_matrix *c)
{
    // param check
    if (a->h != 32 || b->w != 32 || a->w != b->h)
    {
        printf("error: matrix shape mismatch");
        return;
    }
    int N = a->w;
    nice_set_len(N);
    for (int i = 0; i < 32; i++) // 向A端口FIFO输入数据
        for (int j = 0; j < N; j++)
            nice_en_a((int)a->data[i * 32 + j], 1<<i);

    for (int i = 0; i < N; i++) // 向B端口FIFO输入数据
        for (int j = 0; j < 32; j++)
            nice_en_b((int)b->data[i * N + j] << 8, 1<<j);
    nice_start();
    nice_wait();

    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
        	c->data[j * 32 + i] = nice_read();
}


/**
 * @brief 本函数用于计算维度为[32, N]和[N, 32]的矩阵相乘(纯C版本)
 * 
 * @param a [32, N]
 * @param b [N, 32]
 * @param c [32, 32]
 */
void matmul_32xN_c(int16_matrix *a, int16_matrix *b, int16_matrix *c)
{
    // param check
    if (a->h != 32 || b->w != 32 || a->w != b->h)
    {
        printf("error: matrix shape mismatch");
        return;
    }

    int N = a->w;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c->data[i * 32 + j] = 0;
            for (int k = 0; k < 32; k++)
            {
                c->data[i * 32 + j]+= a->data[i * N + k] * b->data[k * N + j];
            }
        }
    }
}
