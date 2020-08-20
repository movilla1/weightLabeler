#include "pesaje.h"
//boton para leer peso
//boton para imprimir etiqueta
//boton para menu principal
#define MENUSIZE 4

Pesaje::Pesaje(DbInterface *db) {
    //dibujar pantalla con peso y articulo
    char *options[10] ={
        "Buscar",
        "Leer Peso",
        "Imprimir",
        "Volver",
    };
    this->db = db;
    this->ventana = new Dialogo(options, MENUSIZE);
    this->articulo = db->cargarPrimerArticulo();
    this->ventana->setTitle("Imprimir Etiqueta");
    this->dlgArea = this->ventana->getDialogArea();
    box(this->dlgArea, 0, 0);
    this->draw();
}

void Pesaje::run() {
    unsigned char selection = this->ventana->runDialog();
    switch (selection) {
    case 0:
      this->buscarSKU();
      this->draw();
      break;
    case 1:
    case 2:
        break;
    case 3:
        this->running = false;
        break;
    }
}

Pesaje::~Pesaje() {
  //delete(this->ventana);
}

void Pesaje::draw() {
  mvwprintw(this->dlgArea, 1, 1, "Producto:");
  mvwprintw(this->dlgArea, 1, 15, this->articulo->nombre.c_str());
  mvwprintw(this->dlgArea, 2, 1, "SKU:");
  mvwprintw(this->dlgArea, 2, 15, this->articulo->sku.c_str());
  mvwprintw(this->dlgArea, 3, 1, "Precio x Kg: $");
  mvwprintw(this->dlgArea, 3, 15, this->articulo->price_rounded().c_str());
  wattron(this->dlgArea, A_BOLD);
  mvwprintw(this->dlgArea, 1, 45, "Peso en Kg");
  wattroff(this->dlgArea, A_BOLD);
  wrefresh(this->dlgArea);
  refresh();
}

void Pesaje::buscarSKU() {
  char input[30];
  list<Articulo> articulos;
  mvwprintw(this->dlgArea,5,1,"Ingrese SKU/UPC:");
  echo();
  mvwgetnstr(this->dlgArea, 5, 18, input, 29);
  noecho();
  this->db->searchBySKU_UPC(input, &articulos);
  if (articulos.size() >= 1) {
    this->articulo = &articulos.front();
  } else {
    mvwprintw(this->dlgArea, 10,10, "No se encontro el articulo, pulse una tecla para continuar");
    wrefresh(this->dlgArea);
    int i = getchar();
  }
  wclear(this->dlgArea);
}