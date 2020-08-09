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
    set_menu_win(this->menu, this->window);
    set_menu_sub(this->menu, derwin(this->window, this->n_choices + 1, 19, 3, 1));
    set_menu_mark(this->menu, " * ");
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
        break;
    case KEY_UP:
        menu_driver(this->menu, REQ_UP_ITEM);
        break;
    case _KEY_ENTER:
        item = current_item(this->menu);
        retval = item->index;
        break;
    case KEY_F(12):
        retval = 4;
        break;
    }
    wrefresh(this->window);
    return retval;
}

void MainMenu::finish() {
    if (this->menu != NULL) {
        unpost_menu(this->menu);
        free_menu(this->menu);
    }
    if (this->title != NULL)
        free(this->title);
    if (this->n_choices != NULL) {
        for (int i = 0; i < this->n_choices; ++i)
            free_item(this->_items[i]);
    }
}

void MainMenu::draw(bool boxed) {
    if (boxed) {
        box(this->window, 0, 0);
        mvwhline(this->window, 2, 1, ACS_HLINE, 23);
    }
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    int windowY = getmaxy(this->window);
    print_in_middle(this->window, 1, 1, windowY, title, COLOR_PAIR(1));
}

MainMenu::~MainMenu() {
    this->finish();
}