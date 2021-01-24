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

static GtkWidget *s_label;

static void update_view(void) {
    struct String value =
        *(struct String const *)s_view.fun(s_view.env, s_state);
    gtk_label_set_text(GTK_LABEL(s_label), str_to_c_str(value));
}

static void on_button_clicked(GtkWidget *button, gpointer _data) {
    s_state = s_update.fun(s_update.env, s_state, &s_msg);
    update_view();
}

static void activate(GtkApplication *app, gpointer _data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello GTK App");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    // gtk_container_add(GTK_CONTAINER(window), button_box);

    GtkWidget *button = gtk_button_new_with_label("Hello World");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    // gtk_container_add(GTK_CONTAINER(button_box), button);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    GtkWidget *label = gtk_label_new("0");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    s_label = label;

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
