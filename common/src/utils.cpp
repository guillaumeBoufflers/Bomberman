#include 			"utils.hh"

namespace 			BUtils {

  void 			handleGtkEvents() {
    while (gtk_events_pending())
      gtk_main_iteration();
  }


  char			*openFileDialog(const char *str) {
    GtkWidget 	*dialog   = NULL;
    char 		*filename = NULL;

    dialog = gtk_file_chooser_dialog_new(str,
					 NULL,
					 GTK_FILE_CHOOSER_ACTION_OPEN,
					 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					 GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					 NULL);

    if (dialog) {
      char *cwd = get_current_dir_name();
      if (cwd)
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), cwd);
      if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
	filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
	if (filename) {
	  gtk_widget_destroy(dialog);
	  BUtils::handleGtkEvents();
	  return (filename);
	}
      }
      gtk_widget_destroy(dialog);
      BUtils::handleGtkEvents();
      return (NULL);
    } else {
      throw new BombermanException("Cannot init open file dialog");
    }
    BUtils::handleGtkEvents();
    return (NULL);
  }

  char			*saveFileDialog(const char *str) {
    GtkWidget 	*dialog   = NULL;
    char 		*filename = NULL;

    dialog = gtk_file_chooser_dialog_new(str,
					 NULL,
					 GTK_FILE_CHOOSER_ACTION_SAVE,
					 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					 GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
					 NULL);

    if (dialog) {
      gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
      char *cwd = get_current_dir_name();
      if (cwd)
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), cwd);
      if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
	filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
	if (filename) {
	  gtk_widget_destroy(dialog);
	  BUtils::handleGtkEvents();
	  return (filename);
	}
      }
      gtk_widget_destroy(dialog);
      BUtils::handleGtkEvents();
      return (NULL);
    } else {
      throw new BombermanException("Cannot init open file dialog");
    }
    BUtils::handleGtkEvents();
    return (NULL);
  }

  void 			runDialog(GtkMessageType type, const char *str) {
    GtkWidget 	*dialog;

    dialog = gtk_message_dialog_new(
				    NULL,
				    GTK_DIALOG_DESTROY_WITH_PARENT,
				    type,
				    GTK_BUTTONS_CLOSE,
				    "%s", str);
    if (dialog) {
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);
      BUtils::handleGtkEvents();
    } else {
      throw new BombermanException("Cannot init open file dialog");
    }
  }

  int   stringToInt(std::string myStream)
  {
    int value;

    std::istringstream buffer(myStream);
    buffer >> value;
    return (value);
  }

  bool    isNum(std::string str)
  {
    int     i;

    i = -1;
    while (str[++i])
      if (!(str[i] <= '9' && str[i] >= '0'))
	return (false);
    return (true);
  }

  std::string		intToString(int a) {
    std::stringstream convert;

    convert << a;
    return (convert.str());
  }

  std::vector<std::string>	split(char delim, std::string work)
  {
    std::vector<std::string> flds;
    std::string buf = "";
    work = work.data();
    size_t        i = 0;

    if (!flds.empty())
      flds.clear();
    while (i < work.length())
      {
	while (work[i] != delim && i < work.length() )
	  {
	    buf += work[i];
	    i++;
	  }
	flds.push_back(buf);
	buf = "";
	while (work[i] == delim && i < work.length() )
	  i++;
      }
    return (flds);
  }

  void						createMd5(const std::string &filename) {
    std::string md5filename = filename + ".md5";
    QFile file(filename.c_str());
    std::fstream filestream(md5filename.c_str(), std::fstream::out | std::fstream::trunc);

    if (filestream && file.open(QIODevice::ReadOnly)) {
      QByteArray byteArray = file.readAll();
      QByteArray md5 = QCryptographicHash::hash(byteArray,QCryptographicHash::Md5);
      filestream << md5.toHex().data() << std::endl;
      filestream.close();
    }
  }

  bool						checkMd5(const std::string &filename) {
    std::string 			md5filename = filename + ".md5";
    QFile 					file(filename.c_str());
    std::fstream 			filestream(md5filename.c_str(), std::fstream::in);
    std::string 			md5_fichier;
    std::string 			md5_reel;
    if (filestream && file.open(QIODevice::ReadOnly)) {
      getline(filestream, md5_fichier);
      QByteArray byteArray = file.readAll();
      QByteArray md5 = QCryptographicHash::hash(byteArray,QCryptographicHash::Md5);
      md5_reel = md5.toHex().data();
      if (md5_reel == md5_fichier)
	return (true);
    }
    return (false);
  }

}
