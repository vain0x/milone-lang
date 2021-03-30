#include "milone.h"

int Competitive_ABC140A_abc140aSolve(int n_8);

char Competitive_ABC140A_abc140aTest(char arg_148);

int Competitive_Helpers_scanInt(char);

char Competitive_ABC140A_abc140aMain(char arg_149);

int Competitive_ABC140A_abc140aSolve(int n_8) {
    return ((n_8 * n_8) * n_8);
}

char Competitive_ABC140A_abc140aTest(char arg_148) {
    int call_369 = Competitive_ABC140A_abc140aSolve(2);
    milone_assert((call_369 == 8), 8, 2);
    int call_370 = Competitive_ABC140A_abc140aSolve(1);
    milone_assert((call_370 == 1), 9, 2);
    return 0;
}

char Competitive_ABC140A_abc140aMain(char arg_149) {
    int call_371 = Competitive_Helpers_scanInt(0);
    int n_9 = call_371;
    int call_372 = Competitive_ABC140A_abc140aSolve(n_9);
    int m_4 = call_372;
    printf("%d\n", m_4);
    return 0;
}
