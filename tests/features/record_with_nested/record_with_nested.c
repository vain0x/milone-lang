#include "milone.h"

struct Date_;

struct Person_;

void* newPerson_(int arg_);

int main();

struct Date_ {
    int Year;
    int Month;
    int Date;
};

struct Person_ {
    struct String Name;
    int Age;
    void* Birthday;
};

void* newPerson_(int arg_) {
    struct Date_ Date_;
    Date_.Year = 2007;
    Date_.Month = 8;
    Date_.Date = 31;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct Date_));
    (*(((struct Date_*)box_))) = Date_;
    struct Person_ Person_;
    Person_.Name = (struct String){.str = "Jane Doe", .len = 8};
    Person_.Age = 16;
    Person_.Birthday = box_;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct Person_));
    (*(((struct Person_*)box_1))) = Person_;
    return box_1;
}

int main() {
    void* call_ = newPerson_(0);
    void* base_ = call_;
    struct Person_ Person_1;
    Person_1.Name = (struct String){.str = "John Doe", .len = 8};
    Person_1.Age = (*(((struct Person_*)base_))).Age;
    Person_1.Birthday = (*(((struct Person_*)base_))).Birthday;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct Person_));
    (*(((struct Person_*)box_2))) = Person_1;
    void* john_ = box_2;
    struct String name_ = (*(((struct Person_*)john_))).Name;
    milone_assert((name_.len == 8), 19, 2);
    return 0;
}
