#include "milone.h"

enum Day_Tag;

struct Day_;

struct Day_ newDay_(int value_);

int dayToInt_(struct Day_ arg_);

struct DayRange_;

struct DayRange_ newDayRange_(struct Day_ start_, struct Day_ endDay_);

int between_(struct Day_ day_, struct DayRange_ range_);

int main();

enum Day_Tag {
    Day_,
};

struct Day_ {
    enum Day_Tag tag;
    union {
        int Day_;
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
    struct Day_ variant_ = (struct Day_){.tag = Day_, .Day_ = value_};
    return variant_;
}

int dayToInt_(struct Day_ arg_) {
    int value_1 = arg_.Day_;
    return value_1;
}

struct DayRange_ {
    struct Day_ Start;
    struct Day_ End;
};

struct DayRange_ newDayRange_(struct Day_ start_, struct Day_ endDay_) {
    int call_ = dayToInt_(endDay_);
    int call_1 = dayToInt_(start_);
    milone_assert((call_ >= call_1), 16, 2);
    struct DayRange_ DayRange_;
    DayRange_.Start = start_;
    DayRange_.End = endDay_;
    return DayRange_;
}

int between_(struct Day_ day_, struct DayRange_ range_) {
    int call_2 = dayToInt_(day_);
    int call_3 = dayToInt_(range_.Start);
    int if_1;
    if ((call_2 >= call_3)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    int call_4 = dayToInt_(range_.End);
    int call_5 = dayToInt_(day_);
    if_1 = (call_4 >= call_5);
    goto if_next_4;
else_6:;
    if_1 = 0;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int main() {
    struct Day_ call_6 = newDay_(13);
    struct Day_ call_7 = newDay_(10);
    struct Day_ call_8 = newDay_(20);
    struct DayRange_ call_9 = newDayRange_(call_7, call_8);
    int call_10 = between_(call_6, call_9);
    milone_assert(call_10, 25, 2);
    return 0;
}
