#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32GU1_;

struct Int32GU1option1_;

int main(int argc, char** argv);

enum Int32GU1_Discriminant {
    GU_,
};

struct Int32GU1_ {
    enum Int32GU1_Discriminant discriminant;
    union {
        void const* GU_;
    };
};

enum Int32GU1option1_Discriminant {
    None_,
    Some_,
};

struct Int32GU1option1_ {
    enum Int32GU1option1_Discriminant discriminant;
    union {
        struct Int32GU1_ Some_;
    };
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    void const* box_;
    struct Int32GU1_ variant_;
    box_ = ((void const*)milone_region_alloc(1, sizeof(struct Int32GU1option1_)));
    (*(((struct Int32GU1option1_*)box_))) = (struct Int32GU1option1_){.discriminant = None_};
    variant_ = (struct Int32GU1_){.discriminant = GU_, .GU_ = box_};
    return 0;
}
