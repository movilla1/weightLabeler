#include "listar_articulos.h"
#define BUSCAR_MENU_SIZE 2
#define PAGE_SIZE 12

// Column positions
#define POS_ID 1
#define POS_NAME 5
#define POS_SKU 28
#define POS_UPC 42
#define POS_PRIC 58

ListarArticulos::ListarArticulos(DbInterface *db) {
    char *options[9] ={
        "Filtrar",
        "Volver",
    };
    this->ventana = new Dialogo(options, BUSCAR_MENU_SIZE);
    this->ventana->setTitle("Listar Articulos");
    this->running = true;
    this->articulo = articulo;
    this->db = db;
    db->listarArticulos(&this->articulos);
    this->dlgArea = this->ventana->getDialogArea();
    this->draw();
}

void ListarArticulos::run() {
    unsigned char selection = this->ventana->runDialog();
    switch (selection) {
    case 0:
        break;
    case 1:
        this->running = false;
        break;
    }
}

ListarArticulos::~ListarArticulos() {
  delete(this->ventana);
}

void ListarArticulos::draw() {
  Articulo articulo;
  box(this->dlgArea, 0, 0);
  wattron(this->dlgArea, A_BOLD);
  mvwprintw(this->dlgArea, 1, POS_ID, "ID");
  mvwprintw(this->dlgArea, 1, POS_NAME, "Nombre");
  mvwprintw(this->dlgArea, 1, POS_SKU, "SKU");
  mvwprintw(this->dlgArea, 1, POS_UPC, "UPC");
  mvwprintw(this->dlgArea, 1, POS_PRIC, "Precio");
  wattroff(this->dlgArea, A_BOLD);
  list <Articulo> :: iterator it;
  
  int i = 0;
  for (it=this->articulos.begin(); it != this->articulos.end(); it++) {
    articulo = *it;
    mvwprintw(this->dlgArea,2+i, POS_ID, to_string(articulo.id).c_str());
    mvwprintw(this->dlgArea,2+i, POS_NAME, articulo.nombre.c_str());
    mvwprintw(this->dlgArea,2+i, POS_SKU, articulo.sku.c_str());
    mvwprintw(this->dlgArea,2+i, POS_UPC, articulo.upc.c_str());
    mvwprintw(this->dlgArea,2+i, POS_PRIC, "$");
    mvwprintw(this->dlgArea,2+i, POS_PRIC+2, articulo.price_rounded().c_str());
    i++;
  }
  wrefresh(this->dlgArea);
}