int f_1(int x_1);

enum Val_Tag;

struct Val_;

int main();

int f_1(int x_1) {
    return x_1;
}

enum Val_Tag {
    Int_,
};

struct Val_ {
    enum Val_Tag tag;
    union {
        int* Int_;
    };
};

int main() {
    int match_;
    int* payload_ = (int*)malloc(sizeof(int));
    (*(((int*)payload_))) = 0;
    struct Val_ variant_ = (struct Val_){.tag = Int_, .Int_ = payload_};
    if (!((variant_.tag == Int_))) goto next_2;
    int x_ = (*(variant_.Int_));
    match_ = x_;
    goto end_match_1;
next_2:;
    exit(1);
end_match_1:;
    int n_ = match_;
    int call_ = f_1(n_);
    int m_ = call_;
    return m_;
}