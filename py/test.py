import torch
import sys
import numpy as np
from mobilenetv2 import mobilenetv2
from PIL import Image
from fuse_bn import fuse_module

SAVED_MODEL = "mobilenetv2_on_cifar10.pth"

type_list = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python {} imagefile".format(sys.argv[0]))
        exit(1)
    
    net = fuse_module()
    # net.load_state_dict(torch.load(SAVED_MODEL))
    # net.eval()

    img = Image.open(sys.argv[1]).convert('RGB').resize((32, 32))
    img = (np.array(img) / 255.0) * 2.0 - 1.0
    img = torch.tensor(img.transpose((2,0,1))).unsqueeze(0).float()
    out = net(img)
    print(type_list[int(torch.argmax(out))])