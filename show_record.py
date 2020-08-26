# -*- coding: utf-8 -*-
import npyscreen
import datetime

class ShowRecord(npyscreen.FormWithMenus):
    def create(self):
        self.value = None
        self.wgName = self.add(npyscreen.TitleFixedText, name="Nombre:",)
        self.wgDescription = self.add(npyscreen.TitleFixedText, name="Descripción:")
        self.wgSKU = self.add(npyscreen.TitleFixedText, name="SKU:")
        self.wgUPC = self.add(npyscreen.TitleFixedText, name="UPC:")
        self.wgPrice = self.add(npyscreen.TitleFixedText, name="Precio:")
        self.wgDate = self.add(npyscreen.TitleFixedText, name="Fecha:")
        menu = self.new_menu('Menu Principal')
        menu.addItem(text="Imprimir")
        menu.addItem(text="Editar", onSelect=self.editar)
        menu.addItem(text="Volver/cancelar", onSelect=self.volver)

    def beforeEditing(self):
        if self.value:
            record = self.parentApp.myDatabase.get_record(self.value)
            self.name = "Registro : %s" % record["id"]
            self.record_id = record["id"]
            self.wgName.value = record["nombre"]
            self.wgDescription.value = record["descripcion"]
            self.wgPrice.value = '{:.2f}'.format(record["precio"])
            self.wgSKU.value = record["sku"]
            self.wgUPC.value = '{:s}'.format(str(record["upc"]))
            self.wgDate.value = record["fecha"]

    def volver(self):
        self.parentApp.switchFormPrevious()

    def editar(self):
        self.parentApp.getForm('EDITRECORDFM').value = self.record_id
        self.parentApp.switchForm('EDITRECORDFM')

    def on_ok(self):
        self.volver()
