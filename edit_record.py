# -*- coding: utf-8 -*-
import npyscreen
import datetime

class EditRecord(npyscreen.ActionForm):
    def create(self):
        self.value = None
        self.wgName = self.add(npyscreen.TitleText, name="Nombre:",)
        self.wgDescription = self.add(npyscreen.TitleText, name="Descripción:")
        self.wgSKU = self.add(npyscreen.TitleText, name="SKU:")
        self.wgUPC = self.add(npyscreen.TitleText, name="UPC:")
        self.wgPrice = self.add(npyscreen.TitleText, name="Precio:")
        self.wgDate = self.add(npyscreen.TitleText, name="Fecha:")

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
            self.wgDate.value = '{:s}'.format(str(record["fecha"]))
        else:
            self.name = "New Record"
            self.record_id = ''
            self.wgName.value = ''
            self.wgDescription.value = ''
            self.wgPrice.value = ''
            self.wgSKU.value = ''
            self.wgUPC.value = ''
            self.wgDate.value = datetime.date.today().isoformat()

    def on_ok(self):
        if self.record_id:  # We are editing an existing record
            self.parentApp.myDatabase.update_record(
                self.record_id,
                nombre=self.wgName.value,
                descripcion=self.wgDescription.value,
                precio=self.wgPrice.value,
                sku=self.wgSKU.value,
                upc=self.wgUPC.value,
                fecha=self.wgDate.value,
            )
        else:  # We are adding a new record.
            self.parentApp.myDatabase.add_record(
                nombre=self.wgName.value,
                descripcion=self.wgDescription.value,
                precio=self.wgPrice.value,
                sku=self.wgSKU.value,
                upc=self.wgUPC.value,
                fecha=self.wgDate.value,
            )
        self.parentApp.switchFormPrevious()

    def on_cancel(self):
        self.parentApp.switchFormPrevious()
