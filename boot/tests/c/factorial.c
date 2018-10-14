int factorial_2(void* _) {
    return 720;
}

int main() {
    int op_3 = (factorial_2(NULL) == 720);
    return op_3;
}
