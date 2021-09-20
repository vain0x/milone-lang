#include "milone.h"

int abc140aSolve_(int n_1);

void Competitive_ABC140A_abc140aTest(void);

int Competitive_Helpers_scanInt(void);

void Competitive_ABC140A_abc140aMain(void);

int abc140aSolve_(int n_1) {
    return ((n_1 * n_1) * n_1);
}

void Competitive_ABC140A_abc140aTest(void) {
    int call_38 = abc140aSolve_(2);
    milone_assert((call_38 == 8), 8, 2);
    int call_39 = abc140aSolve_(1);
    milone_assert((call_39 == 1), 9, 2);
    return;
}

void Competitive_ABC140A_abc140aMain(void) {
    int call_40 = Competitive_Helpers_scanInt();
    int n_2 = call_40;
    int call_41 = abc140aSolve_(n_2);
    int m_1 = call_41;
    printf("%d\n", m_1);
    return;
}
