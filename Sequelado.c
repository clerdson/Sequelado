#include <gtk/gtk.h>
int main(int argc, char *argv[]){

GtkWidget *window;
GtkWidget *button;
GtkWidget *halign;

gtk_init(&argc ,&argv);
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window),"Sequelado");
gtk_window_set_default_size(GTK_WINDOW(window),400,400); 




button = gtk_button_new_with_label("Sequelado");
gtk_widget_set_tooltip_text(button,"Sequelado");

halign = gtk_alignment_new (0,0,0,0);
gtk_container_add(GTK_CONTAINER(halign),button);
gtk_container_add(GTK_CONTAINER(window),halign);


gtk_widget_show_all(window);



gtk_main();

return 0;
}
