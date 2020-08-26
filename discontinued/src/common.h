#include <menu.h>
#include <curses.h>
#include <string>
#include <cstring>
#include <ctime>

#define _KEY_ENTER 10
#define _KEY_ESCAPE 27

#define COLOR_ERROR 20
#define COLOR_NORMAL 21
#define GREEN_ON_BLACK 24
#define CYAN_ON_BLACK 14
#define BLUE_ON_BLACK 4
#define BLUE_ON_WHITE 2
#define YELLOW_ON_BLACK 3


void print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string, chtype color);
std::string getCurrentDate();
void showAlert(WINDOW *win, const char *text, bool isError);