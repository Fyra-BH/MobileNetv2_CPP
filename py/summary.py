import torch
import torchsummary
from mobilenetv2 import mobilenetv2
from fuse_bn import fuse_module

if __name__ == '__main__':
#     net = mobilenetv2()
    net = fuse_module()
    torchsummary.summary(net, (3,32,32), device="cpu")