#include <cstdio>
#include <iostream>
#include <cstring>

#include "unit_tests.hpp"
#include "my_strlen.hpp"
#include "my_strcpy.hpp"

void unit_test_01()
{
    char source[MAX_SIZE] = "Just a simple test.";
    char destination[MAX_SIZE] = "\0";
    size_t length = strlen(source);

    my_strcpy(destination, source, length);
    
    std::cout << "--Test #1--" << std::endl;
    std::cout << "Source string: " << source << std::endl;
    std::cout << "Destination string: " << destination << std::endl;
    
    printf("Source address: %p\n", &source[0]);
    printf("Destination address: %p\n", &destination[0]);
}

void unit_test_02()
{
    char source[MAX_SIZE] = "A test with same pointers.";
    size_t length = strlen(source);

    my_strcpy(source, source, length);
    
    std::cout << "--Test #2--" << std::endl;
    std::cout << "Source string: " << source << std::endl;
    std::cout << "Destination string: " << source << std::endl;
    
    printf("Source address: %p\n", &source[0]);
    printf("Destination address: %p\n", &source[0]);
}

void unit_test_03()
{
    char source[MAX_SIZE] = "A test with overlapping.";
    size_t length = strlen(source);
    
    std::cout << "--Test #3--" << std::endl;
    std::cout << "Source string: " << source << std::endl;
    
    my_strcpy(source + 12, source, length);

    std::cout << "Destination string: " << source << std::endl;

    printf("Source address: %p\n", &source[0]);
    printf("Destination address: %p\n", &source[12]);
}

