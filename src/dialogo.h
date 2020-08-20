#ifndef _DIALOGO_H
#define _DIALOGO_H 1
#include <curses.h>
#include <menu.h>
#include <string>
#include "common.h"

using namespace std;

class Dialogo {
  public:
    Dialogo(char **, unsigned char);
    ~Dialogo();
    bool running;
    void run(); //must be implemented by the subclass
    void setTitle(string title);
    unsigned char runDialog();
    WINDOW *getDialogArea();

  protected:
    void drawScreen();
    WINDOW *window;
    WINDOW *menuWindow;
    WINDOW *dialogArea;
    ITEM **_items;
    MENU *menu;
    string title;
    char *menu_options;
    int maxX;
    unsigned char menuSize;
};
#endif