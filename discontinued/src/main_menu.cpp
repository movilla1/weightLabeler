#include <curses.h>
#include <malloc.h>
#include "main_menu.h"

MainMenu::MainMenu(bool boxed, char *title) {
    int maxY = getmaxy(stdscr);
    WINDOW *menuWindow = newwin(maxY, 25, 0, 0);

    this->n_choices = ARRAY_SIZE(this->choices);
    this->_items = (ITEM **)calloc(this->n_choices + 1, sizeof(ITEM *));
    for (int i = 0; i < this->n_choices; ++i) {
        this->_items[i] = new_item(this->choices[i], this->descriptions[i]);
        this->_items[i]->index = i;
    }
    this->_items[this->n_choices] = (ITEM *)NULL;
    int titleLen = strlen(title);
    this->title = (char *)malloc(titleLen);
    strncpy(this->title, title, titleLen);
    /* Create menu */
    this->menu = new_menu((ITEM **)this->_items);
    this->window = menuWindow;
    keypad(this->window, TRUE);
    wtimeout(this->window, 0);
    this->draw(boxed);
    menu_opts_off(this->menu, O_SHOWDESC);
    set_menu_win(this->menu, this->window);
    set_menu_sub(this->menu, derwin(this->window, this->n_choices + 1, 22, 3, 1));
    post_menu(this->menu);
    wrefresh(this->window);
}

int MainMenu::getAction() {
    int retval=-1;
    int key = wgetch(this->window);
    ITEM *item;
    switch (key) {
    case KEY_DOWN:
        menu_driver(this->menu, REQ_DOWN_ITEM);
        this->showDescription(current_item(this->menu));
        wrefresh(this->window);
        break;
    case KEY_UP:
        menu_driver(this->menu, REQ_UP_ITEM);
        this->showDescription(current_item(this->menu));
        wrefresh(this->window);
        break;
    case _KEY_ENTER:
        item = current_item(this->menu);
        retval = item->index;
        break;
    case KEY_F(8):
        retval = 4;
        break;
    }
    
    return retval;
}

void MainMenu::finish() {
    if (this->menu != nullptr) {
        unpost_menu(this->menu);
        free_menu(this->menu);
    }
    if (this->title != nullptr)
        free(this->title);
    if (this->n_choices != 0) {
        for (int i = 0; i < this->n_choices; ++i)
            free_item(this->_items[i]);
    }
}

void MainMenu::draw(bool boxed) {
    if (boxed) {
        box(this->window, 0, 0);
        mvwaddch(this->window, 2, 0, ACS_LTEE);
        mvwhline(this->window, 2, 1, ACS_HLINE, 23);
        mvwaddch(this->window, 2, 24, ACS_RTEE);
        mvwaddch(this->window,0,24, ACS_TTEE);
        mvwaddch(this->window,24,24, ACS_BTEE);
    }
    int windowY = getmaxy(this->window);
    print_in_middle(this->window, 1, 1, windowY, title, COLOR_PAIR(BLUE_ON_BLACK));
}

void MainMenu::showDescription(ITEM *item) {
  attron(COLOR_PAIR(CYAN_ON_BLACK));
  mvprintw(22,26, item->description.str);
  attroff(COLOR_PAIR(CYAN_ON_BLACK));
}

MainMenu::~MainMenu() {
    this->finish();
}