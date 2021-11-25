#include <iostream>
#include <utility>

#include "X.h"


int main() {
    X x1(1);
    X x2(2);

    std::cout << "copy assignment: ";
    x1 = x2;
    std::cout << std::endl;

    std::cout << "move assignment: ";
    x1 = std::move(x2);
    std::cout << std::endl;

    std::cout << "std::swap: ";
    std::swap(x1, x2);
    std::cout << std::endl;

    std::cout << "custom swap: ";
    swap(x1, x2);
    std::cout << std::endl;
}