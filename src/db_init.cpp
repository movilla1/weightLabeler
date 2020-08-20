#include <sqlite3.h>
#include <iostream>
#include <stdlib.h>

int main(int argc, char **argv)
{
  sqlite3 *DB;
  std::string sql = "CREATE TABLE productos ( "
                    "descripcion  TEXT NOT NULL, "
                    "fecha DATE,"
                    "id INT PRIMARY KEY NOT NULL, "
                    "nombre TEXT NOT NULL, "
                    "precio_kilogramo REAL, "
                    "sku CHAR(20) "
                    " );";
  int exit = 0;
  exit = sqlite3_open("productos.db", &DB);
  char *messaggeError;
  exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

  if (exit != SQLITE_OK)
  {
    std::cerr << "Error Create Table" << std::endl;
    std::cerr << messaggeError << std::endl;
    sqlite3_free(messaggeError);
  }
  else
    std::cout << "Table created Successfully" << std::endl;
  sqlite3_close(DB);
  return (0);
}