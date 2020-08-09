#include <menu.h>
#include <curses.h>
#include <cstring>

#define _KEY_ENTER 10
#define _KEY_ESCAPE 27
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);