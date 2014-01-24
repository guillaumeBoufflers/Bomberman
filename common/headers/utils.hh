#ifndef 		__UTILS_HH__
#define 		__UTILS_HH__

#include 		"common.hh"

namespace 		BUtils {

  char 		*openFileDialog(const char *);
  char    *saveFileDialog(const char *);
  void		handleGtkEvents();
  std::vector<std::string>	split(char delim, std::string work);
  char 		*openFileDialog(const char *str);
  void		handleGtkEvents();
  /**
   * Types possibles :
   *	  GTK_MESSAGE_INFO,
   *	  GTK_MESSAGE_WARNING,
   *	  GTK_MESSAGE_QUESTION,
   *	  GTK_MESSAGE_ERROR,
   *	  GTK_MESSAGE_OTHER
   */
  void 		runDialog(GtkMessageType type, const char *str);
  std::string		intToString(int a);
  int			stringToInt(std::string myStream);
  bool    isNum(std::string str);

  void    createMd5(const std::string &file);
  bool    checkMd5(const std::string &filename);
};

#endif
