#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <iostream>
extern "C" {
    #include <xdo.h>
}
#include <string>


constexpr const char *WINDOW_NAME="Weight Unit Converter";
constexpr const float G_TO_OZ = 28.3495;
constexpr const float OZ_TO_G = 1/G_TO_OZ;
constexpr const float LB_TO_OZ = 16;
constexpr const float OZ_TO_LB = 1/LB_TO_OZ;

struct ClickCallbackDataT {
    GtkEntry *txt_oz;
    GtkEntry *txt_lb;
    GtkEntry *txt_g;
    bool mutex;
};

void convert_lb_event(GtkWidget *entry, gpointer data );
void convert_oz_event(GtkWidget *entry, gpointer data );
void convert_g_event(GtkWidget *entry, gpointer data );

void convert_lb_event(GtkWidget *entry, gpointer data ) {
    ClickCallbackDataT * widgets = (ClickCallbackDataT*)(data);
    if ( widgets->mutex == true )
        return;
    widgets->mutex = true;
    const gchar *pounds_text = gtk_entry_get_text(GTK_ENTRY(widgets->txt_lb));
    const float pounds = g_strtod(pounds_text, NULL);
    const float ounces = pounds * LB_TO_OZ;
    const float grams = ounces * G_TO_OZ;
    gtk_entry_set_text(widgets->txt_oz, g_strdup_printf("%f", ounces));
    gtk_entry_set_text(widgets->txt_g, g_strdup_printf("%f", grams));
    widgets->mutex = false;
}

void convert_oz_event(GtkWidget *entry, gpointer data ) {
    ClickCallbackDataT * widgets = (ClickCallbackDataT*)(data);
    if ( widgets->mutex == true )
        return;
    widgets->mutex = true;
    const gchar *ounces_text = gtk_entry_get_text(GTK_ENTRY(widgets->txt_oz));
    const float ounces = g_strtod(ounces_text, NULL);
    const float pounds = ounces * OZ_TO_LB;
    const float grams = ounces * G_TO_OZ;
    gtk_entry_set_text(widgets->txt_g, g_strdup_printf("%f", grams));
    gtk_entry_set_text(widgets->txt_lb, g_strdup_printf("%f", pounds));
    widgets->mutex = false;
}

void convert_g_event(GtkWidget *entry, gpointer data ) {
    ClickCallbackDataT * widgets = (ClickCallbackDataT*)(data);
    if ( widgets->mutex == true )
        return;
    widgets->mutex = true;
    const gchar *grams_text = gtk_entry_get_text(GTK_ENTRY(widgets->txt_g));
    const float grams = g_strtod(grams_text, NULL);
    const float ounces = grams * OZ_TO_G;
    const float pounds = ounces * LB_TO_OZ;
    gtk_entry_set_text(widgets->txt_oz, g_strdup_printf("%f", ounces));
    gtk_entry_set_text(widgets->txt_lb, g_strdup_printf("%f", pounds));
    widgets->mutex = false;
}

void Gadgetify( GtkWindow *window ) {
    gtk_window_set_decorated( window, false );
    gtk_window_set_keep_below( window, true );
    gtk_window_set_skip_taskbar_hint( window, true );
    gtk_window_set_skip_pager_hint( window, true );
    gtk_window_stick( window );
}

bool shutting_down;
void ProgramExit( void ) {
    shutting_down=true;
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); 
    
    GtkWindow *window = (GtkWindow*) gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect( window, "destroy", G_CALLBACK( ProgramExit ), NULL ); 
    gtk_window_set_title(GTK_WINDOW(window), WINDOW_NAME);
    
    ClickCallbackDataT data;
    GtkLabel *lbl_oz = (GtkLabel*)gtk_label_new("oz");
    GtkLabel *lbl_lb = (GtkLabel*)gtk_label_new("lb");
    GtkLabel *lbl_g = (GtkLabel*)gtk_label_new("g");
    data.txt_oz = (GtkEntry*)gtk_entry_new();
    data.txt_lb = (GtkEntry*)gtk_entry_new();
    data.txt_g = (GtkEntry*)gtk_entry_new();
    data.mutex = false;
    
    g_signal_connect(data.txt_oz, "changed", G_CALLBACK(convert_oz_event), &data); 
    g_signal_connect(data.txt_lb, "changed", G_CALLBACK(convert_lb_event), &data); 
    g_signal_connect(data.txt_g, "changed", G_CALLBACK(convert_g_event), &data); 
    
    GtkWidget *hbox_oz = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox_oz), (GtkWidget*)lbl_oz, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_oz), (GtkWidget*)data.txt_oz, TRUE, TRUE, 0);
    
    GtkWidget *hbox_lb = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox_lb), (GtkWidget*)lbl_lb, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_lb), (GtkWidget*)data.txt_lb, TRUE, TRUE, 0);
    
    GtkWidget *hbox_g = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox_g), (GtkWidget*)lbl_g, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_g), (GtkWidget*)data.txt_g, FALSE, FALSE, 0);
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_lb);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_oz);
    gtk_container_add(GTK_CONTAINER(vbox), hbox_g);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all( (GtkWidget*) window);

    shutting_down=false;
    gtk_main_iteration();
    Gadgetify( window );

    gtk_main();
    return 0;
}
