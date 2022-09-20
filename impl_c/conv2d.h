#ifndef __CONV2D__H__
#define __CONV2D__H__

#include "dtype.h"

void conv2d_s1p1k3(featureMap *img_in, kernel *ker, featureMap *img_out);
void conv2d_pw(featureMap *img_in, kernel *ker, featureMap *img_out);
void conv2d_s1p1k3_dw(featureMap *img_in, kernel *ker, featureMap *img_out);

#endif
