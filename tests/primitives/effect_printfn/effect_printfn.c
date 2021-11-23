#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    printf("No formats\n");
    struct String hello_ = (struct String){.str = "Hello!", .len = 6};
    printf("%s\n", str_to_c_str(hello_));
    printf("Welcome to %s. Entry price is %c%d!\n", "Milone Land", '$', 1000000007);
    return 0;
}
