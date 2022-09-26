import torch
import sys
from mobilenetv2 import mobilenetv2

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python {} imagefile".format(sys.argv[0]))