from blabel import LabelWriter
import npyscreen


class PrintRecord(npyscreen.ActionForm):
    def create(self):
        self.value = None
        self.wgName = self.add(npyscreen.TitleFixedText, name="Nombre:",)
        self.wgDescription = self.add(
            npyscreen.TitleFixedText, name="Descripción:")
        self.wgSKU = self.add(npyscreen.TitleFixedText, name="SKU:")
        self.wgUPC = self.add(npyscreen.TitleFixedText, name="UPC:")
        self.wgPrice = self.add(npyscreen.TitleFixedText, name="Precio:")
        self.wgReadWeight = self.add(
            npyscreen.ButtonPress, name="Leer Peso", relx=2, rely=8)
        self.wgWeight = self.add(npyscreen.TitleFixedText, name="Peso:")
        self.wgReadWeight.whenPressed = self.readWeight

    def beforeEditing(self):
        if self.value:
            record = self.parentApp.myDatabase.get_record(self.value)
            self.name = "Articulo : %s" % record["id"]
            self.record_id = record["id"]
            self.wgName.value = record["nombre"]
            self.wgDescription.value = record["descripcion"]
            self.wgPrice.value = '{:.2f}'.format(record["precio"])
            self.wgSKU.value = record["sku"]
            self.wgUPC.value = '{:s}'.format(str(record["upc"]))
            self.wgWeight.value = 0

    def on_ok(self):
        npyscreen.notify_wait("Not ready yet")
        self.parentApp.switchFormPrevious()

    def on_cancel(self):
        self.parentApp.switchFormPrevious()

    def readWeight(self):
        self.wgWeight.value = 123  # dummy data now
        self.getBarCode()

    def getBarCode(self):
        label_writer = LabelWriter("item_template.html",
                                   default_stylesheets=("style.css",))
        records = [
            dict(sample_id=self.wgUPC.value, sample_weight='{:0.2f}'.format(
                self.wgWeight.value), sample_name=self.wgSKU.value)
        ]

        label_writer.write_labels(
            records, target='tmp/barcode' + self.wgSKU.value + '.pdf')
