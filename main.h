#include <ncurses.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <sqlite3.h> 
#include <malloc.h>
#include <cstring>

void init_display_frame();
void buscar_articulo();
void crear_articulo();
void modificar_articulo();
void imprimir_peso();