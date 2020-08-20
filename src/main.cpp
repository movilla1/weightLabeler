#include "main.h"

using namespace std;

int main(int argc, char ** argv) {
    bool exit = false;
    int action = -1;
    int maxY = 20;
    
    initscr(); //initialize ncurses lib
    start_color();
    clear();
    noecho();
    cbreak();
    DbInterface db;
    /* Get all the mouse events */
    mousemask(ALL_MOUSE_EVENTS, NULL);
    init_display_frame();
    MainMenu menu(true, "Menu Principal");
    keypad(stdscr, true);
    wtimeout(stdscr, 0);
    while (!exit) {
        action = menu.getAction();
        switch (action) {
          case ACTION_PRINT:
            imprimir_peso(&db);
            init_display_frame();
            break;
          case ACTION_SEARCH:
            buscar_articulo(&db);
            init_display_frame();
            break;
          case ACTION_CREATE:
            crear_articulo(&db);
            init_display_frame();
            break;
          case ACTION_MODIFY:
            modificar_articulo(&db);
            init_display_frame();
            break;
          case ACTION_EXIT:
            exit = true;
            break;
        }
        menu.draw(true);
    }
    endwin(); // frees memory and releases all resources
    //printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
    return 0;
}

void init_display_frame() {
    //printf("\033[?1003h\n");
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    box(stdscr, 0, 0);
    wattron(stdscr, COLOR_PAIR(1));
    mvprintw(23,26, "WeigthLabeler v1.0");
    wattroff(stdscr, COLOR_PAIR(1));
    wattron(stdscr, COLOR_PAIR(2));
    mvprintw(23,55, "(c) 2020 - ElcanSoftware");
    wattroff(stdscr, COLOR_PAIR(2));
    refresh();
}

void imprimir_peso(DbInterface *db) {
    Pesaje pesaje(db);
    while(pesaje.running)  {
      pesaje.run();
    }
}

void buscar_articulo(DbInterface *db) {
    // permitir busqueda por codigo o nombre
    // mostrar listado y permitir seleccion de uno para detalles
    // mostrar detalles c/boton volver al listado
    // opcion para volver a menu principal.
    BuscarArticulo buscar(db);
    while(buscar.running) {
      buscar.run();
    }
}

void crear_articulo(DbInterface *db) {
    //dibujar pantalla de articulo
    //esperar inputs
    //grabar datos y preguntar otro o menu
    CrearArticulo crea(db);
    while(crea.running) {
      crea.run();
    }
}

void modificar_articulo(DbInterface *db) {
    //dibujar formulario
    // permitir busqueda por código o nombre
    // mostrar registro seleccionado en campos de edicion
    // grabar y esperar por opcion de volver al menu o seguir editando
    ModificarArticulo mod(db);
    while(mod.running) {
      mod.run();
    }
}