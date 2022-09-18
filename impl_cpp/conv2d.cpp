#include "tensor.hpp"

/**
 * @brief 经典卷积
 * 
 * @param img 特征图 [C, W, H]
 * @param ker 卷积核 [Co, Ci, W, H]
 * @return tensor 
 */
tensor conv2d(tensor &img, tensor &ker){
    if (img.shape().get_ndim() != 3 ||ker.shape().get_ndim() != 4)
    {
        cerr << "Error: Wrong number of dimensions for conv2d\n" << endl;
        return;
    }
    
}