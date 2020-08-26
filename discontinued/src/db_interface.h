#ifndef __DBINTERFACE__h
#define __DBINTERFACE__h 1
#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include "articulo.h"


class DbInterface {
  public:
    DbInterface();
    Articulo *cargarPrimerArticulo();
    Articulo *cargarArticulo(int id);
    void searchBySKU_UPC(string sku_upc, list<Articulo> *articulos);
    void searchByName(string nombre, list<Articulo> *articulos);
    void listarArticulos(list<Articulo> *articulos);
    bool grabarArticulo(Articulo *);
    ~DbInterface();
  protected:
    sqlite3 *DB;
    sqlite3_stmt *stmt;
    char *messaggeError;
    const string pageLimit = " LIMIT 12";
    bool exec(string sql);
    void query(string sql, list<Articulo> *);
};
#endif