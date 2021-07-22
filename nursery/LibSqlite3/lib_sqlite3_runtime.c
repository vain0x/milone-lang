// sqlite3 adapter for milone-lang
// <https://www.sqlite.org/cintro.html>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../vendor/sqlite3/sqlite3.h"
#include <milone.h>

// -----------------------------------------------
// milone FFI?
// -----------------------------------------------

// memory layout is unstable.

enum DbValueDiscriminant { DNull, DString, DInt };

struct DbValue {
    enum DbValueDiscriminant discriminant;

    union {
        struct String DString;
        int DInt;
    };
};

struct DbValueCons {
    struct DbValue head;
    struct DbValueCons const *tail;
};

struct DbValueListCons {
    struct DbValueCons const *head;
    struct DbValueListCons const *tail;
};

struct StringDbValuePair {
    struct String t0;
    struct DbValue t1;
};

struct StringDbValuePairCons {
    struct StringDbValuePair head;
    struct StringDbValuePairCons const *tail;
};

// -----------------------------------------------
// sqlite3
// -----------------------------------------------

// FIXME: avoid static variable
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
    sqlite3_close(s_db); // OK: No-op if null.
    s_db = NULL;
}

void db_open(struct String filename) {
    filename = str_ensure_null_terminated(filename);

    assert(s_db == NULL && "can't db_open twice");

    sqlite3 *db;
    bool ok = sqlite3_open(filename.str, &db) == 0;
    if (!ok) {
        fprintf(stderr, "error: Can't open database: '%s'.\n", filename.str);
        exit(1);
    }

    s_db = db;
    atexit(db_close);
}

static void db_bind_params(sqlite3_stmt *stmt,
                           struct StringDbValuePairCons const *params) {
    for (struct StringDbValuePairCons const *p = params; p != NULL;
         p = p->tail) {
        struct String key = p->head.t0;
        struct DbValue value = p->head.t1;

        int i = sqlite3_bind_parameter_index(stmt, str_to_c_str(key));
        if (i == 0) {
            db_fail(str_to_c_str(str_add(str_borrow("Unknown variable: "), key)));
        }

        switch (value.discriminant) {
        case DNull: {
            bool ok = sqlite3_bind_null(stmt, i) == SQLITE_OK;
            assert(ok && "bind_null");
            break;
        }
        case DString: {
            bool ok =
                sqlite3_bind_text(stmt, i, value.DString.str, value.DString.len,
                                  SQLITE_STATIC) == SQLITE_OK;
            assert(ok && "bind_text");
            break;
        }
        case DInt: {
            bool ok = sqlite3_bind_int(stmt, i, value.DInt) == SQLITE_OK;
            assert(ok && "bind_int");
            break;
        }
        default:
            db_fail("discriminant");
        }
    }
}

static struct DbValueCons const *db_read_row(sqlite3_stmt *stmt) {
    int n = sqlite3_column_count(stmt);
    if (n == 0) {
        return NULL;
    }

    struct DbValueCons *cons = milone_mem_alloc(n, sizeof(struct DbValueCons));

    for (int i = 0; i < n; i++) {
        int ty = sqlite3_column_type(stmt, i);
        struct DbValue d;
        switch (ty) {
        case SQLITE3_TEXT: {
            unsigned char const *s = sqlite3_column_text(stmt, i);
            assert(s != NULL);
            d = (struct DbValue){.discriminant = DString,
                                 .DString = str_of_c_str((char const *)s)};
            break;
        }
        case SQLITE_INTEGER: {
            int value = sqlite3_column_int(stmt, i);
            d = (struct DbValue){.discriminant = DInt, .DInt = value};
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

// Execute a statement to read data and return a list of rows.
struct DbValueListCons const *
db_select(struct String sql, struct StringDbValuePairCons const *params) {
    sqlite3 *db = s_db;
    assert(db != NULL && "db not open");

    sqlite3_stmt *stmt = NULL;
    bool ok = sqlite3_prepare(db, str_to_c_str(sql), sql.len, &stmt, NULL) == SQLITE_OK;
    if (!ok) {
        db_fail("prepare");
    }

    db_bind_params(stmt, params);

    size_t cap = 16;
    size_t len = 0;
    struct DbValueCons const **table = malloc(cap * sizeof(struct DbValueCons const *));

    while (true) {
        int stat = sqlite3_step(stmt);
        switch (stat) {
        case SQLITE_DONE:
            break;

        case SQLITE_BUSY:
            // FIXME: rollback
            fprintf(stderr, "busy.\n");
            break;

        case SQLITE_ROW: {
            if (len == cap) {
                cap *= 2;
                table = realloc(table, cap * sizeof(struct DbValueCons const *));
            }
            table[len] = db_read_row(stmt);
            len++;
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

    // Array to list.
    struct DbValueListCons *result = NULL;
    if (len != 0) {
        result = milone_mem_alloc((int)len, sizeof(struct DbValueListCons));
        for (size_t i = 0; i < len; i++) {
            result[i].head = table[i];
            result[i].tail = i + 1 < len ? &result[i + 1] : NULL;
        }
    }
    free(table);
    return result;
}

// Execute a statement that mutates the database. (insert etc.)
void db_mutate(struct String sql, struct StringDbValuePairCons const *params) {
    sqlite3 *db = s_db;
    assert(db != NULL && "db not open");

    sqlite3_stmt *stmt = NULL;
    bool ok = sqlite3_prepare(db, str_to_c_str(sql), sql.len, &stmt, NULL) == SQLITE_OK;
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
            // FIXME: rollback
            fprintf(stderr, "busy.\n");
            break;

        case SQLITE_ROW: {
            int n = sqlite3_column_count(stmt);
            fprintf(stderr, "warn: row (%d) discarded.\n", n);
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

// Execute statements in batch.
void db_exec(struct String sql) {
    sqlite3 *db = s_db;
    assert(db != NULL && "db not open");

    bool ok =
        sqlite3_exec(db, str_to_c_str(sql), NULL, NULL, NULL) == SQLITE_OK;
    if (!ok) {
        db_fail("exec");
    }
}
