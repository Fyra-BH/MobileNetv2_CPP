import torch
from mobilenetv2 import mobilenetv2
from torch import nn

SAVED_MODEL = "mobilenetv2_on_cifar10.pth"

def get_layer(net, name):
    ret = net
    for sub_name in name.split("."):
        ret = ret._modules[sub_name]
    return ret

# 递归获取每一层名称
def get_layer_names(net, name_list=[], root=""):
    if len(net._modules.keys()) == 0:
        name_list.append(root)
    else:
        for key in net._modules.keys():
            get_layer_names(net._modules[key], name_list, root+ ('.' if root!='' else '') +key)
    return name_list

# 获取 modules_to_fuse 列表 只融合 conv->bn
# https://pytorch.org/docs/stable/generated/torch.quantization.fuse_modules.html
def get_modules_to_fuse(net):
    name_list = get_layer_names(net)
    def _get_modules_to_fuse(name_list, fuse_list=[]):
        if len(name_list) >= 2:
            a, b = name_list[:2]
            if a[:-1] == b[:-1] and (ord(a[-1]) - ord(b[-1]))**2 == 1 and \
                type(get_layer(net, a)) == nn.Conv2d and type(get_layer(net, b)) == nn.BatchNorm2d: # # a和b是否相邻 以及 a和b类型是否正确
                    fuse_list.append([a, b])
                    _get_modules_to_fuse(name_list[2:], fuse_list)
            else:
                _get_modules_to_fuse(name_list[1:], fuse_list)
        return fuse_list
    return _get_modules_to_fuse(name_list)

def fuse_module():
    net = mobilenetv2()
    net.load_state_dict(torch.load(SAVED_MODEL))
    net.eval()
    modules_to_fuse = get_modules_to_fuse(net)
    fused_m = torch.quantization.fuse_modules(net, modules_to_fuse[:53])
    return fused_m


# if __name__ == '__main__':
#     net = mobilenetv2()
#     net.load_state_dict(torch.load(SAVED_MODEL))
#     net.eval()

#     layer_names = get_layer_names(net)
#     # for name in layer_names:
#     #     print(name, type(get_layer(net, name)))
#     modules_to_fuse = get_modules_to_fuse(net)
#     # for a, b in modules_to_fuse:
#     #     print("a = {0}\t{1}".format(a, type(get_layer(net,a))))
#     #     print("b = {0}\t{1}".format(b, type(get_layer(net,b))))
#     fused_m = torch.quantization.fuse_modules(net, modules_to_fuse[:53])
# for v in modules_to_fuse[:53]:
#     print(v)
# print(modules_to_fuse)
