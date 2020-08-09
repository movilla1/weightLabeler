#include "pesaje.h"
//boton para leer peso
//boton para imprimir etiqueta
//boton para menu principal
#define MENUSIZE 4

Pesaje::Pesaje() {
    //dibujar pantalla con peso y articulo
    this->window = newwin(24, 79, 1, 1);
    box(this->window, 0, 0);
    char *options[] ={
        "Leer Peso",
        "Imprimir ",
        "Volver   ",
    };
    this->_items = (ITEM **)calloc(MENUSIZE, sizeof(ITEM *));
    for (int i = 0; i < MENUSIZE - 1; ++i) {
        this->_items[i] = new_item(options[i], options[i]);
        this->_items[i]->index = i;
    }
    this->_items[MENUSIZE] = (ITEM *)NULL;
    wtimeout(this->window, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    print_in_middle(this->window, 1, 1, 79, "Operaciones", COLOR_PAIR(1));
    mvwhline(this->window, 2, 1, ACS_HLINE, 80);
    set_menu_win(this->menu, this->window);
    /* Set menu option not to show the description */
    menu_opts_off(this->menu, O_SHOWDESC);
    set_menu_format(this->menu, 1, 5);
    set_menu_sub(this->menu, derwin(this->window, 3, 80, 1, 1));
    set_menu_mark(this->menu, " * ");
    post_menu(this->menu);
    wrefresh(this->window);
    this->running = true;
}

void Pesaje::run() {
    int selection = -1;
    int key = wgetch(this->window);
    ITEM *item;
    switch (key) {
    case KEY_DOWN:
        menu_driver(this->menu, REQ_DOWN_ITEM);
        break;
    case KEY_UP:
        menu_driver(this->menu, REQ_UP_ITEM);
        break;
    case _KEY_ESCAPE:
        this->running = false;
        break;
    case _KEY_ENTER:
        item = current_item(this->menu);
        selection = item->index;
        break;
    }
    switch (selection) {
      case 2:
        this->running = false;
        break;
    }

    wrefresh(this->window);
}