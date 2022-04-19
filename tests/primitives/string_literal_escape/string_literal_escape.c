#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void string_literal_escape_string_literal_escape_f(char arg_);

void string_literal_escape_string_literal_escape_g(struct String arg_1);

int main(int argc, char** argv);

void string_literal_escape_string_literal_escape_f(char arg_) {
    return;
}

void string_literal_escape_string_literal_escape_g(struct String arg_1) {
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    string_literal_escape_string_literal_escape_f('\'');
    string_literal_escape_string_literal_escape_f('\\');
    string_literal_escape_string_literal_escape_f('\0');
    string_literal_escape_string_literal_escape_f('\x7f');
    string_literal_escape_string_literal_escape_f((char)'\xff');
    string_literal_escape_string_literal_escape_g((struct String){.ptr = "\"HELLO\n WORLD\"", .len = 14});
    string_literal_escape_string_literal_escape_g((struct String){.ptr = "\x7f", .len = 1});
    string_literal_escape_string_literal_escape_g((struct String){.ptr = "€ Á", .len = 3});
    return 0;
}
