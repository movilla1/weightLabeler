#include <string>
#include <ncurses.h>
#include <form.h>
#include "articulo.h"
#include "common.h"
#include "db_interface.h"

using namespace std;

class CrearArticulo {
  public:
    CrearArticulo(DbInterface *);
    ~CrearArticulo();
    bool running;
    void run();

  protected:
    DbInterface *db;
    WINDOW *dlgArea;
    FORM *form;
    FIELD *fields[6];
    void draw();
    void setupForm();
    bool saveData();
    void startNew();
};