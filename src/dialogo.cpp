#include "dialogo.h"

Dialogo::Dialogo(char **options, unsigned char menusize) {
    this->maxX = getmaxx(stdscr);
    this->menuSize = menusize;
    this->window = newwin(24, maxX, 0, 0);
    this->_items = (ITEM **)calloc(this->menuSize+1, sizeof(ITEM *));
    for (int i = 0; i < this->menuSize; ++i) {
        this->_items[i] = new_item(options[i], options[i]);
        this->_items[i]->index = i;
    }
    this->_items[this->menuSize] = (ITEM *)NULL;
    wtimeout(this->window, 0);
    box(this->window, 0, 0);
    this->menuWindow = newwin(3, maxX, 2, 0);
    this->menu = new_menu((ITEM **)this->_items);
    /* Set menu option not to show the description */
    this->drawScreen();
    keypad(this->menuWindow, true);
    keypad(this->window, true);
    wrefresh(this->window);
    menu_opts_off(this->menu, O_SHOWDESC);
    set_menu_win(this->menu, this->menuWindow);
    set_menu_sub(this->menu, derwin(this->menuWindow, 1, maxX - 3, 1, 2));
    set_menu_format(this->menu, 1, 5);
    post_menu(this->menu);
    this->running = true;
    this->dialogArea = newwin( 18, this->maxX-2, 5, 1);
}

void Dialogo::setTitle(string title) {
  this->title = title;
  this->drawScreen();
}

void Dialogo::drawScreen() {
    init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
    print_in_middle(this->window, 1, 1, this->maxX, (char *)this->title.c_str(), COLOR_PAIR(YELLOW_ON_BLACK));
    box(this->menuWindow, 0, 0);
    mvwaddch(this->menuWindow, 0, 0, ACS_LTEE);
    mvwaddch(this->menuWindow, 0, this->maxX-1, ACS_RTEE);
    mvwaddch(this->menuWindow, 2, 0, ACS_LTEE);
    mvwaddch(this->menuWindow, 2, this->maxX-1, ACS_RTEE);
    wrefresh(this->window);
}

Dialogo::~Dialogo() {
    if (this->menu != nullptr) {
        unpost_menu(this->menu);
        free_menu(this->menu);
    }
    if (this->menuSize != 0) {
        for (int i = 0; i < this->menuSize; ++i)
            free_item(this->_items[i]);
    }
}

// This must be overriden by custom class and call parent run
unsigned char Dialogo::runDialog() {
    unsigned char selection = -1;
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
    case _KEY_ENTER:
        item = current_item(this->menu);
        selection = item->index;
        break;
    case KEY_F(8): // ON F8 return the last menu option (by convention used, cancel/quit is on the last menu position)
        selection = this->menuSize - 1;
        break;
    }
    return selection;
}

WINDOW *Dialogo::getDialogArea() {
  return (this->dialogArea);
}