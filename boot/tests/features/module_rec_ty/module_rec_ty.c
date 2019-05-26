enum UnionA_Tag;

struct UnionA_;

struct UnionA_List;

enum UnionB_Tag;

struct UnionB_;

int main();

enum UnionA_Tag {
    T_1,
};

struct UnionA_ {
    enum UnionA_Tag tag;
};

struct UnionA_List {
    struct UnionA_ head;
    struct UnionA_List* tail;
};

enum UnionB_Tag {
    T_,
};

struct UnionB_ {
    enum UnionB_Tag tag;
    union {
        struct UnionA_List* T_;
    };
};

int main() {
    struct UnionA_List* list_ = (struct UnionA_List*)malloc(sizeof(struct UnionA_List));
    list_->head = (struct UnionA_){.tag = T_1};
    list_->tail = NULL;
    struct UnionB_ variant_ = (struct UnionB_){.tag = T_, .T_ = list_};
    struct UnionB_ UnionB_ = variant_;
    return 0;
}
