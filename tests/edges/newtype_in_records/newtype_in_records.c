#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct DayRange_;

int32_t newtype_in_records_newtype_in_records_newDay(int32_t value_);

int32_t newtype_in_records_newtype_in_records_dayToInt(int32_t value_1);

struct DayRange_ newtype_in_records_newtype_in_records_newDayRange(int32_t start_, int32_t endDay_);

bool newtype_in_records_newtype_in_records_between(int32_t day_, struct DayRange_ range_);

int main(int argc, char **argv);

struct DayRange_ {
    int32_t t0;
    int32_t t1;
};

int32_t newtype_in_records_newtype_in_records_newDay(int32_t value_) {
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
    if ((!(if_))) milone_assert_error("newtype_in_records/newtype_in_records.milone", 10, 2);
    return value_;
}

int32_t newtype_in_records_newtype_in_records_dayToInt(int32_t value_1) {
    return value_1;
}

struct DayRange_ newtype_in_records_newtype_in_records_newDayRange(int32_t start_, int32_t endDay_) {
    int32_t call_;
    int32_t call_1;
    struct DayRange_ DayRange_;
    call_ = newtype_in_records_newtype_in_records_dayToInt(endDay_);
    call_1 = newtype_in_records_newtype_in_records_dayToInt(start_);
    if ((call_ < call_1)) milone_assert_error("newtype_in_records/newtype_in_records.milone", 16, 2);
    DayRange_ = (struct DayRange_){.t0 = start_, .t1 = endDay_};
    return DayRange_;
}

bool newtype_in_records_newtype_in_records_between(int32_t day_, struct DayRange_ range_) {
    int32_t call_2;
    int32_t call_3;
    bool if_1;
    int32_t call_4;
    int32_t call_5;
    call_2 = newtype_in_records_newtype_in_records_dayToInt(day_);
    call_3 = newtype_in_records_newtype_in_records_dayToInt(range_.t0);
    if ((call_2 >= call_3)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    call_4 = newtype_in_records_newtype_in_records_dayToInt(range_.t1);
    call_5 = newtype_in_records_newtype_in_records_dayToInt(day_);
    if_1 = (call_4 >= call_5);
    goto if_next_4;
else_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_6;
    int32_t call_7;
    int32_t call_8;
    struct DayRange_ call_9;
    bool call_10;
    call_6 = newtype_in_records_newtype_in_records_newDay(13);
    call_7 = newtype_in_records_newtype_in_records_newDay(10);
    call_8 = newtype_in_records_newtype_in_records_newDay(20);
    call_9 = newtype_in_records_newtype_in_records_newDayRange(call_7, call_8);
    call_10 = newtype_in_records_newtype_in_records_between(call_6, call_9);
    if ((!(call_10))) milone_assert_error("newtype_in_records/newtype_in_records.milone", 24, 2);
    return 0;
}
