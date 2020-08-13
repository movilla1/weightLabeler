#include "articulo.h"

Articulo::Articulo()
{
  this->id = 0;
  this->price = 0.0;
}

Articulo::Articulo(int id, string name, string description, float price, string sku)
{
  this->id = id;
  this->price = price;
  this->name = name;
  this->description = description;
  this->sku = sku;
  this->generateBarcode();
}

void Articulo::setData(int id, string name, string description, float price, string sku)
{
  this->id = id;
  this->price = price;
  this->name = name;
  this->description = description;
  this->sku = sku;
  this->generateBarcode();
}

int Articulo::getId()
{
  return this->id;
}

string Articulo::getName()
{
  return this->name;
}

float Articulo::getPrice()
{
  return this->price;
}

string Articulo::getDescription()
{
  return this->description;
}

string Articulo::getSku()
{
  return this->sku;
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