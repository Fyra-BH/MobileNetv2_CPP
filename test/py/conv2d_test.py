import torch
from torch import nn
from utils import save_tensor_as_text

if __name__ == '__main__':
    with torch.no_grad():
        img = torch.ones(1, 5, 5).float()
        ker = torch.randn(1, 1, 3, 3)
        layer = nn.Conv2d(1, 1, 3, 1, 1)
        # out = F.conv2d(img, ker, stride=1, padding=1)
        out = layer(img)
        ker = next(layer.parameters())
        
        save_tensor_as_text(img, "img.txt")
        save_tensor_as_text(ker, "ker.txt")
        save_tensor_as_text(out, "out.txt")