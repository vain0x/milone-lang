#include "milone.h"

struct Person_;

int main();

struct Person_ {
    struct String Name;
    int Age;
};

int main() {
    struct Person_ Person_;
    Person_.Name = (struct String){.str = "John Doe", .len = 8};
    Person_.Age = 16;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct Person_));
    (*(((struct Person_*)box_))) = Person_;
    void* john_ = box_;
    void* base_ = john_;
    struct Person_ Person_1;
    Person_1.Name = (struct String){.str = "Jane Doe", .len = 8};
    Person_1.Age = (*(((struct Person_*)base_))).Age;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct Person_));
    (*(((struct Person_*)box_1))) = Person_1;
    void* jane_ = box_1;
    milone_assert((str_cmp((*(((struct Person_*)john_))).Name, (struct String){.str = "John Doe", .len = 8}) == 0), 8, 2);
    int call_ = 0;
    milone_assert((str_cmp((*(((struct Person_*)jane_))).Name, (struct String){.str = "Jane Doe", .len = 8}) == 0), 9, 2);
    int call_1 = 0;
    milone_assert(((*(((struct Person_*)jane_))).Age == 16), 10, 2);
    int call_2 = 0;
    void* base_1 = john_;
    struct Person_ Person_2;
    Person_2.Name = (*(((struct Person_*)base_1))).Name;
    Person_2.Age = ((*(((struct Person_*)john_))).Age + 1);
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct Person_));
    (*(((struct Person_*)box_2))) = Person_2;
    void* john_1 = box_2;
    milone_assert(((*(((struct Person_*)john_1))).Age == 17), 13, 2);
    int call_3 = 0;
    return 0;
}
