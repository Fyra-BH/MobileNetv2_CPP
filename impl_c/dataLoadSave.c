#include "include.h"

void load_feature_map_from_file(featureMap *img, char *filename)
{
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d,%d,%d", &(img->channels), &(img->width), &(img->height));
    int len = img->channels * img->width * img->height;
    img->data = (float *)MEM_ALLOC(len * sizeof(float));
    for (int i = 0; i < len; i++)
    {
        fscanf(fp, "%f", img->data + i);
    }
}

void load_kernel_from_file(kernel *ker, char *filename)
{
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d,%d,%d,%d", &(ker->out_channels), &(ker->in_channels), &(ker->width), &(ker->height));
    int len = ker->out_channels * ker->in_channels * ker->width * ker->height;
    ker->data = (float *)MEM_ALLOC(len * sizeof(float));
    for (int i = 0; i < len; i++)
    {
        fscanf(fp, "%f", ker->data + i);
    }
}


void save_feature_map_to_file(featureMap img, char *filename)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d,%d,%d\n", img.channels, img.width, img.height);
    int len = img.channels * img.width * img.height;
    for (int i = 0; i < len; i++)
    {
        fprintf(fp, "%f\n", img.data[i]);
    }
}

void save_kernel_to_file(kernel ker, char *filename)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d,%d,%d,%d\n", ker.in_channels, ker.out_channels, ker.width, ker.height);
    int len = ker.in_channels * ker.out_channels * ker.width * ker.height;
    for (int i = 0; i < len; i++)
    {
        fprintf(fp, "%f\n", ker.data[i]);
    }
}

