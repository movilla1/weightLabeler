#include <string>
#include <ncurses.h>
#include "articulo.h"
#include "common.h"
#include "db_interface.h"
#include "dialogo.h"

using namespace std;

class BuscarArticulo {
  public:
    BuscarArticulo(DbInterface *db);
    ~BuscarArticulo();
    bool running;
    void run();

  protected:
    Articulo *articulo;
    string claves;
    Dialogo *ventana;
    DbInterface *db;
    list<Articulo> articulos;
    WINDOW *dlgArea;
    void draw();
};