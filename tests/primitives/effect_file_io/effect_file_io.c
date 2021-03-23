#include "milone.h"

struct String file_read_all_text(struct String);

struct String effect_file_io_Program_fileReadAllText(struct String fileName_);

void file_write_all_text(struct String, struct String);

char effect_file_io_Program_fileWriteAllText(struct String fileName_1, struct String content_);

int milone_main();

struct String effect_file_io_Program_fileReadAllText(struct String fileName_) {
    struct String file_read_all_text_result = file_read_all_text(fileName_);
    return file_read_all_text_result;
}

char effect_file_io_Program_fileWriteAllText(struct String fileName_1, struct String content_) {
    file_write_all_text(fileName_1, content_);
    return 0;
}

int milone_main() {
    struct String call_ = effect_file_io_Program_fileReadAllText((struct String){.str = "tests/primitives/effect_file_io/input.txt", .len = 41});
    struct String content_1 = call_;
    milone_assert((str_compare(content_1, (struct String){.str = "hello\n", .len = 6}) == 0), 12, 2);
    struct String content_2 = str_add(content_1, (struct String){.str = "world\n", .len = 6});
    char call_1 = effect_file_io_Program_fileWriteAllText((struct String){.str = "tests/primitives/effect_file_io/output.txt", .len = 42}, content_2);
    return 0;
}
