#ifndef __DTYPE__H__
#define __DTYPE__H__

typedef struct{
    int channels, width, height;
    float *data;
}featureMap;

typedef struct{
    int out_channels, in_channels, width, height;
    float *data;
}kernel;

#endif
