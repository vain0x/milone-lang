#include "milone.h"

int main();

int main() {
    printf("No formats\n");
    struct String hello_ = (struct String){.str = "Hello!", .len = 6};
    printf("%s\n", hello_.str);
    printf("Welcome to %s. Entry price is %c%d!\n", "Milone Land", '$', 1000000007);
    return 0;
}
