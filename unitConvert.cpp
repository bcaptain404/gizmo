#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>

void convert_button_clicked(GtkWidget *button, gpointer data) {
    GtkWidget *entry_input = GTK_WIDGET(data);
    const gchar *input_text = gtk_entry_get_text(GTK_ENTRY(entry_input));
    
    // Perform conversion logic here (e.g., convert to uppercase)
    gchar *converted_text = g_strdup(g_ascii_strup(input_text, strlen(input_text))); 
    
    GtkWidget *label_output = gtk_widget_get_parent(button); // Get the label widget
    gtk_label_set_text(GTK_LABEL(label_output), converted_text);
    
    g_free(converted_text);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *entry, *label, *button;
    
    gtk_init(&argc, &argv); 
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simple Converter");
    
    entry = gtk_entry_new();
    label = gtk_label_new("Output:"); 
    button = gtk_button_new_with_label("Convert"); 
    
    g_signal_connect(button, "clicked", G_CALLBACK(convert_button_clicked), entry); 
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    
    gtk_main();
    return 0;
}
