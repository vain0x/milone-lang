#include <assert.h>
#include <gtk/gtk.h>
#include <milone.h>

// -----------------------------------------------
// Milone
// -----------------------------------------------

struct ObjectObjectFun1 {
    void const *(*fun)(void const *, void const *);
    void const *env;
};

struct ObjectObjectObjectFun2 {
    void const *(*fun)(void const *, void const *, void const *);
    void const *env;
};

void str_error(struct String s) {
    fprintf(stderr, "error: %s\n", str_to_c_str(s));
}

// -----------------------------------------------
// MyState
// -----------------------------------------------

static bool same_ptr(void const *l, void const *r) {
    if (l == r) {
        fprintf(stderr, "same: %p\n", l);
        return true;
    }
    return false;
}

struct IntOption {
    bool some;
    int value;
};

struct IntOptionList {
    struct IntOption head;
    struct IntOptionList *tail;
};

struct MyState_ {
    int t0;
    struct IntOptionList *t1;
    struct IntOptionList *t2;
};

// struct PtrChain {
//     void const *ptr;
//     struct PtrChain *prev;
//     struct PtrChain *next;
// };

// static struct PtrChain *s_chain = NULL;

// static bool p_find(void const *p, struct PtrChain **out_chain) {
//     assert(p != NULL);

//     for (struct PtrChain *c = s_chain; c != NULL; c = c->next) {
//         if (c->ptr == p) {
//             *out_chain = c;
//             return true;
//         }
//     }

//     *out_chain = NULL;
//     return false;
// }

// static bool is_promoted(void const *p) {
//     struct PtrChain *c;
//     return p != NULL && p_find(p, &c);
// }

// static void p_link(void *p) {
//     assert(p != NULL);
//     assert(!is_promoted(p));

//     struct PtrChain *c = malloc(sizeof(struct PtrChain));
//     *c = (struct PtrChain){.ptr = p, .prev = NULL, .next = s_chain};
//     s_chain = c;
// }

// static void p_unlink(void *p) {
//     if (p == NULL) {
//         return;
//     }

//     struct PtrChain *c;
//     if (!p_find(p, &c)) {
//         return;
//     }

//     // Fix links.
//     if (c->prev != NULL) {
//         assert(c->prev->next == c);
//         c->prev->next = c->next;
//     }
//     if (c->next != NULL) {
//         assert(c->next->prev == c);
//         c->next->prev = c->prev;
//     }
//     if (c == s_chain) {
//         s_chain = c->next;
//     }

//     free(c);
// }

static void promote_int_option_list(struct IntOptionList **old_ptr,
                                    struct IntOptionList *const *new_ptr);

static struct IntOptionList *allocate_cons(struct IntOption head,
                                           struct IntOptionList *tail) {
    struct IntOptionList *cons = malloc(sizeof(struct IntOptionList));
    cons->head = head;
    cons->tail = NULL; // set default
    fprintf(stderr, "new cons: %p\n", cons);

    // Can't do `cons->tail = tail` because tail is not promoted.
    promote_int_option_list(&cons->tail, &tail);
    return cons;
}

static void free_cons(struct IntOptionList *cons) {
    fprintf(stderr, "free cons: %p\n", cons);
    free(cons);
}

static void promote_int_option_list(struct IntOptionList **old_ptr,
                                    struct IntOptionList *const *new_ptr) {
    if (same_ptr(old_ptr, new_ptr)) {
        return;
    }

    // free or (_, nil) | ((some x, some y) when x <> y)
    if (new_ptr == NULL || *new_ptr == NULL) {
        if (*old_ptr != NULL) {
            // free head: pass.

            // free tail
            promote_int_option_list(&(*old_ptr)->tail, NULL);

            // free cons
            free_cons(*old_ptr);
            *old_ptr = NULL;
        }
        return;
    }

    // nil, cons
    if (*old_ptr == NULL) {
        assert(*new_ptr != NULL);
        *old_ptr = allocate_cons((*new_ptr)->head, (*new_ptr)->tail);
        return;
    }

    // cons, cons
    assert(*old_ptr != NULL);
    assert(*new_ptr != NULL);

    // promote head (just copy);
    (*old_ptr)->head = (*new_ptr)->head;

    // promote tail
    promote_int_option_list(&(*old_ptr)->tail, &(*new_ptr)->tail);
}

static void promote_my_state(struct MyState_ *old_ptr,
                             struct MyState_ const *new_ptr) {
    if (same_ptr(old_ptr, new_ptr)) {
        return;
    }

    // free each field
    if (new_ptr == NULL) {
        promote_int_option_list(&old_ptr->t1, NULL);
        return;
    }

    // promote each field
    old_ptr->t0 = new_ptr->t0;
    promote_int_option_list(&old_ptr->t1, &new_ptr->t1);
    promote_int_option_list(&old_ptr->t2, &new_ptr->t2);
}

struct MyStateOption {
    bool some;
    struct MyState_ value;
};

static void promote_my_state_option(struct MyStateOption *old_ptr,
                                    struct MyStateOption const *new_ptr) {
    if (same_ptr(old_ptr, new_ptr)) {
        return;
    }

    // free
    if (new_ptr == NULL) {
        if (old_ptr->some) {
            old_ptr->some = false;
            promote_my_state(&old_ptr->value, NULL);
        }
        return;
    }

    // none vs. none
    if (!old_ptr->some && !new_ptr->some) {
        return;
    }

    // some vs. none
    if (old_ptr->some && !new_ptr->some) {
        old_ptr->some = false;
        promote_my_state(&old_ptr->value, NULL);
        return;
    }

    // none vs. some
    if (!old_ptr->some) {
        assert(new_ptr->some);

        old_ptr->some = true;
        old_ptr->value = (struct MyState_){.t0 = 0, .t1 = NULL}; // set default
        promote_my_state(&old_ptr->value, &new_ptr->value);
        return;
    }

    // some vs. some
    promote_my_state(&old_ptr->value, &new_ptr->value);
}

// -----------------------------------------------
// GTK
// -----------------------------------------------

typedef struct ObjectObjectObjectFun2 UpdateFn;
typedef struct ObjectObjectFun1 ViewFn;

static GtkApplication *s_app;
static void const *s_state;
static UpdateFn s_update;
static ViewFn s_view;

static int s_msg = 0;

static GtkWidget *s_grid;

static void const *s_ui;

static void update_view(void) {
    fprintf(stderr, "trace: update_view\n");
    s_view.fun(s_view.env, s_state);
}

static void on_button_clicked(GtkWidget *button, gpointer data) {
    fprintf(stderr, "trace: on_button_clicked data=%p\n", data);
    int msg = (int)(uintptr_t)data;

    s_state = s_update.fun(s_update.env, s_state, &msg);
    update_view();
}

void milone_gtk_set_view(void const *ui) {
    fprintf(stderr, "trace: set_view %p -> %p\n", s_ui, ui);
    s_ui = ui;
}

void const *milone_gtk_get_view(void) {
    fprintf(stderr, "trace: get_view %p\n", s_ui);
    return s_ui;
}

void milone_gtk_apply_diff(struct String diff_string) {
    GtkWidget *grid = s_grid;

    char *diff = strdup(str_to_c_str(diff_string));
    char *tok = NULL;
    char const *delim = " \r\n";

    while (true) {
        char *s = strtok_r(diff, delim, &tok);
        if (s == NULL) {
            break;
        }

        // Non-first call to strtok_r should pass NULL as first argument.
        diff = NULL;

        fprintf(stderr, "tok: '%s' (%ld)\n", s, strlen(s));

        if (strcmp(s, "ADD_LABEL") == 0) {
            int index = str_to_int(str_borrow(strtok_r(NULL, delim, &tok)));
            char const *text = strtok_r(NULL, delim, &tok);
            fprintf(stderr, "trace: add_label index=%d text=%s\n", index, text);

            GtkWidget *label = gtk_label_new(text);
            gtk_grid_attach(GTK_GRID(grid), label, 0, index, 1, 1);

            gtk_widget_show(label);
            continue;
        }

        if (strcmp(s, "ADD_BUTTON") == 0) {
            int index = str_to_int(str_borrow(strtok_r(NULL, delim, &tok)));
            int msg = str_to_int(str_borrow(strtok_r(NULL, delim, &tok)));
            char const *text = strtok_r(NULL, delim, &tok);

            GtkWidget *button = gtk_button_new_with_label(text);
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked),
                             (gpointer)(uintptr_t)msg);
            gtk_grid_attach(GTK_GRID(grid), button, 0, index, 1, 1);

            gtk_widget_show(button);
            continue;
        }

        if (strcmp(s, "SET_LABEL") == 0) {
            int index = str_to_int(str_borrow(strtok_r(NULL, delim, &tok)));
            char const *text = strtok_r(NULL, delim, &tok);
            fprintf(stderr, "trace: set_label index=%d text=%s\n", index, text);

            GtkWidget *label = gtk_grid_get_child_at(GTK_GRID(grid), 0, index);
            gtk_label_set_text(GTK_LABEL(label), text);
            continue;
        }

        fprintf(stderr, "unknown msg: '%s' (%ld)\n", s, strlen(s));
        break;
    }
}

static void activate(GtkApplication *app, gpointer _data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello GTK App");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    s_grid = grid;

    update_view();
    gtk_widget_show_all(window);
}

static void dump(struct MyStateOption const *s) {
    if (!s->some) {
        fprintf(stderr, "state = None.\n");
        return;
    }

    fprintf(stderr, "state = Some\n");
    fprintf(stderr, "  {.t0 = %d,\n", s->value.t0);

    for (int i = 0; i < 2; i++) {
        struct IntOptionList const *xs = i == 0 ? s->value.t1 : s->value.t2;
        if (xs == NULL) {
            fprintf(stderr, "   .t%d = []\n", i + 1);
        } else {
            fprintf(stderr, "   .t%d =        %p\n", i + 1, xs);
            char const *prefix = "[";

            for (; xs != NULL; xs = xs->tail) {
                char const *sep = xs->tail == NULL ? " ]" : "";
                if (xs->head.some) {
                    fprintf(stderr, "    %s Some %d%s      -> %p\n", prefix,
                            xs->head.value, sep, xs->tail);
                } else {
                    fprintf(stderr, "    %s None%s      -> %p\n", prefix, sep,
                            xs->tail);
                }

                prefix = " ";
            }
        }
    }
    fprintf(stderr, "  }\n");
}

int app_main(void const *init, UpdateFn update, ViewFn view) {
    // s_state = init;
    // s_update = update;
    // s_view = view;

    // GtkApplication *app =
    //     gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    // s_app = app;

    // g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // int status = g_application_run(G_APPLICATION(app), 0, NULL);
    // s_app = NULL;
    // g_object_unref(app);
    // return status;

    static struct MyStateOption state = {.some = false};
    {
        struct MyStateOption s = {true, {.t0 = 42, .t1 = NULL}};
        promote_my_state_option(&state, &s);
    }
    dump(&state);
    {
        struct MyStateOption s = state;
        struct IntOptionList cons = {.head = {.some = true, .value = 42},
                                     .tail = NULL};
        s.value.t1 = &cons;
        promote_my_state_option(&state, &s);
    }
    dump(&state);
    {
        struct MyStateOption s = state;
        struct IntOptionList cons = {.head = {.some = true, .value = 42},
                                     .tail = s.value.t1};
        s.value.t1 = &cons;
        promote_my_state_option(&state, &s);
    }
    dump(&state);

    promote_my_state_option(&state, NULL);
    dump(&state);
    return 0;
}
