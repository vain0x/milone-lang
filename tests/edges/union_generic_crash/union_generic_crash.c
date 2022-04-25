#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32GU1_;

struct Int32GU1option1_;

int main(int argc, char **argv);

enum Int32GU1_Discriminant {
    Int32GU1_GU,
};

struct Int32GU1_ {
    enum Int32GU1_Discriminant discriminant;
    union {
        void const *Int32GU1_GU;
    };
};

enum Int32GU1option1_Discriminant {
    Int32GU1option1_None,
    Int32GU1option1_Some,
};

struct Int32GU1option1_ {
    enum Int32GU1option1_Discriminant discriminant;
    union {
        struct Int32GU1_ Int32GU1option1_Some;
    };
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    void const *box_;
    struct Int32GU1_ variant_;
    box_ = ((void const *)milone_region_alloc(1, sizeof(struct Int32GU1option1_)));
    (*(((struct Int32GU1option1_ *)box_))) = (struct Int32GU1option1_){.discriminant = Int32GU1option1_None};
    variant_ = (struct Int32GU1_){.discriminant = Int32GU1_GU, .Int32GU1_GU = box_};
    return 0;
}
