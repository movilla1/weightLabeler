#include <menu.h>
#include <curses.h>
#include <string>
#include <cstring>
#include <ctime>

#define _KEY_ENTER 10
#define _KEY_ESCAPE 27
#define COLOR_GRAY 20230
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
std::string getCurrentDate();
