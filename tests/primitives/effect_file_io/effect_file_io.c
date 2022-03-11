#include <milone.h>

struct String file_read_all_text(struct String );

struct String effect_file_io_effect_file_io_fileReadAllText(struct String fileName_);

void file_write_all_text(struct String , struct String );

void effect_file_io_effect_file_io_fileWriteAllText(struct String fileName_1, struct String content_);

int main(int argc, char** argv);

struct String effect_file_io_effect_file_io_fileReadAllText(struct String fileName_) {
    struct String file_read_all_text_result;
    file_read_all_text_result = file_read_all_text(fileName_);
    return file_read_all_text_result;
}

void effect_file_io_effect_file_io_fileWriteAllText(struct String fileName_1, struct String content_) {
    file_write_all_text(fileName_1, content_);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct String content_1;
    struct String content_2;
    struct String call_;
    call_ = effect_file_io_effect_file_io_fileReadAllText((struct String){.str = "tests/primitives/effect_file_io/input.txt", .len = 41});
    content_1 = call_;
    milone_assert((str_compare(content_1, (struct String){.str = "hello\n", .len = 6}) == 0), (struct String){.str = "effect_file_io/effect_file_io.milone", .len = 36}, 12, 2);
    content_2 = str_add(content_1, (struct String){.str = "world\n", .len = 6});
    effect_file_io_effect_file_io_fileWriteAllText((struct String){.str = "tests/primitives/effect_file_io/output.txt", .len = 42}, content_2);
    return 0;
}
