#include "milone.h"

struct StringList;

struct BoolBoolStringListStringListStringListTuple5;

void* defaultOptions_(int arg_);

int main();

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct BoolBoolStringListStringListStringListTuple5 {
    int t0;
    int t1;
    struct StringList* t2;
    struct StringList* t3;
    struct StringList* t4;
};

void* defaultOptions_(int arg_) {
    struct BoolBoolStringListStringListStringListTuple5 tuple_;
    tuple_.t0 = 0;
    tuple_.t1 = 0;
    tuple_.t2 = NULL;
    tuple_.t3 = NULL;
    tuple_.t4 = NULL;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct BoolBoolStringListStringListStringListTuple5));
    (*(((struct BoolBoolStringListStringListStringListTuple5*)box_))) = tuple_;
    return box_;
}

int main() {
    void* call_ = defaultOptions_(0);
    void* _options_ = call_;
    return 0;
}
