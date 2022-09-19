#include "tensor.hpp"

/**
 * @brief 经典卷积 默认stride=1 paddings=1
 * 
 * @param img 特征图 [Ci, W, H]
 * @param ker 卷积核 [Co, Ci, Wk, Hk]
 * @return tensor [Co, W, H]
 */
tensor conv2d(tensor &img, tensor &ker)
{
    if (img.shape().get_ndim() != 3 ||ker.shape().get_ndim() != 4)
    {
        cerr << "Error: Wrong number of dimensions for conv2d\n" << endl;
        return;
    }
    dimension dim = dimension("0,0,0");
    dim[0] = ker.shape()[0];
    dim[1] = img.shape()[1];
    dim[2] = img.shape()[2];
}