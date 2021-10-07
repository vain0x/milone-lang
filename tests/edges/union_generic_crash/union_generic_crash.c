#include "milone.h"

struct GU_;

struct IntGU1Option_;

int milone_main(void);

enum GU_Discriminant {
    GU_,
};

struct GU_ {
    enum GU_Discriminant discriminant;
    union {
        void const* GU_;
    };
};

enum IntGU1Option_Discriminant {
    None_,
    Some_,
};

struct IntGU1Option_ {
    enum IntGU1Option_Discriminant discriminant;
    union {
        struct GU_ Some_;
    };
};

int milone_main(void) {
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntGU1Option_));
    (*(((struct IntGU1Option_*)box_))) = (struct IntGU1Option_){.discriminant = None_};
    struct GU_ variant_ = (struct GU_){.discriminant = GU_, .GU_ = box_};
    return 0;
}
