/**
 * @file tensor.h
 * @author Fyra-BH (fyra@foxmail.com)
 * @brief tensor数据类型实现
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __TENSOR_H__
#define __TENSOR_H__

#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>


using namespace std;

/**
 * @brief 
 * 
 */
class dimension {
    public:
        dimension(){};
        dimension(string str);
        dimension(int num,  int *arr);
        int& operator[](int i);
        int get_ndim();
        int accum();
        int *get_arr(){return arr;};
    private:
        int ndim=0;
        int *arr=NULL;
};

/**
 * @brief 
 * 
 */
class tensor{
    public:
        tensor(){};
        tensor(dimension dim);
        tensor(dimension dim, float *arr);
        tensor(dimension dim, float initial_value);

        float *get_arr(){return arr;};
        dimension shape(){return dim;};
        int size(){return dim.accum();};

        tensor operator[](int i);
        tensor operator*(float a);
        tensor operator+(float a);
        tensor operator-(float a);
        tensor operator/(float a);
        tensor operator*(tensor a);
        tensor operator+(tensor a);
        tensor operator-(tensor a);
        tensor operator/(tensor a);
    private:
        dimension dim;
        float *arr=NULL;
};

#endif
