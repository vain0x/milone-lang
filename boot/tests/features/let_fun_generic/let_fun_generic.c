void* failWith_(struct String msg_);

void* id_(void* x_);

struct StringList;

struct IntList;

int main();

void* failWith_(struct String msg_) {
    printf("%s\n", msg_.str);
    int call_2 = 0;
    exit(1);
    return NULL;
}

void* id_(void* x_) {
    return x_;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct IntList {
    int head;
    struct IntList* tail;
};

int main() {
    int call_ = id_(42);
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = (struct String){.str = "A", .len = 1};
    list_->tail = NULL;
    struct StringList* call_1 = id_(list_);
    struct IntList* call_3 = failWith_((struct String){.str = "string -> int list", .len = 18});
    struct StringList* call_4 = failWith_((struct String){.str = "string -> string list", .len = 21});
    return 0;
}
