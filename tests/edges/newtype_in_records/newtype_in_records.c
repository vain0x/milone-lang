#include "milone.h"

enum Day_Tag;

struct Day_;

struct Day_ newDay_(int value_);

int dayToInt_(struct Day_ arg_);

struct DayRange_;

void* newDayRange_(struct Day_ start_, struct Day_ endDay_);

int between_(struct Day_ day_, void* range_);

int main();

enum Day_Tag {
    Day_,
};

struct Day_ {
    enum Day_Tag tag;
    union {
        void* Day_;
    };
};

struct Day_ newDay_(int value_) {
    int if_;
    if ((value_ >= 1)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (31 >= value_);
    goto if_next_1;
else_3:;
    if_ = 0;
    goto if_next_1;
if_next_1:;
    milone_assert(if_, 10, 2);
    int call_ = 0;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = value_;
    struct Day_ variant_ = (struct Day_){.tag = Day_, .Day_ = box_};
    return variant_;
}

int dayToInt_(struct Day_ arg_) {
    int value_1 = (*(((int*)arg_.Day_)));
    return value_1;
}

struct DayRange_ {
    struct Day_ Start;
    struct Day_ End;
};

void* newDayRange_(struct Day_ start_, struct Day_ endDay_) {
    int call_1 = dayToInt_(endDay_);
    int call_2 = dayToInt_(start_);
    milone_assert((call_1 >= call_2), 16, 2);
    int call_3 = 0;
    struct DayRange_ DayRange_;
    DayRange_.Start = start_;
    DayRange_.End = endDay_;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct DayRange_));
    (*(((struct DayRange_*)box_1))) = DayRange_;
    return box_1;
}

int between_(struct Day_ day_, void* range_) {
    int call_4 = dayToInt_(day_);
    int call_5 = dayToInt_((*(((struct DayRange_*)range_))).Start);
    int if_1;
    if ((call_4 >= call_5)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    int call_6 = dayToInt_((*(((struct DayRange_*)range_))).End);
    int call_7 = dayToInt_(day_);
    if_1 = (call_6 >= call_7);
    goto if_next_4;
else_6:;
    if_1 = 0;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int main() {
    struct Day_ call_8 = newDay_(13);
    struct Day_ call_9 = newDay_(10);
    struct Day_ call_10 = newDay_(20);
    void* call_11 = newDayRange_(call_9, call_10);
    int call_12 = between_(call_8, call_11);
    milone_assert(call_12, 25, 2);
    int call_13 = 0;
    return 0;
}
