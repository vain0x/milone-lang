// sqlite3 adapter for milone-lang (experimental)
// <https://www.sqlite.org/cintro.html>

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../vendor/sqlite3/sqlite3.h"
#include <milone.h>

// -----------------------------------------------
// milone types
// -----------------------------------------------

// WARNING: memory layout is unstable.

// these definitions happen to be correct because this source file is inside the
// repository and we know the implementation details of the compiler.

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

_Noreturn static void db_fail(struct sqlite3 *db, char const *msg) {
    if (db != NULL) {
        fprintf(stderr, "error: %s: %s\n", msg, sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "error: %s\n", msg);
    }
    exit(1);
}

// Open a database file.
//
// - pathname is typically `*.db`.
//      - Database file is created if missing.
//      - It can be `":memory:"` to create an in-memory database.
// - `p_error` can be null.
// - Return non-NULL pointer if success.
//      - Return NULL if error.
//      - Set `*p_error` if error and `p_error` isn't null.
struct sqlite3 *db_open(struct String pathname, struct String *p_error) {
    pathname = string_ensure_null_terminated(pathname);

    struct sqlite3 *db;
    if (sqlite3_open(pathname.ptr, &db) != 0) {
        if (p_error) {
            char buf[1024] = "";
            sprintf(buf, "error: Can't open as database: '%s'.\n",
                    pathname.ptr);
            *p_error = string_of_c_str(buf);
        }
        return NULL;
    }

    if (p_error) {
        *p_error = string_borrow("");
    }

    assert(db);
    return db;
}

// Close a database.
void db_close(struct sqlite3 *db) {
    sqlite3_close(db); // OK: No-op if null.
}

static bool db_bind_params(struct sqlite3 *db, sqlite3_stmt *stmt,
                           struct StringDbValuePairCons const *params) {
    for (struct StringDbValuePairCons const *p = params; p != NULL;
         p = p->tail) {
        struct String key = string_ensure_null_terminated(p->head.t0);
        struct DbValue value = p->head.t1;

        int i = sqlite3_bind_parameter_index(stmt, string_to_c_str(key));
        if (i == 0) {
            fprintf(stderr, "error: Unknown variable: %s.\n",
                    string_to_c_str(key));
            return false;
        }

        switch (value.discriminant) {
        case DNull: {
            bool ok = sqlite3_bind_null(stmt, i) == SQLITE_OK;
            assert(ok && "bind_null");
            break;
        }
        case DString: {
            bool ok =
                sqlite3_bind_text(stmt, i, value.DString.ptr, value.DString.len,
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
            db_fail(db, "DbValue.discriminant");
        }
    }
    return true;
}

static struct DbValueCons const *db_read_row(struct sqlite3 *db,
                                             sqlite3_stmt *stmt) {
    int n = sqlite3_column_count(stmt);
    if (n == 0) {
        return NULL;
    }

    struct DbValueCons *cons =
        milone_region_alloc(n, sizeof(struct DbValueCons));

    for (int i = 0; i < n; i++) {
        int ty = sqlite3_column_type(stmt, i);
        struct DbValue d;
        switch (ty) {
        case SQLITE3_TEXT: {
            unsigned char const *s = sqlite3_column_text(stmt, i);
            assert(s != NULL);
            d = (struct DbValue){.discriminant = DString,
                                 .DString = string_of_c_str((char const *)s)};
            break;
        }
        case SQLITE_INTEGER: {
            int value = sqlite3_column_int(stmt, i);
            d = (struct DbValue){.discriminant = DInt, .DInt = value};
            break;
        }
        default:
            if (ty != SQLITE_NULL) {
                db_fail(db, "unsupported type");
            }
            d = (struct DbValue){.discriminant = DNull};
            break;
        }

        cons[i].head = d;
        cons[i].tail = i + 1 < n ? &cons[i + 1] : NULL;
    }
    return cons;
}

// Execute a statement to read data.
//
// Return true if success. Set `p_rows` if success.
//
// - This function may fail due to non-exhaustive parameters.
bool db_select(struct sqlite3 *db, struct String sql,
               struct StringDbValuePairCons const *params,
               struct DbValueListCons const **p_rows) {
    assert(db && p_rows);

    bool success = false;
    struct DbValueListCons *rows = NULL;
    struct DbValueCons const **table = NULL;

    // Prepare.
    sqlite3_stmt *stmt;
    if (sqlite3_prepare(db, string_to_c_str(sql), sql.len, &stmt, NULL) !=
        SQLITE_OK) {
        db_fail(db, "sqlite3_prepare");
    }
    assert(stmt);

    if (!db_bind_params(db, stmt, params)) {
        return NULL;
    }

    // Retrieve results to table (array of lists).
    size_t cap = 64;
    size_t len = 0;
    table = calloc(cap, sizeof(struct DbValueCons *));
    if (!table) {
        goto FAIL;
    }

    while (true) {
        int stat = sqlite3_step(stmt);
        switch (stat) {
        case SQLITE_DONE:
            success = true;
            break;

        case SQLITE_BUSY:
            goto FAIL;

        case SQLITE_ROW: {
            if (len == cap) {
                cap *= 2;
                table = realloc(table, cap * sizeof(struct DbValueCons *));
                if (!table) {
                    goto FAIL;
                }
            }
            table[len] = db_read_row(db, stmt);
            len++;
            continue;
        }
        default:
            fprintf(stderr, "sqlite3_step: unhandled status %d\n", stat);
            goto FAIL;
        }
        break;
    }

    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        db_fail(db, "sqlite3_finalize");
    }

    // Convert array to list.
    if (len != 0) {
        rows = milone_region_alloc((int)len, sizeof(struct DbValueListCons));
        for (size_t i = 0; i < len; i++) {
            rows[i].head = table[i];
            rows[i].tail = i + 1 < len ? &rows[i + 1] : NULL;
        }
    }

FAIL:
    free(table);
    *p_rows = rows;
    return success;
}

// Execute a statement that mutates the database. (insert etc.)
//
// Return true if success.
bool db_mutate(struct sqlite3 *db, struct String sql,
               struct StringDbValuePairCons const *params) {
    assert(db);

    bool success = false;

    // Prepare.
    sqlite3_stmt *stmt;
    if (sqlite3_prepare(db, string_to_c_str(sql), sql.len, &stmt, NULL) !=
        SQLITE_OK) {
        db_fail(db, "sqlite3_prepare");
    }
    assert(stmt);

    if (!db_bind_params(db, stmt, params)) {
        goto FAIL;
    }

    // Process the statement.
    while (true) {
        int stat = sqlite3_step(stmt);
        switch (stat) {
        case SQLITE_DONE:
            success = true;
            break;

        case SQLITE_BUSY:
            goto FAIL;

        case SQLITE_ROW: {
            // db_mutate doesn't retrieve rows.
            // int n = sqlite3_column_count(stmt);
            // fprintf(stderr, "warn: row (%d) discarded.\n", n);
            continue;
        }
        default:
            fprintf(stderr, "sqlite3_step: unhandled status %d\n", stat);
            goto FAIL;
        }
        break;
    }

    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        db_fail(db, "finalize");
    }

FAIL:
    return success;
}

// Execute multiple statements in batch.
//
// Return true if success. Set error message (that is generated by sqlite3) to
// `*p_error` if failed.
bool db_exec(struct sqlite3 *db, struct String sql, struct String *p_error) {
    assert(db && p_error);

    bool ok =
        sqlite3_exec(db, string_to_c_str(sql), NULL, NULL, NULL) == SQLITE_OK;
    if (ok) {
        *p_error = string_borrow("");
    } else {
        *p_error = string_of_c_str(sqlite3_errmsg(db));
    }

    return ok;
}
