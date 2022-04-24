#include <iostream>
using namespace std;

template <typename T> 
T multiply(T x, T y){
    return x*y;
}

template <typename T> T myMax(T x, T y)
{
    return (x > y) ? x : y;
}

int main(int argc, char* argv[]){
    printf("hello world\n");
    double t = multiply<double>(2.2,3);
    cout << t << endl;
    return 0;
}