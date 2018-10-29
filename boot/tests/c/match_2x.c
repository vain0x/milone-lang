int f_3(int x_4) {
    return (x_4 * x_4);
}

int main() {
    int match_6;
    int call_7 = f_3(3);
    if (!((call_7 == 1))) goto next_2;
    match_6 = 1;
    goto end_match_1;
next_2:;
    int y_5 = call_7;
    match_6 = (y_5 - 9);
    goto end_match_1;
end_match_1:;
    return match_6;
}
