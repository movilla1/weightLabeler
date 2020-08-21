#include "main.h"

using namespace std;

void init_colors()
{
  init_pair(GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK);
  init_pair(CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK);
  init_pair(BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
  init_pair(BLUE_ON_WHITE, COLOR_BLUE, COLOR_WHITE);
  init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
}

int main(int argc, char **argv)
{
  bool exit = false;
  int action = -1;

  initscr(); //initialize ncurses lib
  start_color();
  init_colors();
  clear();
  noecho();
  cbreak();
  DbInterface db;
  /* Get all the mouse events */
  printf("\033[?1003h\n");
  mousemask(ALL_MOUSE_EVENTS, NULL);
  init_display_frame();
  MainMenu menu(true, "Menu Principal");
  keypad(stdscr, true);
  wtimeout(stdscr, 0);
  while (!exit)
  {
    action = menu.getAction();
    switch (action)
    {
    case ACTION_PRINT:
      imprimir_peso(&db);
      init_display_frame();
      break;
    case ACTION_SEARCH:
      listar_articulo(&db);
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
  endwin();                // frees memory and releases all resources
  printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
  return 0;
}

void init_display_frame()
{
  clear();
  box(stdscr, 0, 0);
  wattron(stdscr, COLOR_PAIR(GREEN_ON_BLACK));
  mvprintw(23, 26, "WeigthLabeler v1.0");
  wattroff(stdscr, COLOR_PAIR(GREEN_ON_BLACK));
  wattron(stdscr, COLOR_PAIR(CYAN_ON_BLACK));
  mvprintw(23, 55, "(c) 2020 - ElcanSoftware");
  wattroff(stdscr, COLOR_PAIR(CYAN_ON_BLACK));
  refresh();
}

void imprimir_peso(DbInterface *db)
{
  Pesaje pesaje(db);
  while (pesaje.running)
  {
    pesaje.run();
  }
}

void listar_articulo(DbInterface *db)
{
  ListarArticulos lista(db);
  while (lista.running)
  {
    lista.run();
  }
}

void crear_articulo(DbInterface *db)
{
  CrearArticulo crea(db);
  while (crea.running)
  {
    crea.run();
  }
}

void modificar_articulo(DbInterface *db)
{
  ModificarArticulo mod(db);
  while (mod.running)
  {
    mod.run();
  }
}