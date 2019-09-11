#include "milone.h"

int main();

int main() {
    int match_;
    if (!((1 == 1))) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!((1 == 0))) goto next_3;
    match_ = 1;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}
