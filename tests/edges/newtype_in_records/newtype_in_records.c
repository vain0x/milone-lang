#include "milone.h"

enum Day_Discriminant;

struct Day_;

struct Day_ newDay_(int value_);

int dayToInt_(struct Day_ arg_);

struct DayRange_;

struct DayRange_ newDayRange_(struct Day_ start_, struct Day_ endDay_);

bool between_(struct Day_ day_, struct DayRange_ range_);

int main();

enum Day_Discriminant {
    Day_,
};

struct Day_ {
    enum Day_Discriminant discriminant;
    union {
        int Day_;
    };
};

struct Day_ newDay_(int value_) {
    bool if_;
    if ((value_ >= 1)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (31 >= value_);
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    milone_assert(if_, 10, 2);
    struct Day_ variant_ = (struct Day_){.discriminant = Day_, .Day_ = value_};
    return variant_;
}

int dayToInt_(struct Day_ arg_) {
    int value_1 = arg_.Day_;
    return value_1;
}

struct DayRange_ {
    struct Day_ t0;
    struct Day_ t1;
};

struct DayRange_ newDayRange_(struct Day_ start_, struct Day_ endDay_) {
    int call_ = dayToInt_(endDay_);
    int call_1 = dayToInt_(start_);
    milone_assert((call_ >= call_1), 16, 2);
    struct DayRange_ DayRange_ = (struct DayRange_){.t0 = start_, .t1 = endDay_};
    return DayRange_;
}

bool between_(struct Day_ day_, struct DayRange_ range_) {
    int call_2 = dayToInt_(day_);
    int call_3 = dayToInt_(range_.t0);
    bool if_1;
    if ((call_2 >= call_3)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    int call_4 = dayToInt_(range_.t1);
    int call_5 = dayToInt_(day_);
    if_1 = (call_4 >= call_5);
    goto if_next_4;
else_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int main() {
    struct Day_ call_6 = newDay_(13);
    struct Day_ call_7 = newDay_(10);
    struct Day_ call_8 = newDay_(20);
    struct DayRange_ call_9 = newDayRange_(call_7, call_8);
    bool call_10 = between_(call_6, call_9);
    milone_assert(call_10, 25, 2);
    return 0;
}
