#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <milone.h>

#include "milone_cita.h"

// library code:

struct FieldValue {
    char value[32];
};

struct Row {
    struct FieldValue fields[32];
    int32_t field_count;
};

struct RowArray {
    struct Row *items;
    int32_t row_count;
    int32_t row_capacity;
};

// roughly parses csv
//
// DON'T USE THIS:
//      this is just for demonstration.
//      this isn't a serious parser, lack of features
//
// output buffer must be allocated by the caller, enough large to store all data.

static void parse_csv(char const *text, struct RowArray *out) {
    assert(out != NULL && out->row_capacity >= 1 &&
           out->row_count <= out->row_capacity && out->items != NULL &&
           out->items[out->row_capacity - 1].field_count >= 0);

    int32_t len;
    {
        size_t z = strlen(text);
        assert(z < ((size_t)1 << 31) || "too long");
        len = (int32_t)z;
    }
    int32_t i = 0;

    // parse rows
    int32_t row_count = out->row_count;
    assert(row_count >= 0);

    while (i < len) {
        assert(row_count < out->row_capacity && "not implemented");
        struct Row *row = &out->items[row_count];

        // parse fields
        int32_t field_count = 0;
        while (i < len && text[i] != '\n') {
            assert(field_count < 32 && "not implemented");

            int32_t l = i;
            while (i < len && text[i] != ',' && text[i] != '\n')
                i++;

            memcpy(&row->fields[field_count].value, &text[l], i - l);
            row->fields[field_count].value[i - l] = '\0';
            field_count++;

            if (i < len && text[i] == ',')
                i++;
        }

        if (i < len && text[i] == '\n')
            i++;

        row->field_count = field_count;
        row_count++;
    }

    assert(i == len);
    out->row_count = row_count;
}

// glue code:

struct CiData parse_csv_for_milone(struct String text) {
    struct Row row_data[32];
    memset(row_data, 0, sizeof(row_data));
    struct RowArray row_array = {
        .items = row_data,
        .row_count = 0,
        .row_capacity = 32};

    parse_csv(string_to_c_str(text), &row_array);

    // convert to cita value
    struct CiData *buf =
        milone_region_alloc(row_array.row_count, sizeof(struct CiData));
    for (int32_t i = 0; i < row_array.row_count; i++) {
        struct Row *row = &row_array.items[i];

        struct CiData *field_buf =
            milone_region_alloc(row->field_count, sizeof(struct CiData));
        for (int32_t x = 0; x < row->field_count; x++) {
            field_buf[x] = CiData_unsafeOfCString(row->fields[x].value);
        }

        buf[i] = CiData_unsafeWrapArray(
            (struct CiArray){.ptr = field_buf, .len = row->field_count});
    }
    return CiData_unsafeWrapArray(
        (struct CiArray){.ptr = buf, .len = row_array.row_count});
}
