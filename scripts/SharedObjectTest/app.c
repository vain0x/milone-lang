#include <stdio.h>

// From libsotest.so
extern int SharedObjectTest_initialize(int argc, char **argv);
extern int my_gcd(int x, int y);
extern double my_multiply(int x, double y);
extern int my_static_var(void);

int main(int argc, char **argv) {
    SharedObjectTest_initialize(argc, argv);

    printf("main\n");
    printf("gcd 12 16 = 4?  %d\n", my_gcd(12, 16));
    printf("multiply 7 3.14 = 21.98?  %lf\n", my_multiply(7, 3.14));
    printf("staticVar = 4?  %d\n", my_static_var());
    return 0;
}
