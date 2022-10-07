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
        debug("wrong kernel width or height\n");
        return;
    }
    else if (ker->in_channels != img_in->channels)
    {
        debug("wrong kernel channels\n");
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

/**
 * @brief pointwise卷积 逐点卷积
 * 
 * @param img_in 输入特征图
 * @param ker 卷积核 MxNx1x1
 * @param img_out 输出特征图
 */
void conv2d_pw(featureMap *img_in, kernel *ker, featureMap *img_out)
{
    // check args
    if (ker->width != 1 || ker->height != 1)
    {
        debug("wrong kernel width or height\n");
        return;
    }
    else if (ker->in_channels != img_in->channels)
    {
        debug("wrong kernel channels\n");
        return;
    }
    
    // start conv2d
    int OCH = ker->out_channels;
    int ICH = ker->in_channels;
    int IW = img_in->width;
    int IH = img_in->height;
    // debug("OCH=%d ICH=%d IW=%d IH=%d KW=%d KH=%d\n", OCH, ICH, IW, IH, KW, KH);

    for (int och = 0; och < OCH; och++)
    {
        for (int ich = 0; ich < ICH; ich++)
        {
            for (int iw = 0; iw < IW; iw++)
            {
                for (int ih = 0; ih < IH; ih++)
                {
                    // img_out[och][iw][ih] += img_in[ich][iw][ih] * ker[och][ich][0][0]
                    *(img_out->data + och*IW*IH + iw*IH + ih) += \
                    *(img_in->data + ich*IW*IH + iw*IH + ih) * \
                    *(ker->data + och*ICH + ich);
                }

            }
        }
    }
}

/**
 * @brief depthwise卷积 深度可分离卷积
 * 
 * @param img_in 输入特征图
 * @param ker 卷积核 Mx1x3x3
 * @param img_out 输出特征图
 */
void conv2d_s1p1k3_dw(featureMap *img_in, kernel *ker, featureMap *img_out)
{
    // check args
    if (ker->in_channels != 1 || ker->width != 3 || ker->height != 3)
    {
        debug("wrong kernel width or height\n");
        return;
    }
    else if (ker->out_channels != img_in->channels)
    {
        debug("wrong kernel channels\n");
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
                        {   // img_out[och][iw][ih] += img_in[och][iw+kw-1][ih+kh-1] * ker[och][0][kw][kh]
                            *(img_out->data + och*IW*IH + iw*IH + ih) += \
                            *(img_in->data + och*IW*IH + (iw+kw-1)*IH + (ih+kh-1)) * \
                            *(ker->data + och*KW*KH + kw*KH + kh);
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief depthwise卷积 深度可分离卷积 步进为2
 * 
 * @param img_in 输入特征图
 * @param ker 卷积核 Mx1x3x3
 * @param img_out 输出特征图
 */
void conv2d_s2p1k3_dw(featureMap *img_in, kernel *ker, featureMap *img_out)
{
    // check args
    if (ker->in_channels != 1 || ker->width != 3 || ker->height != 3)
    {
        debug("wrong kernel width or height\n");
        return;
    }
    else if (ker->out_channels != img_in->channels)
    {
        debug("wrong kernel channels\n");
        return;
    }
    else if (img_in->width / 2 != img_out->width || img_in->height / 2 != img_out->height)
    {
        debug("wrong kernel channels\n");
        return;
    }


    // start conv2d
    int OCH = ker->out_channels;
    int ICH = ker->in_channels;
    int IW = img_in->width / 2;
    int IH = img_in->height / 2;
    int KW = ker->width;
    int KH = ker->height;
    // debug("OCH=%d ICH=%d IW=%d IH=%d KW=%d KH=%d\n", OCH, ICH, IW, IH, KW, KH);

    for (int och = 0; och < OCH; och++)
    {
        for (int iw = 0; iw < IW; iw++)
        {
            for (int ih = 0; ih < IH; ih++)
            {
                for (int kw = 0; kw < KW; kw++)
                {
                    for (int kh = 0; kh < KH; kh++)
                    {
                        if (iw*2+kw==0 || ih*2+kh==0 || iw*2+kw-1>=IW*2 || ih*2+kh-1>=IH*2)
                        {   // 边界判断
                            // do nothing
                        }
                        else
                        {   // img_out[och][iw][ih] += img_in[och][iw*2+kw-1][ih*2+kh-1] * ker[och][0][kw][kh]
                            *(img_out->data + och*IW*IH + iw*IH + ih) += \
                            *(img_in->data + och*IW*IH*4 + (iw*2+kw-1)*IH*2 + (ih*2+kh-1)) * \
                            *(ker->data + och*KW*KH + kw*KH + kh);
                        }
                    }
                }
            }
        }
    }
}
