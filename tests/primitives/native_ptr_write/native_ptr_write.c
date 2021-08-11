#include "milone.h"

struct UInt64UInt64Tuple2_;

struct String str_of_raw_parts(char const*, int);

struct String native_ptr_write_Program_strOfRawParts(char const* p_, int len_);

int milone_main();

struct UInt64UInt64Tuple2_ {
    uint64_t t0;
    uint64_t t1;
};

struct String native_ptr_write_Program_strOfRawParts(char const* p_, int len_) {
    struct String str_of_raw_parts_result = str_of_raw_parts(p_, len_);
    return str_of_raw_parts_result;
}

int milone_main() {
    void const* box_ = milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_))) = (struct String){.str = "zero", .len = 4};
    void const* stringBox_ = box_;
    (*(((struct String*)stringBox_))) = (struct String){.str = "one", .len = 3};
    milone_assert((str_compare((*(((struct String const*)stringBox_))), (struct String){.str = "one", .len = 3}) == 0), 11, 2);
    struct UInt64UInt64Tuple2_ UInt64UInt64Tuple2_ = (struct UInt64UInt64Tuple2_){.t0 = ((uint64_t)0), .t1 = ((uint64_t)0)};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct UInt64UInt64Tuple2_));
    (*(((struct UInt64UInt64Tuple2_*)box_1))) = UInt64UInt64Tuple2_;
    char* buf_ = ((char*)box_1);
    (*(buf_)) = 'H';
    buf_[1] = 'i';
    struct String call_ = native_ptr_write_Program_strOfRawParts(((char const*)buf_), 2);
    struct String s_ = call_;
    milone_assert((str_compare(s_, (struct String){.str = "Hi", .len = 2}) == 0), 20, 2);
    return 0;
}
