#include "modificar_articulo.h"
#define BUSCAR_MENU_SIZE 2

ModificarArticulo::ModificarArticulo(DbInterface *db) {
    char *options[10] ={
        "Grabar",
        "Volver/Cancelar",
    };
    this->ventana = new Dialogo(options, BUSCAR_MENU_SIZE);
    this->ventana->setTitle("Editar Articulo");
    this->running = true;
    this->db = db;
}

void ModificarArticulo::run() {
    unsigned char selection = this->ventana->runDialog();
    switch (selection) {
    case 0:
        break;
    case 1:
        this->running = false;
        break;
    }
}

ModificarArticulo::~ModificarArticulo() {
  delete(this->ventana);
}
