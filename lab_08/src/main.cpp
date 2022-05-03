#include <iostream>
#include <cstring>

#include "my_strlen.hpp"
#include "unit_tests.hpp"

int main()
{
    char buffer[MAX_SIZE];

    std::cout << "Enter your string: ";

    std::cin >> buffer;

    std::cout << "Library STRLEN function: " << strlen(buffer) << std::endl;
    std::cout << "Custom assembly STRLEN function: " << my_strlen(buffer) << std::endl;

    unit_test_01();   
    unit_test_02();   
    unit_test_03();

    return EXIT_SUCCESS;
}

