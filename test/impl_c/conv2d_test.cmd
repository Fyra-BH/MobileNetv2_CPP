gcc conv2d_test.c ../../impl_c/conv2d.c ../../impl_c/dataLoadSave.c -I../../impl_c -DDEBUG -o conv2d_test.exe

python ../py/conv2d_test.py

conv2d_test.exe