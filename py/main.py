import torch
import torch.optim as optim
import os

from torch import nn
from torchvision.datasets import CIFAR10
from torchvision import transforms
from mobilenetv2 import mobilenetv2
from os import path

####################################
NUM_EPOCH   = 2
THREADS     = 8
BATCH_SIZE  = 128
PRINT_INTERVAL = 100
SAVED_FILE = 'mobilenetv2_on_cifar10.pth'
####################################

if __name__ == "__main__":
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Resize((32,32)),
        transforms.Normalize(mean=[0.5], std=[0.5])])

    train_set = CIFAR10(
        root="data",
        train=True,
        transform=transform,
        download=True)

    eval_set = CIFAR10(
        root="data",
        train=False,
        transform=transform,
        download=True)

    train_loader = torch.utils.data.DataLoader(
        train_set,
        batch_size = BATCH_SIZE,
        shuffle=True,
        num_workers=THREADS)

    eval_loader = torch.utils.data.DataLoader(
        eval_set,
        batch_size = BATCH_SIZE,
        shuffle=True,
        num_workers=THREADS)

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    device = torch.device("cpu")

    cnn = mobilenetv2()
    cnn = cnn.to(device)

    loss_fn = nn.CrossEntropyLoss()
    # optimizer = optim.SGD(cnn.parameters(), lr=0.04, momentum=0.9)
    optimizer = optim.Adam(cnn.parameters(), lr=0.01, weight_decay=1e-6)

    ###################### train ######################
    if not path.exists(SAVED_FILE):    
        for epoch in range(NUM_EPOCH):
            for i, data in enumerate(train_loader, 0):
                inputs, labels = data[0].to(device), data[1].to(device)
                optimizer.zero_grad()
                outputs = cnn(inputs)
                loss = loss_fn(outputs, labels)
                loss.backward()
                optimizer.step()
                if (i%PRINT_INTERVAL==0):
                    print("epoch:{}, loss:{}".format(epoch, loss))
        #save model
        torch.save(cnn.to('cpu').state_dict(), SAVED_FILE)

    #################### test on eval_set ####################
    cnn = mobilenetv2()
    cnn.load_state_dict(torch.load(SAVED_FILE))
    cnn.to(device)
    cnn.eval()
    corr_num = 0
    total_num = 0

    with torch.no_grad():
        for i, (datas, labels) in enumerate(eval_loader):
            outputs = cnn(datas.to(device))
            predicted = torch.argmax(outputs.detach(), dim=1)
            corr_num += torch.sum(predicted == labels.to(device))
            total_num += len(datas)

    print("eval set corr:{:0.4f}".format(corr_num / total_num))
    
    # ######################## export parameters #################
    # INCLUDE_DIR = path.join('..', 'params')
    # if not path.exists(INCLUDE_DIR):
    #     os.mkdir(INCLUDE_DIR)
    # for n, p in cnn.named_parameters():
    #     np2c_header(p.to('cpu').detach().numpy(), path.join(INCLUDE_DIR, n))