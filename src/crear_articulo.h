#include <string>
#include <ncurses.h>
#include <form.h>
#include "articulo.h"
#include "common.h"
#include "db_interface.h"

#define CREATE_FIELD_COUNT 5

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
    void setFieldBacks();
    void setFieldOpts();
    bool saveData();
    void startNew();
};