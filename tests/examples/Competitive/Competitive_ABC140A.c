#include "milone.h"

int abc140aSolve_(int n_8);

void Competitive_ABC140A_abc140aTest(void);

int Competitive_Helpers_scanInt(void);

void Competitive_ABC140A_abc140aMain(void);

int abc140aSolve_(int n_8) {
    return ((n_8 * n_8) * n_8);
}

void Competitive_ABC140A_abc140aTest(void) {
    int call_352 = abc140aSolve_(2);
    milone_assert((call_352 == 8), 8, 2);
    int call_353 = abc140aSolve_(1);
    milone_assert((call_353 == 1), 9, 2);
    return;
}

void Competitive_ABC140A_abc140aMain(void) {
    int call_354 = Competitive_Helpers_scanInt();
    int n_9 = call_354;
    int call_355 = abc140aSolve_(n_9);
    int m_4 = call_355;
    printf("%d\n", m_4);
    return;
}
