#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>

struct ClickCallbackDataT {
    GtkEntry *txt_in;
    GtkEntry *txt_out;
};

void convert_button_clicked(GtkWidget *button, gpointer data ) {
    ClickCallbackDataT * widgets = (ClickCallbackDataT*)(data);

    const gchar *input_text = gtk_entry_get_text(GTK_ENTRY(widgets->txt_in));
    
    gchar *converted_text = g_strdup(g_ascii_strup(input_text, strlen(input_text)));
    
    gtk_entry_set_text(widgets->txt_out, converted_text);
  
    g_free(converted_text);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); 
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect( window, "destroy", G_CALLBACK( gtk_main_quit), NULL ); 
    gtk_window_set_title(GTK_WINDOW(window), "Simple Converter");
    
    ClickCallbackDataT data;
    data.txt_in = (GtkEntry*)gtk_entry_new();
    data.txt_out = (GtkEntry*)gtk_entry_new();
    
    GtkWidget *button = gtk_button_new_with_label("Convert");

    g_signal_connect(button, "clicked", G_CALLBACK(convert_button_clicked), &data); 
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), (GtkWidget*)data.txt_in, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), (GtkWidget*)data.txt_out, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    gtk_main();
    //gtk_widget_destroy(window);
    return 0;
}
