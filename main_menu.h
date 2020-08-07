#include <menu.h>
#include <curses.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

class MainMenu {
public:
    MainMenu(char *choices[], char *descriptions[], int size, WINDOW *, bool);
    int getAction();

    void finish();

private:
    int n_choices;
    WINDOW *window;
    MENU *menu;
    ITEM **_items;
};