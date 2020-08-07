#include <curses.h>
#include <malloc.h>
#include "main_menu.h"

MainMenu::MainMenu(char *choices[], char *descriptions[], int choice_size, WINDOW *win, bool boxed) {
    this->n_choices = choice_size;
    this->_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for (int i = 0; i < n_choices; ++i)
    {
        this->_items[i] = new_item(choices[i], descriptions[i]);
        /* Set the user pointer */
    }
    this->_items[n_choices] = (ITEM *)NULL;

    /* Create menu */
    this->menu = new_menu((ITEM **)this->_items);
    this->window = win;
    set_menu_win(this->menu, this->window);
    set_menu_mark(this->menu, " * ");
    keypad(this->window, TRUE);
    if (boxed) {
        box(this->window, 0, 0);
    }
    wtimeout(this->window, 0);
    post_menu(this->menu);
    mvwprintw(this->window, 11,1, "%d", choice_size);
    wrefresh(this->window);
}

int MainMenu::getAction() {
    int retval=-1;
    int key = wgetch(this->window);
    switch (key) {
    case KEY_DOWN:
        menu_driver(this->menu, REQ_DOWN_ITEM);
        break;
    case KEY_UP:
        menu_driver(this->menu, REQ_UP_ITEM);
        break;
    case 10: //this is the enter key pressed
        wprintw(this->window, "Enter!");
        break;
    case KEY_F(1): /* Enter */
        retval= 3;
        break;
    }
    wrefresh(this->window);
    return retval;
}

void MainMenu::finish() {
    unpost_menu(this->menu);
    free_menu(this->menu);
    for (int i = 0; i < this->n_choices; ++i)
        free_item(this->_items[i]);
}