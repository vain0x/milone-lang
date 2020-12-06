#include "milone.h"

struct StringList;

struct GitCommitOptions_;

void const* defaultOptions_(int arg_);

int main();

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct GitCommitOptions_ {
    bool All;
    bool Patch;
    struct StringList const* ReuseMessage;
    struct StringList const* ReeditMessage;
    struct StringList const* Fixup;
    struct StringList const* Squash;
    bool ResetAuthor;
};

void const* defaultOptions_(int arg_) {
    struct GitCommitOptions_ GitCommitOptions_;
    GitCommitOptions_.All = false;
    GitCommitOptions_.Patch = false;
    GitCommitOptions_.ReuseMessage = NULL;
    GitCommitOptions_.ReeditMessage = NULL;
    GitCommitOptions_.Fixup = NULL;
    GitCommitOptions_.Squash = NULL;
    GitCommitOptions_.ResetAuthor = false;
    void const* box_ = milone_mem_alloc(1, sizeof(struct GitCommitOptions_));
    (*(((struct GitCommitOptions_*)box_))) = GitCommitOptions_;
    return box_;
}

int main() {
    void const* call_ = defaultOptions_(0);
    void const* _options_ = call_;
    return 0;
}
