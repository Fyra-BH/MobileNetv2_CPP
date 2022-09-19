from torch import Tensor
import numpy as np
import os

def save_tensor_as_text(t: Tensor, filename: str):
    np_arr = np.array(t.detach())
    tmpfile = filename + '.tmp'
    np.savetxt(tmpfile, np_arr.flatten(), fmt="%f")
    with open(filename, 'w') as fp:
        fp.write(str(np_arr.shape)[1:-1] + "\n")
        fp.write(open(tmpfile).read())
    os.remove(tmpfile)

