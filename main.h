#include <ncurses.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <sqlite3.h> 
#include <malloc.h>
#include <cstring>
#include <menu.h>
#include "main_menu.h"
#include "pesaje.h"
#include "articulo.h"

#define ACTION_PRINT 0
#define ACTION_SEARCH 1
#define ACTION_CREATE 2
#define ACTION_MODIFY 3
#define ACTION_EXIT 4

void init_display_frame();
void buscar_articulo();
void crear_articulo();
void modificar_articulo();
void imprimir_peso();