#include "milone.h"

struct String fileReadAllText_(struct String fileName_);

int fileWriteAllText_(struct String fileName_1, struct String content_);

int main();

struct String fileReadAllText_(struct String fileName_) {
    struct String call_ = file_read_all_text(fileName_);
    return call_;
}

int fileWriteAllText_(struct String fileName_1, struct String content_) {
    int call_1 = file_write_all_text(fileName_1, content_);
    return 0;
}

int main() {
    struct String call_2 = fileReadAllText_((struct String){.str = "tests/functions/io_file/input.txt", .len = 33});
    struct String content_1 = call_2;
    milone_assert((str_cmp(content_1, (struct String){.str = "hello\n", .len = 6}) == 0));
    int call_3 = 0;
    struct String content_2 = str_add(content_1, (struct String){.str = "world\n", .len = 6});
    int call_4 = fileWriteAllText_((struct String){.str = "tests/functions/io_file/output.txt", .len = 34}, content_2);
    return 0;
}
