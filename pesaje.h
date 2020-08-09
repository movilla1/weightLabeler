#include <curses.h>
#include <menu.h>
#include <string>
#include "common.h"

class Pesaje {
public:
    bool running;
    Pesaje();
    void run();

protected:
    void drawScreen();
    WINDOW *window;
    ITEM **_items;
    MENU *menu;
};