#include "include.h"

/**
 * @brief 传统卷积 stride=1 paddings=1 卷积核尺寸固定为3x3
 * 
 * @param img_in 
 * @param ker 
 * @param img_out 
 */
void conv2d_s1p1k3(featureMap *img_in, kernel *ker, featureMap *img_out)
{
    // check args
    if (ker->width != 3 || ker->height != 3)
    {
        debug("wrong kernel width or height");
        return;
    }
    else if (ker->in_channels != img_in->channels)
    {
        debug("wrong kernel channels");
        return;
    }

    // start conv2d
    int OCH = ker->out_channels;
    int ICH = ker->in_channels;
    int IW = img_in->width;
    int IH = img_in->height;
    int KW = ker->width;
    int KH = ker->height;
    // debug("OCH=%d ICH=%d IW=%d IH=%d KW=%d KH=%d\n", OCH, ICH, IW, IH, KW, KH);

    for (int och = 0; och < OCH; och++)
    {
        for (int ich = 0; ich < ICH; ich++)
        {
            for (int iw = 0; iw < IW; iw++)
            {
                for (int ih = 0; ih < IH; ih++)
                {
                    for (int kw = 0; kw < KW; kw++)
                    {
                        for (int kh = 0; kh < KH; kh++)
                        {
                            if (iw+kw==0 || ih+kh == 0 || iw+kw-1==IW || ih+kh-1==IH)
                            {   // 边界判断
                                // do nothing
                            }
                            else
                            {   // img_out[och][iw][ih] += img_in[ich][iw+kw-1][ih+kh-1] * ker[och][ich][kw][kh]
                                *(img_out->data + och*IW*IH + iw*IH + ih) += \
                                *(img_in->data + ich*IW*IH + (iw+kw-1)*IH + (ih+kh-1)) * \
                                *(ker->data + och*ICH*KW*KH + ich*KW*KH + kw*KH + kh);
                            }
                        }
                    }
                }
            }
        }
    }
}