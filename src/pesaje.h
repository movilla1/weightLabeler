#include "dialogo.h"
#include "articulo.h"
#include "db_interface.h"

class Pesaje {
public:
    bool running;
    Pesaje(DbInterface *db);
    ~Pesaje();
    void run();

protected:
    void draw();
    void buscarSKU();
    Dialogo *ventana;
    WINDOW *dlgArea;
    Articulo *articulo;
    DbInterface *db;
};