#include "milone.h"

struct IntStringTuple2;

int main();

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

int main() {
    exit(1);
    struct IntStringTuple2 t_ = ((struct IntStringTuple2){});
    int x_ = t_.t0;
    struct String y_ = t_.t1;
    exit(2);
    printf("%s\n", ((struct String){}).str);
    void* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 1;
    exit((*(((int*)box_))));
    exit(0);
    return 0;
}
