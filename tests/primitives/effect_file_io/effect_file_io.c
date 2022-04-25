#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct String file_read_all_text(struct String);

struct String effect_file_io_effect_file_io_fileReadAllText(struct String fileName_);

void file_write_all_text(struct String, struct String);

void effect_file_io_effect_file_io_fileWriteAllText(struct String fileName_1, struct String content_);

int main(int argc, char **argv);

struct String effect_file_io_effect_file_io_fileReadAllText(struct String fileName_) {
    struct String file_read_all_text_result;
    file_read_all_text_result = file_read_all_text(fileName_);
    return file_read_all_text_result;
}

void effect_file_io_effect_file_io_fileWriteAllText(struct String fileName_1, struct String content_) {
    file_write_all_text(fileName_1, content_);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct String content_1;
    struct String content_2;
    struct String call_;
    call_ = effect_file_io_effect_file_io_fileReadAllText((struct String){.ptr = "tests/primitives/effect_file_io/input.txt", .len = 41});
    content_1 = call_;
    if ((string_compare(content_1, (struct String){.ptr = "hello\n", .len = 6}) != 0)) milone_assert_error("effect_file_io/effect_file_io.milone", 12, 2);
    content_2 = string_add(content_1, (struct String){.ptr = "world\n", .len = 6});
    effect_file_io_effect_file_io_fileWriteAllText((struct String){.ptr = "tests/primitives/effect_file_io/output.txt", .len = 42}, content_2);
    return 0;
}
