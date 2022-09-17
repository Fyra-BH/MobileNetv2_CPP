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

class dimension {
    public:
        dimension(int num,  int *arr);
    private:
        int num;
        int *arr;
};

dimension::dimension(int num,  int *arr){
    this->num = num;
    this->arr = arr;
}

class tensor{

};


#endif
