#include <milone.h>

struct UInt64UInt64Tuple2_;

struct String str_of_raw_parts(char const* , int );

struct String native_ptr_write_native_ptr_write_strOfRawParts(char const* p_, int len_);

int main(int argc, char** argv);

struct UInt64UInt64Tuple2_ {
    uint64_t t0;
    uint64_t t1;
};

struct String native_ptr_write_native_ptr_write_strOfRawParts(char const* p_, int len_) {
    struct String str_of_raw_parts_result;
    str_of_raw_parts_result = str_of_raw_parts(p_, len_);
    return str_of_raw_parts_result;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    void const* stringBox_;
    char* buf_;
    struct String s_;
    void const* box_;
    struct UInt64UInt64Tuple2_ UInt64UInt64Tuple2_;
    void const* box_1;
    struct String call_;
    box_ = ((void const*)milone_mem_alloc(1, sizeof(struct String)));
    (*(((struct String*)box_))) = (struct String){.str = "zero", .len = 4};
    stringBox_ = box_;
    (*(((struct String*)stringBox_))) = (struct String){.str = "one", .len = 3};
    milone_assert((str_compare((*(((struct String const*)stringBox_))), (struct String){.str = "one", .len = 3}) == 0), (struct String){.str = "native_ptr_write/native_ptr_write.milone", .len = 40}, 14, 2);
    UInt64UInt64Tuple2_ = (struct UInt64UInt64Tuple2_){.t0 = 0ULL, .t1 = 0ULL};
    box_1 = ((void const*)milone_mem_alloc(1, sizeof(struct UInt64UInt64Tuple2_)));
    (*(((struct UInt64UInt64Tuple2_*)box_1))) = UInt64UInt64Tuple2_;
    buf_ = ((char*)box_1);
    buf_[0] = 'H';
    buf_[1] = 'i';
    call_ = native_ptr_write_native_ptr_write_strOfRawParts(((char const*)buf_), 2);
    s_ = call_;
    milone_assert((str_compare(s_, (struct String){.str = "Hi", .len = 2}) == 0), (struct String){.str = "native_ptr_write/native_ptr_write.milone", .len = 40}, 22, 2);
    return 0;
}
