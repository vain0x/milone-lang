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
    void* _john_ = box_;
    struct Person_ Person_1;
    Person_1.Name = (struct String){.str = "Jane Doe", .len = 8};
    Person_1.Age = 18;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct Person_));
    (*(((struct Person_*)box_1))) = Person_1;
    void* _jane_ = box_1;
    return 0;
}
