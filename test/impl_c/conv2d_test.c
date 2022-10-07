#include "include.h"

int main(int argc, char const *argv[])
{
    featureMap img_in, img_out_py, img_out_c;
    kernel ker;
    int len;
    float err;

    debug("---------------------------------------------------------------------------------------\n");
    load_feature_map_from_file(&img_in, "img_s1p1k3_test.txt");
    load_feature_map_from_file(&img_out_py, "out_s1p1k3_test.txt");
    load_kernel_from_file(&ker, "ker_s1p1k3_test.txt");

    len = emptyFeatureMap(img_out_c, img_out_py.channels,\
        img_out_py.width, \
        img_out_py.height);

    debug("conv2d_s1p1k3 test\t");
    debug("img_in:[%d,%d,%d]\t",img_in.channels, img_in.width, img_in.height);
    debug("kernel:[%d,%d,%d,%d]\t",ker.out_channels, ker.in_channels, ker.width, ker.height);
    debug("img_out:[%d,%d,%d]\n",img_out_c.channels, img_out_c.width, img_out_c.height);
    conv2d_s1p1k3(&img_in, &ker, &img_out_c);
    err = 0.0;
    for (int i = 0; i < len; i++)
    {
        err += pow2(img_out_c.data[i] - img_out_py.data[i]);
    }
    debug("err:%f\n", err);

    debug("---------------------------------------------------------------------------------------\n");
    load_feature_map_from_file(&img_in, "img_pw_test.txt");
    load_feature_map_from_file(&img_out_py, "out_pw_test.txt");
    load_kernel_from_file(&ker, "ker_pw_test.txt");

    len = emptyFeatureMap(img_out_c, img_out_py.channels,\
        img_out_py.width, \
        img_out_py.height);

    debug("conv2d_pw test\t");
    debug("img_in:[%d,%d,%d]\t",img_in.channels, img_in.width, img_in.height);
    debug("kernel:[%d,%d,%d,%d]\t",ker.out_channels, ker.in_channels, ker.width, ker.height);
    debug("img_out:[%d,%d,%d]\n",img_out_c.channels, img_out_c.width, img_out_c.height);
    conv2d_pw(&img_in, &ker, &img_out_c);
    err = 0.0;
    for (int i = 0; i < len; i++)
    {
        err += pow2(img_out_c.data[i] - img_out_py.data[i]);
    }
    debug("err:%f\n", err);

    debug("---------------------------------------------------------------------------------------\n");
    load_feature_map_from_file(&img_in, "img_dw_test.txt");
    load_feature_map_from_file(&img_out_py, "out_dw_test.txt");
    load_kernel_from_file(&ker, "ker_dw_test.txt");

    len = emptyFeatureMap(img_out_c, img_out_py.channels,\
        img_out_py.width, \
        img_out_py.height);

    debug("conv2d_s1p1k3_dw test\t");
    debug("img_in:[%d,%d,%d]\t",img_in.channels, img_in.width, img_in.height);
    debug("kernel:[%d,%d,%d,%d]\t",ker.out_channels, ker.in_channels, ker.width, ker.height);
    debug("img_out:[%d,%d,%d]\n",img_out_c.channels, img_out_c.width, img_out_c.height);
    conv2d_s1p1k3_dw(&img_in, &ker, &img_out_c);
    err = 0.0;
    for (int i = 0; i < len; i++)
    {
        err += pow2(img_out_c.data[i] - img_out_py.data[i]);
    }
    debug("err:%f\n", err);

    debug("---------------------------------------------------------------------------------------\n");
    load_feature_map_from_file(&img_in, "img_dw_s2_test.txt");
    load_feature_map_from_file(&img_out_py, "out_dw_s2_test.txt");
    load_kernel_from_file(&ker, "ker_dw_s2_test.txt");

    len = emptyFeatureMap(img_out_c, img_out_py.channels,\
        img_out_py.width, \
        img_out_py.height);

    debug("conv2d_s2p1k3_dw test\t");
    debug("img_in:[%d,%d,%d]\t",img_in.channels, img_in.width, img_in.height);
    debug("kernel:[%d,%d,%d,%d]\t",ker.out_channels, ker.in_channels, ker.width, ker.height);
    debug("img_out:[%d,%d,%d]\n",img_out_c.channels, img_out_c.width, img_out_c.height);
    conv2d_s2p1k3_dw(&img_in, &ker, &img_out_c);
    save_feature_map_to_file(img_out_c, "img_out_c.txt");
    err = 0.0;
    for (int i = 0; i < len; i++)
    {
        err += pow2(img_out_c.data[i] - img_out_py.data[i]);
    }
    debug("err:%f\n", err);
    return 0;
}
