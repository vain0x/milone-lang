#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct String hello_;
    printf("No formats\n");
    hello_ = (struct String){.ptr = "Hello!", .len = 6};
    printf("%s\n", string_to_c_str(hello_));
    printf("Welcome to %s. Entry price is %c%d!\n", "Milone Land", '$', 1000000007);
    return 0;
}
