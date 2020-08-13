#include <string>
#include <glbarcode/Factory.h>
#include <glbarcode/RendererSvg.h>

using namespace std;

class Articulo {
  public:
    Articulo();
    Articulo(int id, string name, string description, float price, string sku);
    void setData(int id, string name, string description, float price, string sku);
    int getId();
    string getName();
    float getPrice();
    string getDescription();
    string getSku();
    string getBarcodeFileName();
  protected:
    int id;
    float price;
    string name;
    string description;
    string sku;
    string barcode;
    void generateBarcode();
}