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
        int* NewTypeInt_;
    };
};

int main() {
    int* payload_ = (int*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)payload_))) = 1;
    struct NewTypeInt_ variant_ = (struct NewTypeInt_){.tag = NewTypeInt_, .NewTypeInt_ = payload_};
    int inner_ = (*(variant_.NewTypeInt_));
    milone_assert((inner_ == 1), 7, 2);
    int call_ = 0;
    return 0;
}
