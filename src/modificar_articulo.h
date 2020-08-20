#include <string>
#include <ncurses.h>
#include "articulo.h"
#include "common.h"
#include "dialogo.h"
#include "db_interface.h"

using namespace std;

class ModificarArticulo {
  public:
    ModificarArticulo(DbInterface *);
    ~ModificarArticulo();
    bool running;
    void run();

  protected:
    DbInterface *db;
    string claves;
    Dialogo *ventana;
};