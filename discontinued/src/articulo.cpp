#include "articulo.h"

Articulo::Articulo()
{
  this->id = 0;
  this->precio = 0.0;
  this->nombre = "";
  this->descripcion = "";
  this->sku = "";
  this->fecha = getCurrentDate();
}

Articulo::Articulo(Articulo *src) {
  this->id = src->id;
  this->precio = src->precio;
  this->nombre = src->nombre;
  this->descripcion = src->descripcion;
  this->sku = src->sku;
  this->fecha = src->fecha;
  this->upc = src->upc;
  this->generateBarcode();
}

Articulo::Articulo(int id, string name, string description, float precio, string sku)
{
  this->id = id;
  this->precio = precio;
  this->nombre = name;
  this->descripcion = description;
  this->sku = sku;
  this->generateBarcode();
}

string Articulo::getBarcodeFileName()
{
  return "tmp/" + this->sku + ".svg";
}

void Articulo::generateBarcode()
{
  glbarcode::Barcode *bc = glbarcode::Factory::createBarcode("code39");
  bc->setChecksum(true).setShowText(true).build(this->sku, 566, 144);
  bc->render(glbarcode::RendererSvg().setFilename(this->getBarcodeFileName()));
  delete (bc);
}

string Articulo::price_rounded() {
  char price_rounded[20];
  sprintf(price_rounded, "%.2f", this->precio);
  return string(price_rounded);
}