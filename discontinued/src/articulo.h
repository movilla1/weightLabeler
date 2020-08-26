#ifndef _ARTICULO_H
#define _ARTICULO_H 1
#include <string>
#include <ctime>
#include <glbarcode/Factory.h>
#include <glbarcode/RendererSvg.h>
#include "common.h"

using namespace std;

class Articulo {
  public:
    int id;
    float precio;
    string nombre;
    string descripcion;
    string sku;
    string fecha;
    string upc;
    string price_rounded();
    Articulo();
    Articulo(Articulo *art); //copy constructor
    Articulo(int id, string name, string description, float price, string sku);
    string getBarcodeFileName();

  protected:
    string barcode;
    void generateBarcode();
};
#endif