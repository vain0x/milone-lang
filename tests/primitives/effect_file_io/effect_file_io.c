#include "milone.h"

struct String file_read_all_text(struct String);

struct String fileReadAllText_(struct String fileName_);

void file_write_all_text(struct String, struct String);

int fileWriteAllText_(struct String fileName_1, struct String content_);

int milone_main();

struct String fileReadAllText_(struct String fileName_) {
    struct String file_read_all_text_result_ = file_read_all_text(fileName_);
    return file_read_all_text_result_;
}

int fileWriteAllText_(struct String fileName_1, struct String content_) {
    file_write_all_text(fileName_1, content_);
    return 0;
}

int milone_main() {
    struct String call_ = fileReadAllText_((struct String){.str = "tests/primitives/effect_file_io/input.txt", .len = 41});
    struct String content_1 = call_;
    milone_assert((str_compare(content_1, (struct String){.str = "hello\n", .len = 6}) == 0), 12, 2);
    struct String content_2 = str_add(content_1, (struct String){.str = "world\n", .len = 6});
    int call_1 = fileWriteAllText_((struct String){.str = "tests/primitives/effect_file_io/output.txt", .len = 42}, content_2);
    return 0;
}
