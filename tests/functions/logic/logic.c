#include "milone.h"

int main();

int main() {
    int if_;
    int if_1;
    int if_2;
    if ((2 < 1)) goto else_5;
    if_2 = (2 < 3);
    goto end_if_6;
else_5:;
    if_2 = 0;
end_if_6:;
    if ((!(if_2))) goto else_3;
    if_1 = 1;
    goto end_if_4;
else_3:;
    int if_3;
    if ((2 >= 3)) goto else_7;
    if_3 = (2 >= 1);
    goto end_if_8;
else_7:;
    if_3 = 0;
end_if_8:;
    if_1 = if_3;
end_if_4:;
    if ((!(if_1))) goto else_1;
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 1;
end_if_2:;
    return if_;
}
