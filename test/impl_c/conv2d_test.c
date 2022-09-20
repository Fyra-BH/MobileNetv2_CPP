#include "include.h"

int main(int argc, char const *argv[])
{
    featureMap img_in, img_out_py, img_out_c;
    kernel ker;
    load_feature_map_from_file(&img_in, "img.txt");
    load_feature_map_from_file(&img_out_py, "out.txt");
    load_kernel_from_file(&ker, "ker.txt");

    int len = emptyFeatureMap(img_out_c, img_out_py.channels,\
        img_out_py.width, \
        img_out_py.height);
        
    conv2d_s1p1k3(&img_in, &ker, &img_out_c);
    save_feature_map_to_file(img_out_c, "outc.txt");

    float err = 0.0;
    for (int i = 0; i < len; i++)
    {
        err += (img_out_c.data[i] - img_out_py.data[i]) * (img_out_c.data[i] - img_out_py.data[i]);
    }
    
    printf("err = %f\n", err);
    return 0;
}
