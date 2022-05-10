#include <cmath>
#include <cstdlib>
#include <iostream>

#define EPS "%.20f"

double sin_pi()
{
    double result;

    __asm__("fldpi;"
            "fsin;"
            "fstp %0;"
            : "=m" (result)
            );

    return result;
}

double sin_half_pi()
{
    const int divider = 2;

    double result;
    
    __asm__("fldpi;"
            "fild %0;"
            "fdivp;"
            "fsin;"
            "fstp %1;"
            : "=m" (result)
            : "m" (divider)
            );

    return result;
}

int main()
{
    printf("Testing PI:\n");
    
    printf("Library sin(3.14) =         " EPS "\n", sin(3.14));
    printf("Library sin(3.141596) =     " EPS "\n", sin(3.141596));
    printf("Library sin(M_PI) =         " EPS "\n", sin(M_PI));
    printf("FPU sin(PI) =               " EPS "\n\n", sin_pi());
    
    printf("Testing PI / 2:\n");

    printf("Library sin(3.14 / 2) =     " EPS "\n", sin(3.14 / 2));
    printf("Library sin(3.141596 / 2) = " EPS "\n", sin(3.141596 / 2));
    printf("Library sin(M_PI / 2) =     " EPS "\n", sin(M_PI / 2));
    printf("FPU sin(PI / 2) =           " EPS "\n", sin_half_pi());
    
    return EXIT_SUCCESS;
}
