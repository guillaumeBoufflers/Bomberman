#include	"errorWindow.hh"

void		errorWindow(std::string message, std::string title)
{
  GtkWidget* pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(pWindow), title.c_str());
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 50);
  GtkWidget *hBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(pWindow), hBox);
  GtkWidget *pLabel = gtk_label_new(message.c_str());
  gtk_box_pack_start(GTK_BOX(hBox), pLabel, TRUE, FALSE, 0);
  gtk_widget_show_all(pWindow);
}
