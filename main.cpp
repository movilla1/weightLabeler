#include <menu.h>
#include "main.h"
#include "main_menu.h"

using namespace std;

int main(int argc, char ** argv) {
    bool exit = false;
    int action = -1;
    int key = 0;
    char *choices[] = {
      "Imprimir Peso     ",
      "Buscar Articulo   ",
      "Crear Articulo    ",
      "Modificar Articulo",
      "Salir             "
    };
    char *descriptions[] = {
      "Imprimir etiqueta de peso con art. ",
      "Buscar articulo por codigo o nombre",
      "Crear articulo nuevo en la base    ",
      "Modificar datos de articulo        ",
      "Terminar y salir del sistema       "
    };

    MEVENT mouseEvent;
    MENU *myMenu;
    ITEM **my_items;

    initscr(); //initialize ncurses lib
    clear();
    noecho();
    cbreak();
    /* Get all the mouse events */
    mousemask(ALL_MOUSE_EVENTS, NULL);
    init_display_frame();
    WINDOW *menuWindow = newwin(11, 25, 1, 1);
    MainMenu menu(choices, descriptions,ARRAY_SIZE(choices), menuWindow, true);
    keypad(stdscr, true);
    wtimeout(stdscr, 0);
    while (!exit) {
        action = menu.getAction();
        switch (action) {
          case 3:
            exit = true;
            break;
        }
    }
    menu.finish();
    endwin(); // frees memory and releases all resources
    //printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
    return 0;
}

void init_display_frame() {
    //printf("\033[?1003h\n");
    box(stdscr, 0, 0);
    move(14, 24);
    printw("Hello!");
    refresh();
}

void imprimir_peso() {
    //dibujar pantalla con peso y articulo
    //boton para leer peso
    //boton para imprimir etiqueta
    //boton para menu principal
}

void buscar_articulo() {
    // permitir busqueda por codigo o nombre
    // mostrar listado y permitir seleccion de uno para detalles
    // mostrar detalles c/boton volver al listado
    // opcion para volver a menu principal.
}

void crear_articulo() {
    //dibujar pantalla de articulo
    //esperar inputs
    //grabar datos y preguntar otro o menu
}

void modificar_articulo() {
    //dibujar formulario
    // permitir busqueda por código o nombre
    // mostrar registro seleccionado en campos de edicion
    // grabar y esperar por opcion de volver al menu o seguir editando
}