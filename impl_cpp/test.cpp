#include <iostream>
#include "tensor.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    
    cout << "let's begin" << endl;
    tensor img = tensor(dimension("3,3,3"));
    img = img[2][2];

    cout << "img val:" << endl;
    for (int i = 0; i < img.size(); ++i)
    {
        cout << img.get_arr()[i] << ", ";
    }

    cout << "\nimg*0.5 val:" << endl;
    for (int i = 0; i < img.size(); ++i)
    {
        cout << (img * 0.3).get_arr()[i] << ", ";
    }

    cout << "\nimg*-1 val:" << endl;
    for (int i = 0; i < img.size(); ++i)
    {
        cout << (img * tensor(dimension("1"), -1.0)).get_arr()[i] << ", ";
    }
    return 0;
}
