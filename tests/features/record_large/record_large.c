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
    bool All;
    bool Patch;
    struct StringList* ReuseMessage;
    struct StringList* ReeditMessage;
    struct StringList* Fixup;
    struct StringList* Squash;
    bool ResetAuthor;
};

void* defaultOptions_(int arg_) {
    struct GitCommitOptions_ GitCommitOptions_;
    GitCommitOptions_.All = false;
    GitCommitOptions_.Patch = false;
    GitCommitOptions_.ReuseMessage = NULL;
    GitCommitOptions_.ReeditMessage = NULL;
    GitCommitOptions_.Fixup = NULL;
    GitCommitOptions_.Squash = NULL;
    GitCommitOptions_.ResetAuthor = false;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct GitCommitOptions_));
    (*(((struct GitCommitOptions_*)box_))) = GitCommitOptions_;
    return box_;
}

int main() {
    void* call_ = defaultOptions_(0);
    void* _options_ = call_;
    return 0;
}
