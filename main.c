#include <stdio.h>
#include <string.h>
#include <gtk-3.0/gtk/gtk.h>

#include "include/ui.h"

int main(int argc, char *argv[])
{
    // Create a new application
    GtkApplication *app;
    app = gtk_application_new("com.team4", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
