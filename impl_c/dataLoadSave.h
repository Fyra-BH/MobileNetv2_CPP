#ifndef __DATA_LOAD_SAVE__H__
#define __DATA_LOAD_SAVE__H__

#include "dtype.h"

void load_feature_map_from_file(featureMap *img, char *filename);
void load_kernel_from_file(kernel *ker, char *filename);
void save_feature_map_to_file(featureMap img, char *filename);
void save_kernel_to_file(kernel ker, char *filename);

#endif
