import torch
from mobilenetv2 import mobilenetv2
from fuse_bn import fuse_module

SAVED_FILE = 'mobilenetv2_on_cifar10.pth'

if __name__ == "__main__":
    net1 = mobilenetv2()
    net1.load_state_dict(torch.load(SAVED_FILE))
    net2 = fuse_module(net1)
    
    data_in = torch.randn(1, 3, 32, 32)
    out1 = net1(data_in)
    out2 = net2(data_in)
    
    err = torch.sum(torch.abs(out1 - out2))
    print(err)