#include "milone.h"

bool unary_op_syntax_Program_f(int n_, int m_);

int milone_main();

bool unary_op_syntax_Program_f(int n_, int m_) {
    return (n_ == (m_ + 1));
}

int milone_main() {
    bool call_ = unary_op_syntax_Program_f(-1, -2);
    milone_assert(call_, 5, 2);
    return 0;
}
