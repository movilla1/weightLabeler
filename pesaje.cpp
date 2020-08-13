#include "pesaje.h"
//boton para leer peso
//boton para imprimir etiqueta
//boton para menu principal
#define MENUSIZE 4

Pesaje::Pesaje(Articulo *articulo) {
    //dibujar pantalla con peso y articulo
    this->window = newwin(24, 79, 0, 0);
    char *options[10] ={
        "Leer Peso",
        "Imprimir",
        "Volver",
    };
    this->_items = (ITEM **)calloc(MENUSIZE, sizeof(ITEM *));
    for (int i = 0; i < MENUSIZE - 1; ++i) {
        this->_items[i] = new_item(options[i], options[i]);
        this->_items[i]->index = i;
    }
    this->_items[MENUSIZE-1] = (ITEM *)NULL;
    wtimeout(this->window, 0);
    box(this->window, 0, 0);
    this->menuWindow = newwin(3, 79, 2, 0);
    this->menu = new_menu((ITEM **)this->_items);
    /* Set menu option not to show the description */
    this->drawScreen();
    keypad(this->menuWindow, true);
    keypad(this->window, true);
    wrefresh(this->window);
    menu_opts_off(this->menu, O_SHOWDESC);
    set_menu_win(this->menu, this->menuWindow);
    set_menu_sub(this->menu, derwin(this->menuWindow, 1, 76, 1, 2));
    set_menu_format(this->menu, 1, 5);
    post_menu(this->menu);
    wrefresh(this->menuWindow);
    this->running = true;
    this->articulo = articulo;
}

void Pesaje::run() {
    int selection = -1;
    int key = wgetch(this->menuWindow);
    ITEM *item;
    switch (key) {
    case KEY_LEFT:
        menu_driver(this->menu, REQ_LEFT_ITEM);
        wrefresh(this->menuWindow);
        break;
    case KEY_RIGHT:
        menu_driver(this->menu, REQ_RIGHT_ITEM);
        wrefresh(this->menuWindow);
        break;
    case 'q':
        this->running = false;
        break;
    case _KEY_ENTER:
        item = current_item(this->menu);
        selection = item->index;
        break;
    }
    switch (selection) {
    case 0:
    case 1:
        break;
    case 2:
        this->running = false;
        break;
    }
}

void Pesaje::drawScreen() {
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    print_in_middle(this->window, 1, 1, 79, "Operaciones", COLOR_PAIR(1));
    box(this->menuWindow, 0, 0);
    mvwaddch(this->menuWindow, 0, 0, ACS_LTEE);
    mvwaddch(this->menuWindow, 0, 78, ACS_RTEE);
    mvwaddch(this->menuWindow, 2, 0, ACS_LTEE);
    mvwaddch(this->menuWindow, 2, 78, ACS_RTEE);
    wrefresh(this->window);
}