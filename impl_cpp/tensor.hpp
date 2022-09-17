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
#include <iostream>
#include <stdio.h>
using namespace std;

class dimension {
    public:
        dimension(string str);
        int& operator[](int i);
        int length();
    private:
        dimension(int num,  int *arr);
        int num;
        int *arr;
};

/**
 * @brief Construct a new dimension::dimension object
 * 
 * @param num 有几个维度
 * @param arr 各个维度的大小（数组）
 */
dimension::dimension(int num,  int *arr)
{
    this->num = num;
    this->arr = arr;
}

/**
 * @brief Construct a new dimension::dimension object
 * 
 * @param str 字符串输入  形式: "3,1,2,3" 
                第一个数字代表之后有几个值
 */
dimension::dimension(string str)
{
    int *arr;
    int num;

    const char *s = str.c_str();
    printf("dimension %s\n", s);
    sscanf(s, "%d", &num);
    s = strchr(s, ',')+1;
    arr = new int[num];

    for (int i = 0; i < num; i++)
    {
        sscanf(s, "%d", &arr[i]);
        s = strchr(s, ',')+1;
    }
    this->num = num;
    this->arr = arr;
}

int& dimension::operator[](int i)
{
    if (i > num) 
    {// 超出索引
        return arr[0];
    }
    return arr[i];
}

int dimension::length(){
    return num;
}

class tensor{

};


#endif
