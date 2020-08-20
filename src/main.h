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
#include "articulo.h"
#include "buscar.h"
#include "crear_articulo.h"
#include "db_interface.h"
#include "main_menu.h"
#include "modificar_articulo.h"
#include "pesaje.h"

#define ACTION_PRINT 0
#define ACTION_SEARCH 1
#define ACTION_CREATE 2
#define ACTION_MODIFY 3
#define ACTION_EXIT 4

void init_display_frame();
void buscar_articulo(DbInterface *);
void crear_articulo(DbInterface *);
void modificar_articulo(DbInterface *);
void imprimir_peso(DbInterface *);