#include "db_interface.h"

using namespace std;

Articulo *DbInterface::cargarPrimerArticulo() {
  string sql = "SELECT * FROM productos WHERE 1 ORDER BY id ASC LIMIT 2";
  list<Articulo> articulos;
  this->query(sql, &articulos);
  return new Articulo(articulos.front());
}

Articulo *DbInterface::cargarArticulo(int id)
{
  string sql = "SELECT * FROM productos WHERE id='";
  sql += to_string(id) + "'";
  list<Articulo> articulos;
  this->query(sql, &articulos);
  return new Articulo(articulos.front());
}

void DbInterface::searchBySKU_UPC(string sku_upc, list<Articulo> *articulos)
{
  string sql = "SELECT * FROM productos WHERE sku LIKE '" + sku_upc + "' OR upc LIKE '";
  sql += sku_upc + "' ORDER BY sku" + this->pageLimit;
  this->query(sql, articulos);
}

void DbInterface::searchByName(string nombre, list<Articulo> *articulos)
{
  string sql = "SELECT * FROM productos WHERE nombre LIKE '%";
  sql += nombre + "%' ORDER BY sku ASC" + this->pageLimit;
  this->query(sql, articulos);
}

void DbInterface::listarArticulos(list<Articulo> *articulos) {
  string sql = "SELECT * FROM productos WHERE 1" + this->pageLimit; //just one page
  this->query(sql, articulos);
}

DbInterface::DbInterface() 
{
  sqlite3_initialize();
  if (sqlite3_open("productos.db", &this->DB) != SQLITE_OK)
    throw std::runtime_error("Error Opening DB");
}

DbInterface::~DbInterface() {
  if (this->DB) {
    sqlite3_close(this->DB);
    sqlite3_shutdown();
  }
}

void DbInterface::query(string sql, list<Articulo> *list) {
  int res = sqlite3_prepare_v2(this->DB, sql.c_str(), -1, &this->stmt, 0);
  if (res == SQLITE_OK) {
    while(sqlite3_step(this->stmt) == SQLITE_ROW) { // load all the rows
      Articulo art;
      art.id = sqlite3_column_int(this->stmt, 0);
      art.nombre = (const char *)sqlite3_column_text(this->stmt, 1);
      art.descripcion = (const char *)sqlite3_column_text(this->stmt, 2);
      art.precio = sqlite3_column_double(this->stmt, 3);
      art.sku = (const char *)sqlite3_column_text(this->stmt, 4);
      art.fecha = (const char *)sqlite3_column_text(this->stmt, 5);
      art.upc = (const char *)sqlite3_column_text(this->stmt, 6);
      list->push_front(art);
    }
    res = sqlite3_clear_bindings(this->stmt);
    res = sqlite3_finalize( this->stmt );
  }
}

bool DbInterface::exec(string sql) {
  int res = sqlite3_prepare_v2(this->DB, sql.c_str(), -1, &this->stmt, 0);
  if (res == SQLITE_OK) {
    res = sqlite3_step(this->stmt);
    if (!res) {
      cerr << sqlite3_errmsg(this->DB);
    }
  } else {
    cerr << sqlite3_errmsg(this->DB);
  }
  sqlite3_finalize(this->stmt);
  return (res == SQLITE_OK || res == SQLITE_ROW);
}

bool DbInterface::grabarArticulo(Articulo *art) {
  string sql = "INSERT INTO productos (nombre, descripcion, precio, upc, sku, fecha) VALUES (";
  sql += "'" + art->nombre + "','" + art->descripcion + "','" + to_string(art->precio);
  sql += "','"  + art->upc + "','" + art->sku + "','" + art->fecha + "')";
  return (this->exec(sql));
}