#include "milone.h"

int f_(int x_);

int main();

int f_(int x_) {
    return (x_ * x_);
}

int main() {
    int switch_;
    int call_ = f_(3);
    switch (call_) {
       case 1:
          goto clause_2;

       default:
          goto clause_3;
    }
clause_2:;
    switch_ = 1;
    goto switch_next_1;
clause_3:;
    int y_ = call_;
    switch_ = (y_ - 9);
    goto switch_next_1;
switch_next_1:;
    return switch_;
}
