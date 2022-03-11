#include <milone.h>

struct IntGU1_;

struct IntGU1option1_;

int main(int argc, char** argv);

enum IntGU1_Discriminant {
    GU_,
};

struct IntGU1_ {
    enum IntGU1_Discriminant discriminant;
    union {
        void const* GU_;
    };
};

enum IntGU1option1_Discriminant {
    None_,
    Some_,
};

struct IntGU1option1_ {
    enum IntGU1option1_Discriminant discriminant;
    union {
        struct IntGU1_ Some_;
    };
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    void const* box_;
    struct IntGU1_ variant_;
    box_ = ((void const*)milone_mem_alloc(1, sizeof(struct IntGU1option1_)));
    (*(((struct IntGU1option1_*)box_))) = (struct IntGU1option1_){.discriminant = None_};
    variant_ = (struct IntGU1_){.discriminant = GU_, .GU_ = box_};
    return 0;
}
