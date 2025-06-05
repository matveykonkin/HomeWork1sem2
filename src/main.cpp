#include "cyclicList.h"
#include <iostream>

int main() {
    CyclicList<int> list = {1, 2, 3, 4, 5};
    
    std::cout << "List elements: ";
    for (const auto& item : list) {
        std::cout << item << " ";
    }
    std::cout << "\n";
    
    return 0;
}