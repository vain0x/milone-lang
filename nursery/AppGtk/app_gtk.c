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

int app_main(void const *init, UpdateFn update, ViewFn view) {
    s_state = init;
    s_update = update;
    s_view = view;

    GtkApplication *app =
        gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    s_app = app;

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), 0, NULL);
    s_app = NULL;
    g_object_unref(app);
    return status;
}
