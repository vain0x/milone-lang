#include "milone.h"

int main();

int main() {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 1;
    int inner_ = (*(((int*)box_)));
    milone_assert((inner_ == 1), 7, 2);
    int call_ = 0;
    return 0;
}
