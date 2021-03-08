#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../vendor/pdjson/pdjson.h"
#include <milone.h>

// -----------------------------------------------
// milone FFI?
// -----------------------------------------------

// memory layout is unstable.

enum JsonValueDiscriminant {
    JNull,
    JString,
    JNumber,
    JBoolean,
    JArray,
    JObject,
};

struct JsonValue {
    enum JsonValueDiscriminant discriminant;
    union {
        struct String JString;
        double JNumber;
        bool JBoolean;
        struct JsonValueCons const *JArray;
        struct JsonEntryCons const *JObject;
    };
};

struct JsonValueCons {
    struct JsonValue head;
    struct JsonValueCons const *tail;
};

struct JsonEntry {
    struct String t0;
    struct JsonValue t1;
};

struct JsonEntryCons {
    struct JsonEntry head;
    struct JsonEntryCons const *tail;
};

// -----------------------------------------------
// JSON parsing
// -----------------------------------------------

static bool json_parse_to_value(json_stream *json, struct JsonValue *output) {
    enum json_type t = json_next(json);
    switch (t) {
    case JSON_ERROR:
    case JSON_DONE:
    case JSON_OBJECT_END:
    case JSON_ARRAY_END:
        return false;

    case JSON_OBJECT: {
        struct JsonEntryCons const *list = NULL;

        while (true) {
            enum json_type t = json_next(json);
            if (t == JSON_OBJECT_END) {
                break;
            }
            if (t != JSON_STRING) {
                return false;
            }
            size_t len;
            char const *s = json_get_string(json, &len);
            assert(len >= 1 && s[len - 1] == '\0');
            len--; // Exclude the null byte.
            struct String key = str_of_raw_parts(s, (int)len);

            struct JsonValue value;
            if (!json_parse_to_value(json, &value)) {
                return false;
            }

            struct JsonEntryCons *cons =
                milone_mem_alloc(1, sizeof(struct JsonEntryCons));
            *cons = (struct JsonEntryCons){
                .head = (struct JsonEntry){.t0 = key, .t1 = value},
                .tail = list};
            list = cons;
            continue;
        }

        *output = (struct JsonValue){.discriminant = JObject, .JObject = list};
        return true;
    }
    case JSON_ARRAY: {
        struct JsonValueCons const *list = NULL;

        while (json_peek(json) != JSON_ARRAY_END) {
            struct JsonValue item;
            if (!json_parse_to_value(json, &item)) {
                return false;
            }

            struct JsonValueCons *cons =
                milone_mem_alloc(1, sizeof(struct JsonValueCons));
            *cons = (struct JsonValueCons){.head = item, .tail = list};
            list = cons;
            continue;
        }
        json_next(json); // Skip ']'.

        *output = (struct JsonValue){
            .discriminant = JArray,
            .JArray = list,
        };
        return true;
    }
    case JSON_STRING: {
        size_t len = 0;
        char const *s = json_get_string(json, &len);
        assert(len >= 1 && s[len - 1] == '\0');
        len--; // Exclude the null byte.
        struct String value = str_of_raw_parts(s, (int)len);

        *output = (struct JsonValue){.discriminant = JString, .JString = value};
        return true;
    }
    case JSON_NUMBER: {
        double value = json_get_number(json);
        *output = (struct JsonValue){
            .discriminant = JNumber,
            .JNumber = value,
        };
        return true;
    }
    case JSON_TRUE: {
        *output =
            (struct JsonValue){.discriminant = JBoolean, .JBoolean = true};
        return true;
    }
    case JSON_FALSE: {
        *output =
            (struct JsonValue){.discriminant = JBoolean, .JBoolean = false};
        return true;
    }
    case JSON_NULL: {
        *output = (struct JsonValue){.discriminant = JNull};
        return true;
    }
    default:
        assert(false && "unknown json_type");
    }
}

struct JsonValue json_parse_from_string(struct String s) {
    json_stream json = {};
    json_open_buffer(&json, str_to_c_str(s), s.len);
    json_set_streaming(&json, false);

    struct JsonValue value;
    if (!json_parse_to_value(&json, &value)) {
        fprintf(stderr, "error: json_parse: %s\n", json_get_error(&json));
        json_close(&json);
        exit(1);
    }

    json_close(&json);
    return value;
}
