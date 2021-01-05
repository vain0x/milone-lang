#include "milone.h"

enum NewTypeInt_Discriminant;

struct NewTypeInt_;

int main();

enum NewTypeInt_Discriminant {
    NewTypeInt_,
};

struct NewTypeInt_ {
    enum NewTypeInt_Discriminant discriminant;
    union {
        int NewTypeInt_;
    };
};

int main() {
    struct NewTypeInt_ variant_ = (struct NewTypeInt_){.discriminant = NewTypeInt_, .NewTypeInt_ = 1};
    int inner_ = variant_.NewTypeInt_;
    milone_assert((inner_ == 1), 8, 2);
    return 0;
}
