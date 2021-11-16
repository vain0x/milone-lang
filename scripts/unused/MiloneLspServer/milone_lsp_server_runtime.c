#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vendor/pdjson/pdjson.h"
#include "vendor/sqlite3/sqlite3.h"
#include <milone.h>

static struct String str_of_c_str(char const *s) {
    return str_of_raw_parts(s, strlen(s));
}

// -----------------------------------------------
// milone FFI?
// -----------------------------------------------

// memory layout is unstable.

struct UnitIntFun1 {
    int (*fun)(void const *env, char unit);
    void const *env;
};

// -----------------------------------------------
// JSON parsing
// -----------------------------------------------

enum JsonValue_Discriminant {
    JNull_,
    JString_,
    JNumber_,
    JBoolean_,
    JArray_,
    JObject_,
};

struct JsonValue_ {
    enum JsonValue_Discriminant discriminant;
    union {
        struct String JString_;
        double JNumber_;
        bool JBoolean_;
        struct JsonValue_List const *JArray_;
        struct StringJsonValue_Tuple2List const *JObject_;
    };
};

struct JsonValue_List {
    struct JsonValue_ head;
    struct JsonValue_List const *tail;
};

struct StringJsonValue_Tuple2 {
    struct String t0;
    struct JsonValue_ t1;
};

struct StringJsonValue_Tuple2List {
    struct StringJsonValue_Tuple2 head;
    struct StringJsonValue_Tuple2List const *tail;
};

typedef struct StringJsonValue_Tuple2 JsonEntry;
typedef struct StringJsonValue_Tuple2List JsonEntryCons;
typedef struct JsonValue_List JsonItemCons;
typedef struct JsonValue_ JsonValue;

typedef enum json_type json_type;

static bool json_parse_value(json_stream *json, JsonValue *output) {
    json_type t = json_next(json);
    switch (t) {
    case JSON_ERROR:
    case JSON_DONE:
    case JSON_OBJECT_END:
    case JSON_ARRAY_END:
        return false;

    case JSON_OBJECT: {
        JsonEntryCons const *list = NULL;

        while (true) {
            json_type t = json_next(json);
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

            JsonValue value;
            if (!json_parse_value(json, &value)) {
                return false;
            }

            JsonEntryCons *cons = milone_mem_alloc(1, sizeof(JsonEntryCons));
            *cons = (JsonEntryCons){.head = (JsonEntry){.t0 = key, .t1 = value},
                                    .tail = list};
            list = cons;
            continue;
        }

        *output = (JsonValue){.discriminant = JObject_, .JObject_ = list};
        return true;
    }
    case JSON_ARRAY: {
        JsonItemCons const *list = NULL;

        while (json_peek(json) != JSON_ARRAY_END) {
            JsonValue item;
            if (!json_parse_value(json, &item)) {
                return false;
            }

            JsonItemCons *cons = milone_mem_alloc(1, sizeof(JsonItemCons));
            *cons = (JsonItemCons){.head = item, .tail = list};
            list = cons;
            continue;
        }
        json_next(json);

        *output = (JsonValue){
            .discriminant = JArray_,
            .JArray_ = list,
        };
        return true;
    }
    case JSON_STRING: {
        size_t len = 0;
        char const *s = json_get_string(json, &len);
        assert(len >= 1 && s[len - 1] == '\0');
        len--; // Exclude the null byte.
        struct String value = str_of_raw_parts(s, (int)len);

        *output = (JsonValue){.discriminant = JString_, .JString_ = value};
        return true;
    }
    case JSON_NUMBER: {
        double value = json_get_number(json);
        *output = (JsonValue){
            .discriminant = JNumber_,
            .JNumber_ = value,
        };
        return true;
    }
    case JSON_TRUE: {
        *output = (JsonValue){.discriminant = JBoolean_, .JBoolean_ = true};
        return true;
    }
    case JSON_FALSE: {
        *output = (JsonValue){.discriminant = JBoolean_, .JBoolean_ = false};
        return true;
    }
    case JSON_NULL: {
        *output = (JsonValue){.discriminant = JNull_};
        return true;
    }
    default:
        assert(false && "unknown json_type");
    }
}

JsonValue json_parse_string(struct String s) {
    json_stream json = {};
    json_open_buffer(&json, str_to_c_str(s), s.len);
    json_set_streaming(&json, false);

    JsonValue value;
    if (!json_parse_value(&json, &value)) {
        fprintf(stderr, "error: json_parse: %s\n", json_get_error(&json));
        json_close(&json);
        exit(1);
    }

    json_close(&json);
    return value;
}

// -----------------------------------------------
// JSON writing
// -----------------------------------------------

// -----------------------------------------------
// standard IO
// -----------------------------------------------

struct String io_read_line(void) {
    char buf[4096] = {};

    bool ok = fgets(buf, sizeof(buf), stdin) != NULL;
    if (!ok) {
        return str_borrow("");
    }

    return str_of_raw_parts(buf, (int)strlen(buf));
}

struct String io_read_block(int len) {
    char *buf = milone_mem_alloc(len + 1, sizeof(char));

    bool ok = fread(buf, (size_t)len, 1, stdin) == 1;
    if (!ok) {
        fprintf(stderr, "error: fread: %d\n", len);
        exit(1);
    }

    return (struct String){.str = buf, .len = len};
}

// -----------------------------------------------
// Concurrency
// -----------------------------------------------

// experimental

void *thread_entrypoint(void *arg) {
    struct UnitIntFun1 const *f = arg;
    int result = f->fun(f->env, 0);
    return (void *)(intptr_t)result;
}

int concurrently(struct UnitIntFun1 worker1, struct UnitIntFun1 worker2) {
    printf("Before Thread\n");

    pthread_t t1;
    bool ok = pthread_create(&t1, NULL, thread_entrypoint, &worker1) == 0;
    assert(ok);

    pthread_t t2;
    ok = pthread_create(&t2, NULL, thread_entrypoint, &worker2) == 0;
    assert(ok);

    void *result1;
    void *result2;
    bool ok1 = pthread_join(t1, &result1);
    bool ok2 = pthread_join(t2, &result2);

    assert(ok1 && ok2);
    printf("After Thread\n");

    printf("result: %p, %p\n", result1, result2);
    return 0;
}

// -----------------------------------------------
// sqlite
// -----------------------------------------------

static sqlite3 *s_db = NULL;

_Noreturn static void db_fail(char const *msg) {
    sqlite3 *db = s_db;
    if (db != NULL) {
        fprintf(stderr, "error: %s: '%s'.\n", msg, sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "error: %s.\n", msg);
    }
    exit(1);
}

static void db_close(void) {
    if (s_db != NULL) {
        sqlite3_close(s_db);
        s_db = NULL;
    }
}

void db_open(struct String filename) {
    assert(s_db == NULL);

    sqlite3 *db;
    char const *name = str_to_c_str(filename);
    bool ok = sqlite3_open(name, &db) == 0;
    if (!ok) {
        fprintf(stderr, "error: Can't open database: '%s'.\n", name);
        exit(1);
    }

    s_db = db;
    atexit(db_close);
}

enum DbValueDiscriminant { DNull, DInt, DString };

struct DbValue {
    enum DbValueDiscriminant discriminant;

    union {
        int DInt;
        struct String DString;
    };
};

struct DbValueList {
    struct DbValue head;
    struct DbValueList const *tail;
};

struct DbValueListList {
    struct DbValueList const *head;
    struct DbValueListList const *tail;
};

struct StringDbValuePair {
    struct String t0;
    struct DbValue t1;
};

struct StringDbValuePairList {
    struct StringDbValuePair head;
    struct StringDbValuePairList const *tail;
};

static void db_bind_params(sqlite3_stmt *stmt,
                           struct StringDbValuePairList const *params) {
    for (struct StringDbValuePairList const *p = params; p != NULL;
         p = p->tail) {
        struct String key = p->head.t0;
        struct DbValue value = p->head.t1;

        int i = sqlite3_bind_parameter_index(stmt, str_to_c_str(key));
        if (i == 0) {
            db_fail("index");
        }

        switch (value.discriminant) {
        case DInt: {
            bool ok = sqlite3_bind_int(stmt, i, value.DInt) == SQLITE_OK;
            assert(ok && "bind_int");
            break;
        }
        case DString: {
            bool ok =
                sqlite3_bind_text(stmt, i, value.DString.str, value.DString.len,
                                  SQLITE_STATIC) == SQLITE_OK;
            assert(ok && "bind_text");
            break;
        }
        default:
            db_fail("discriminant");
        }
    }
}

static struct DbValueList const *db_read_row(sqlite3_stmt *stmt) {
    int n = sqlite3_column_count(stmt);
    if (n == 0) {
        return NULL;
    }

    struct DbValueList *cons = milone_mem_alloc(n, sizeof(struct DbValueList));

    for (int i = 0; i < n; i++) {
        int ty = sqlite3_column_type(stmt, i);
        struct DbValue d;
        switch (ty) {
            case SQLITE_INTEGER: {
                int value = sqlite3_column_int(stmt, i);
                d = (struct DbValue){.discriminant = DInt, .DInt = value};
                break;
            }
            case SQLITE3_TEXT: {
                unsigned char const *s = sqlite3_column_text(stmt, i);
                assert(s != NULL);
                d = (struct DbValue){.discriminant = DString, .DString = str_of_c_str((char const *)s)};
                break;
            }
            default:
                if (ty != SQLITE_NULL) {
                    db_fail("unsupported type");
                }
                d = (struct DbValue){.discriminant = DNull};
                break;
        }

        cons[i].head = d;
        cons[i].tail = i + 1 < n ? &cons[i + 1] : NULL;
    }
    return cons;
}

struct DbValueListList const *db_select(struct String sql, struct StringDbValuePairList const *params) {
    sqlite3 *db = s_db;
    assert(db != NULL);

    sqlite3_stmt *stmt = NULL;
    bool ok = sqlite3_prepare(db, str_to_c_str(sql), sql.len, &stmt, NULL) == 0;
    if (!ok) {
        db_fail("prepare");
    }

    db_bind_params(stmt, params);

    struct DbValueListList *result = NULL;

    while (true) {
        int stat = sqlite3_step(stmt);
        switch (stat) {
        case SQLITE_DONE:
            break;

        case SQLITE_BUSY:
            // do rollback.
            fprintf(stderr, "busy.\n");
            break;

        case SQLITE_ROW: {
            struct DbValueListList *cons = milone_mem_alloc(1, sizeof(struct DbValueListList));
            cons->head = db_read_row(stmt);
            cons->tail = result;
            result = cons;

            // int n = sqlite3_column_count(stmt);
            // fprintf(stderr, "row (%d):\n", n);

            // for (int i = 0; i < n; i++) {
            //     char const *key = sqlite3_column_name(stmt, i);
            //     unsigned char const *value = sqlite3_column_text(stmt, i);
            //     assert(key != NULL);
            //     assert(value != NULL);
            //     int ty = sqlite3_column_type(stmt, i);
            //     fprintf(stderr, "  %s: %s [%d]\n", key, value, ty);
            // }
            continue;
        }
        default:
            db_fail("step");
        }
        break;
    }

    fprintf(stderr, "done.\n");

    {
        bool ok = sqlite3_finalize(stmt) == SQLITE_OK;
        if (!ok) {
            db_fail("finalize");
        }
    }

    return result;
}

void db_mutate(struct String sql, struct StringDbValuePairList const *params) {
    sqlite3 *db = s_db;
    assert(db != NULL);

    fprintf(stderr, "mutate\n");
    sqlite3_stmt *stmt = NULL;
    bool ok = sqlite3_prepare(db, str_to_c_str(sql), sql.len, &stmt, NULL) == 0;
    if (!ok) {
        db_fail("prepare");
    }

    db_bind_params(stmt, params);

    while (true) {
        int stat = sqlite3_step(stmt);
        switch (stat) {
        case SQLITE_DONE:
            break;

        case SQLITE_BUSY:
            // do rollback.
            fprintf(stderr, "busy.\n");
            break;

        case SQLITE_ROW: {
            int n = sqlite3_column_count(stmt);
            fprintf(stderr, "row (%d) discarded.\n", n);
            continue;
        }
        default:
            db_fail("step");
        }
        break;
    }

    {
        bool ok = sqlite3_finalize(stmt) == SQLITE_OK;
        if (!ok) {
            db_fail("finalize");
        }
    }
}

void db_exec(struct String sql) {
    sqlite3 *db = s_db;
    assert(db != NULL);

    bool ok =
        sqlite3_exec(db, str_to_c_str(sql), NULL, NULL, NULL) == SQLITE_OK;
    if (!ok) {
        db_fail("exec");
    }
}

// int db_exec(struct String db_file, struct String sql) {
//     sqlite3 *db;
//     int stat = sqlite3_open(str_to_c_str(db_file), &db);
//     if (stat) {
//         fprintf(stderr, "error: Can't open database: '%s'.\n",
//                 sqlite3_errmsg(db));
//         sqlite3_close(db);
//         exit(1);
//     }

//     db_entry_count = 0;
//     char *error_message = NULL;
//     stat = sqlite3_exec(db, str_to_c_str(sql), callback, 0, &error_message);
//     if (stat != SQLITE_OK) {
//         fprintf(stderr, "error: SQL error: %s\n", error_message);
//         sqlite3_free(error_message);
//         sqlite3_close(db);
//         exit(1);
//     }

//     sqlite3_close(db);
//     return db_entry_count;
// }

int run_server(void) { return 0; }
