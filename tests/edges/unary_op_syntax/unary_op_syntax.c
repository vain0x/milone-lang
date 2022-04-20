#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

bool unary_op_syntax_unary_op_syntax_f(int32_t n_, int32_t m_);

int main(int argc, char **argv);

bool unary_op_syntax_unary_op_syntax_f(int32_t n_, int32_t m_) {
    return (n_ == (m_ + 1));
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    bool call_;
    call_ = unary_op_syntax_unary_op_syntax_f(-1, -2);
    if ((!(call_))) milone_assert_error("unary_op_syntax/unary_op_syntax.milone", 5, 2);
    return 0;
}
