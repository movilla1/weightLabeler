import npyscreen
from elcandata.sale import Sale
from yaenv.core import Env
import datetime


class PosForm(npyscreen.ActionForm):
    def __init__(self):
        self.productId = None
        self.weight = 0

    def create(self):
        self.env = Env('.env')
        self.value = None
        self.venta = Sale()
        self.wgProductSearch = self.add(npyscreen.TitleText, name="UPC/SKU")
        self.wgSearchBtn = self.add(npyscreen.ButtonPress, name="Buscar")
        self.wgAddBtn = self.add(npyscreen.ButtonPress, name="Agregar")
        self.wgList = self.add(npyscreen.MultiLine, name="Productos")
        self.wgSearchBtn.whenPressed = self.searchProduct
        self.wgAddBtn.whenPressed = self.addProduct

    def beforeEditing(self):
        self.parentApp.numVenta += 1
        self.name = "Venta Nro. {:d}".format(
            self.parentApp.numVenta) + " / Fecha: {:s}".format(datetime.date.today())

    def searchProduct(self):
        npyscreen.notify("Not ready yet")

    def addProduct(self):
        self.venta.append({'id': self.productId, 'weight': self.weight})
        self.refresh()

    def on_ok(self):
        self.parentApp.switchFormPrevious()
