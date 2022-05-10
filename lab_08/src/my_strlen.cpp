#include <cstdlib>

#include "my_strlen.hpp"

size_t my_strlen(const char *const buffer)
{
    size_t size;

    __asm__("xor %%rcx, %%rcx;"
            "not %%rcx;"
            "movb $0, %%al;"
            "movq %1, %%rdi;"
            "repne scasb;"
            "not %%rcx;"
            "dec %%rcx;"
            "mov %%rcx, %0;"
            : "=r"(size)
            : "r"(buffer)
            : "rcx", "rdi", "al"
           );
    
    return size;
}

