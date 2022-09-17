#include <iostream>
#include "tensor.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "hello wolrd" << endl;
    dimension d = dimension("3,3,125,125");
    cout << d.length() << endl;
    for (int i = 0; i < d.length(); i++)
    {
        cout << "d[i]="<<d[i] << endl;
    }

    return 0;
}
