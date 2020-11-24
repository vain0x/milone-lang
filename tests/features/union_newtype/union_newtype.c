#include "milone.h"

enum NewTypeInt_Tag;

struct NewTypeInt_;

int main();

enum NewTypeInt_Tag {
    NewTypeInt_,
};

struct NewTypeInt_ {
    enum NewTypeInt_Tag tag;
    union {
        void* NewTypeInt_;
    };
};

int main() {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 1;
    struct NewTypeInt_ variant_ = (struct NewTypeInt_){.tag = NewTypeInt_, .NewTypeInt_ = box_};
    int inner_ = (*(((int*)variant_.NewTypeInt_)));
    milone_assert((inner_ == 1), 7, 2);
    return 0;
}
