#include <menu.h>
#include <curses.h>
#include <cstring>
#include "common.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

class MainMenu {
public:
    MainMenu(bool, char *);
    ~MainMenu();
    int getAction();
    void draw(bool);
    void finish();

private:
    const char choices[5][20] = {
      "Imprimir Peso",
      "Listar Articulos",
      "Crear Articulo",
      "Modificar Articulo",
      "Terminar y Salir"
    };
    const char descriptions[5][35] = {
      "Imprimir etiqueta de peso con art.",
      "Listar Todos los articulos en db.",
      "Crear articulo nuevo en la base",
      "Modificar datos de articulo",
      "Terminar y salir del sistema"
    };
    void showDescription(ITEM *);
    int n_choices;
    char *title;
    WINDOW *window;
    MENU *menu;
    ITEM **_items;
};