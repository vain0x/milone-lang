#include <stdio.h>

// From StaticLibTest.a
extern int StaticLibTest_initialize(int argc, char **argv);
extern int my_gcd(int x, int y);
extern double my_multiply(int x, double y);

int main(int argc, char **argv) {
    StaticLibTest_initialize(argc, argv);

    printf("main\n");
    printf("gcd 12 16 = 4?  %d\n", my_gcd(12, 16));
    printf("multiply 7 3.14 = 21.98?  %lf\n", my_multiply(7, 3.14));
    return 0;
}
