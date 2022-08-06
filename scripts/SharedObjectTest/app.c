#include <stdio.h>

#define my_gcd SharedObjectTest_SharedObjectTest_myGcd
#define my_multiply SharedObjectTest_SharedObjectTest_myMultiple

// From libsotest.so
extern int my_gcd(int x, int y);
extern double my_multiply(int x, double y);

int main(void) {
    printf("main\n");
    printf("gcd 12 16 = 4?  %d\n", my_gcd(12, 16));
    printf("multiply 7 3.14 = 21.98?  %lf\n", my_multiply(7, 3.14));
    return 0;
}
