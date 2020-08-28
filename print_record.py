from blabel import LabelWriter
from yaenv.core import Env
from systel_protocol import SystelProtocol
import npyscreen
import subprocess


class PrintRecord(npyscreen.ActionForm):
    def create(self):
        self.env = Env('.env')
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
        if (self.wgWeight.value):
            # print
            subprocess.call("/usr/bin/lpr " + self._barcodeFilename()) # send to the default printer.
        else:
            npyscreen.notify_wait("Debe leer el peso antes de poder imprimir")
        self.parentApp.switchFormPrevious()

    def on_cancel(self):
        self.parentApp.switchFormPrevious()

    def readWeight(self):
        weight = self._readSerialScale()
        if (weight != -1):
            self.wgWeight.value = str(weight)
            self._getBarCode()

    def _getBarCode(self):
        label_writer = LabelWriter("item_template.html",
                                   default_stylesheets=("style.css",))
        records = [
            dict(sample_id=self.wgUPC.value, sample_weight='{:0.2f}'.format(
                self.wgWeight.value), sample_name=self.wgSKU.value)
        ]

        label_writer.write_labels(
            records, target=self._barcodeFilename())

    def _barcodeFilename(self):
        fname = 'tmp/barcode' + self.wgSKU.value + '.pdf'
        return fname

    def _readSerialScale(self):
        port = self.env.get('SERIALPORT', '/dev/ttyUSB0')
        proto = SystelProtocol(port)
        weight = proto.readWeight()
        return weight