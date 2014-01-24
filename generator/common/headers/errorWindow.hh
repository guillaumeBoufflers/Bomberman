#ifndef		__ERRORWINDOW_HH__
#define		__ERRORWINDOW_HH__

#include	<iostream>
#include	<vector>
#include	<string>
#include	<cstdlib>
#include	<pthread.h>
#include	<gtk/gtk.h>

void		errorWindow(std::string message, std::string title);

#endif
