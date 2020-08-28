# -*- coding: utf-8 -*-
import npyscreen
import datetime


class ShowRecord(npyscreen.FormBaseNewWithMenus):
    def create(self):
        self.value = None
        self.wgName = self.add(npyscreen.TitleFixedText, name="Nombre:",)
        self.wgDescription = self.add(
            npyscreen.TitleFixedText, name="Descripción:")
        self.wgSKU = self.add(npyscreen.TitleFixedText, name="SKU:")
        self.wgUPC = self.add(npyscreen.TitleFixedText, name="UPC:")
        self.wgPrice = self.add(npyscreen.TitleFixedText, name="Precio:")
        self.wgDate = self.add(npyscreen.TitleFixedText, name="Fecha:")
        self.wgOk = self.add(npyscreen.ButtonPress,
                             name="Cerrar", relx=67, rely=21)
        menu = self.new_menu('Menu Principal')
        menu.addItem(text="Imprimir")
        menu.addItem(text="Editar", onSelect=self.editar)
        menu.addItem(text="Volver", onSelect=self.volver)
        menu.addItem(text="Cancelar/Cerrar Menu")
        self.add_handlers({
            "^E": self.when_edit,
            "^P": self.when_weight_print
        })

    def beforeEditing(self):
        self.wgOk.whenPressed = self.volver
        if self.value:
            record = self.parentApp.myDatabase.get_record(self.value)
            self.name = "Detalle del Registro : %s" % record["id"]
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
        npyscreen.notify("OK PRESS")
        self.parentApp.switchFormPrevious()

    def when_edit(self, *arg, **kwds):
        self.editar()

    def when_weight_print(self, *arg, **kwds):
        self.parentApp.getForm('PRINTRECORDFM').value = self.record_id
        self.parentApp.switchForm('PRINTRECORDFM')
