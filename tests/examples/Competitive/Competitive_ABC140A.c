#include "milone.h"

int Competitive_ABC140A_abc140aSolve(int n_8);

void Competitive_ABC140A_abc140aTest(void);

int Competitive_Helpers_scanInt(void);

void Competitive_ABC140A_abc140aMain(void);

int Competitive_ABC140A_abc140aSolve(int n_8) {
    return ((n_8 * n_8) * n_8);
}

void Competitive_ABC140A_abc140aTest(void) {
    int call_352 = Competitive_ABC140A_abc140aSolve(2);
    milone_assert((call_352 == 8), 8, 2);
    int call_353 = Competitive_ABC140A_abc140aSolve(1);
    milone_assert((call_353 == 1), 9, 2);
    return;
}

void Competitive_ABC140A_abc140aMain(void) {
    int call_354 = Competitive_Helpers_scanInt();
    int n_9 = call_354;
    int call_355 = Competitive_ABC140A_abc140aSolve(n_9);
    int m_4 = call_355;
    printf("%d\n", m_4);
    return;
}
