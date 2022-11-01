import torch
from mobilenetv2_simp import mobilenetv2
from fuse_bn import fuse_module
from utils import save_tensor_as_text
import os
from os import path

SAVED_MODEL = "mobilenetv2_on_cifar10_simp.pth"
TXT_PARAM_DIR = "txt_param"
if __name__ == '__main__':
    if not path.exists(TXT_PARAM_DIR):
        os.mkdir(TXT_PARAM_DIR)
    net = mobilenetv2()
    net.load_state_dict(torch.load(SAVED_MODEL))
    
    net = fuse_module(net)
    for n, p in net.named_parameters():
        print(n, p.shape)
        save_tensor_as_text(p, path.join(TXT_PARAM_DIR, n + ".txt"))
    