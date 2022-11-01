import torch
from torch import nn
from utils import save_tensor_as_text
from torch.nn import functional as F
import os

TXT_PARAM_DIR = "txt_param"
if __name__ == '__main__':
    if not os.path.exists(TXT_PARAM_DIR):
        os.mkdir(TXT_PARAM_DIR)
    with torch.no_grad():
        img = torch.randn(3, 32, 32)
        ker = torch.randn(16, 3, 3, 3)
        out = F.conv2d(img, ker, stride=1, padding=1)
        def _save_tensor_as_text(t, p):
            save_tensor_as_text(t, os.path.join(TXT_PARAM_DIR,p))
        _save_tensor_as_text(img, "img_s1p1k3_test.txt")
        _save_tensor_as_text(ker, "ker_s1p1k3_test.txt")
        _save_tensor_as_text(out, "out_s1p1k3_test.txt")
        
        img = torch.randn(16, 32, 32)
        ker = torch.randn(24, 16, 1, 1)
        out = F.conv2d(img, ker, stride=1, padding=0)
        _save_tensor_as_text(img, "img_pw_test.txt")
        _save_tensor_as_text(ker, "ker_pw_test.txt")
        _save_tensor_as_text(out, "out_pw_test.txt")

        img = torch.randn(96, 32, 32)
        ker = torch.randn(96, 1, 3, 3)
        out = F.conv2d(img, ker, stride=1, padding=1, groups=96)
        _save_tensor_as_text(img, "img_dw_test.txt")
        _save_tensor_as_text(ker, "ker_dw_test.txt")
        _save_tensor_as_text(out, "out_dw_test.txt")

        img = torch.randn(96, 32, 32)
        ker = torch.randn(96, 1, 3, 3)
        out = F.conv2d(img, ker, stride=2, padding=1, groups=96)
        _save_tensor_as_text(img, "img_dw_s2_test.txt")
        _save_tensor_as_text(ker, "ker_dw_s2_test.txt")
        _save_tensor_as_text(out, "out_dw_s2_test.txt")
        