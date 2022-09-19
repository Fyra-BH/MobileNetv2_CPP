#include "tensor.hpp"

/**
 * @brief Construct a new dimension::dimension object
 * 
 * @param ndim 有几个维度
 * @param arr 各个维度的大小（数组）
 */
dimension::dimension(int ndim,  int *arr)
{
    // int *new_arr = new int[ndim];
    // for(int i=0;i<ndim;i++)
    //     new_arr[i] = arr[i];
    this->ndim = ndim;
    this->arr = arr;
}

/**
 * @brief Construct a new dimension::dimension object
 * 
 * @param str 字符串输入  形式: "1,2,3" 
                
 */
dimension::dimension(string str)
{
    int *arr;
    int ndim = 0;

    const char *s = str.c_str();
    while (*s)
    {
        if(*(s++) == ',')
            ndim++;
    }
    ndim = ndim + 1; // 数字比逗号多一个
    arr = new int[ndim];
    s = str.c_str();
    for (int i = 0; i < ndim; i++)
    {
        sscanf(s, "%d", &arr[i]);
        s = strchr(s, ',')+1;
    }
    this->ndim = ndim;
    this->arr = arr;
}

int& dimension::operator[](int i)
{
    if (i > ndim) 
    {// 超出索引
        return arr[0];
    }
    return arr[i];
}

int dimension::get_ndim(){
    return ndim;
}

int dimension::accum(){
    int accum_res = 1;
    for (int i = 0; i < this->get_ndim(); i++)
    {
        accum_res *= (*this)[i];
    }
    return accum_res;
}

/*----------------------------------------------------------------*/

/**
 * @brief Construct a new tensor::tensor object
 * 随机初始化
 * @param dim 维度
 * @param min 最小值
 * @param max 最大值
 */
tensor::tensor(dimension dim)
{
    int size;
    float *arr;
    float mean = 0.0;
    float var = 0.0;

    size = dim.accum();
    if (size == 0)
    {
        dim = dimension("0");
        size = 1;
    }
    arr = new float[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = (float)(rand() % 1000000);
        mean += arr[i] / (float)size;
    }
    for (int i = 0; i < size; i++)
    {
        var += (arr[i] - mean)*(arr[i] - mean) / (float)size;
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = (arr[i] - mean) / sqrt(var + 0.001);
    }
    

    this->dim = dim;
    this->arr = arr;
}

tensor::tensor(dimension dim, float *arr)
{
    int size;
    size = dim.accum();
    this->dim = dim;
    this->arr = arr;
}
/**
 * @brief Construct a new tensor::tensor object
 * 
 * @param dim 维度
 * @param n 填充数据
 */
tensor::tensor(dimension dim, float initial_value)
{
    float *arr;
    int size;
    size = dim.accum();

    arr = new float[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = initial_value;
    }
    
    this->dim = dim;
    this->arr = arr;
}


tensor tensor::operator[](int i){
    tensor &res = *this;
    if (dim.get_ndim() == 1)
    {
        if (i < dim[0])
        {
            dimension new_dim = dimension("0");
            tensor *res = new tensor(new_dim, this->arr + i);
            return *res;
        }
        else
            cout << "out of index" << endl;
    }
    else if(dim.get_ndim() > 1)
    {
        if(i < dim[0])
        {
            dimension new_dim = dimension(dim.get_ndim() - 1, dim.get_arr() + 1);
            int block_size = new_dim.accum();
            tensor *res = new tensor(new_dim, this->arr + block_size * i);
            return *res;
        }
    }

    return res;
}

// 一些双目运算符重载
static float float_op2(char op, float a, float b)
{
    switch (op)
    {
        case '+':
            return a + b;
            break;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
            break;       
        default:
            cout << "not supported" << endl;
            return 0.0;
            break;
    }
} 

tensor tensor_op2(char op, tensor a, float b)
{
    tensor res = tensor(a.shape(), new float[a.shape().get_ndim()]);
    for (int i = 0; i < res.size(); i++)
    {
        res.get_arr()[i] = float_op2(op, a.get_arr()[i], b);
    }
    return res;
}

tensor tensor::operator*(float a)
{
    return tensor_op2('*', *(this), a);
}

tensor tensor::operator+(float a)
{
    return tensor_op2('+', *(this), a);
}

tensor tensor::operator-(float b)
{
    return tensor_op2('-', *(this), b);
}

tensor tensor::operator/(float b)
{
    return tensor_op2('/', *(this), b);
}

/*------------------------------------------------*/

tensor tensor::operator*(tensor a)
{
    if (a.shape().accum() != 1)
    {
        cout << "shape mismatch" << endl;
    }
    return *(this) * a.get_arr()[0];
}

tensor tensor::operator+(tensor a)
{
    if (a.shape().accum() != 1)
    {
        cout << "shape mismatch" << endl;
    }
    return *(this) + a.get_arr()[0];
}

tensor tensor::operator-(tensor a)
{
    if (a.shape().accum() != 1)
    {
        cout << "shape mismatch" << endl;
    }
    return *(this) - a.get_arr()[0];
}

tensor tensor::operator/(tensor a)
{
    if (a.shape().accum() != 1)
    {
        cout << "shape mismatch" << endl;
    }
    return *(this) / a.get_arr()[0];
}