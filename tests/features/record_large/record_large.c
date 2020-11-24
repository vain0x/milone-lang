#include "milone.h"

struct StringList;

struct GitCommitOptions_;

void* defaultOptions_(int arg_);

int main();

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct GitCommitOptions_ {
    int All;
    int Patch;
    struct StringList* ReuseMessage;
    struct StringList* ReeditMessage;
    struct StringList* Fixup;
    struct StringList* Squash;
    int ResetAuthor;
};

void* defaultOptions_(int arg_) {
    struct GitCommitOptions_ GitCommitOptions_;
    GitCommitOptions_.All = 0;
    GitCommitOptions_.Patch = 0;
    GitCommitOptions_.ReuseMessage = NULL;
    GitCommitOptions_.ReeditMessage = NULL;
    GitCommitOptions_.Fixup = NULL;
    GitCommitOptions_.Squash = NULL;
    GitCommitOptions_.ResetAuthor = 0;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct GitCommitOptions_));
    (*(((struct GitCommitOptions_*)box_))) = GitCommitOptions_;
    return box_;
}

int main() {
    void* call_ = defaultOptions_(0);
    void* _options_ = call_;
    return 0;
}
