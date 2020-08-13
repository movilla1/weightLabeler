#include <curses.h>
#include <menu.h>
#include <string>
#include "common.h"
#include "articulo.h"

class Pesaje {
public:
    bool running;
    Pesaje(Articulo *articulo);
    void run();

protected:
    void drawScreen();
    WINDOW *window;
    WINDOW *menuWindow;
    ITEM **_items;
    MENU *menu;
    Articulo *articulo;
};