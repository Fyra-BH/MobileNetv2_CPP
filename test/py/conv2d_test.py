import torch
from torch import nn
from utils import save_tensor_as_text
from torch.nn import functional as F

if __name__ == '__main__':
    with torch.no_grad():
        img = torch.randn(3, 64, 64)
        ker = torch.randn(16, 3, 3, 3)
        layer = nn.Conv2d(3, 16, 3, 1, 1, bias=False)
        out = F.conv2d(img, ker, stride=1, padding=1)
        
        save_tensor_as_text(img, "img.txt")
        save_tensor_as_text(ker, "ker.txt")
        save_tensor_as_text(out, "out.txt")