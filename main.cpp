#include <iostream>
#include "crossarray.hpp"

int main(){
    // Minimal smoke test to ensure build
    sjtu::CrossArray ca(2);
    int a[3] = {1,2,3};
    ca.InsertArrays(a,3);
    int b[2] = {4,5};
    ca.InsertArrays(b,2);
    std::cout << ca.At(0,0) + ca.At(1,1) << "\n"; // 1 + 5 = 6
    return 0;
}

