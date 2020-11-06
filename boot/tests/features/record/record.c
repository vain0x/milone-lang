#include "milone.h"

int main();

int main() {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    struct Point_ _pt_ = (*(((struct Point_*)box_)));
    return 0;
}
