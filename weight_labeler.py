#!/usr/bin/env python3

import npyscreen
import sqlite3
import datetime

from products_database import ProductsDatabase
from edit_record import EditRecord
from record_list import RecordList
from show_record import ShowRecord
from filter_form import FilterForm
from print_record import PrintRecord

class RecordListDisplay(npyscreen.FormMuttActiveWithMenus):
    MAIN_WIDGET_CLASS = RecordList
    STATUS_WIDGET_CLASS = npyscreen.Textfield
    STATUS_WIDGET_X_OFFSET = 0

    def __init__(self, *args, **keywords):
        menu = self.new_menu("Principal")
        menu.addItem("Filtrar", onSelect=self.filter)
        menu.addItem("Salir", onSelect=self.do_exit)
        super(RecordListDisplay, self).__init__(*args, **keywords)
        self.help = "\
        Para editar un articulo pulse sobre el mismo y luego Ctrl+E y proceda a editar.\n\
        Para agregar un nuevo articulo use Ctrl+A.\n\
        Borre seleccionando un articulo y luego Ctrl+D.\n\
        Imprima una etiqueta seleccionando el artículo y luego Ctrl+P.\n"

    def beforeEditing(self):
        self.wStatus1.value = "Elcan Weight Labeler v1.0.0b"
        self.wStatus2.value = "(c) 2020 - ElcanSoftware - Mario O. Villarroel"
        self.update_list()

    def update_list(self):
        if not self.parentApp.keywords:
            self.wMain.values = self.parentApp.myDatabase.list_all_records()
        else:
            self.wMain.values = self.parentApp.myDatabase.list_records_matching(self.parentApp.keywords)
        self.wMain.display()

    def do_exit(self, *args, **keywords):
        message_to_display = 'Seguro que desea salir?'
        conf = npyscreen.notify_yes_no(
            message_to_display, title='Confirmar Salida')
        if conf:
            self.parentApp.switchForm(None)

    def filter(self, *args, **kwd):
        self.parentApp.getForm("FILTERFORM").value = self.parentApp.keywords
        self.parentApp.switchForm("FILTERFORM")


class ProductLabelerApplication(npyscreen.NPSAppManaged):
    def onStart(self):
        self.keywords = ''
        self.myDatabase = ProductsDatabase()
        self.addForm("MAIN", RecordListDisplay)
        self.addForm("EDITRECORDFM", EditRecord)
        self.addForm("SHOWRECORDFM", ShowRecord)
        self.addForm("FILTERFORM", FilterForm)
        self.addForm("PRINTRECORDFM", PrintRecord)
        npyscreen.setTheme(npyscreen.Themes.ColorfulTheme)


if __name__ == '__main__':
    myApp = ProductLabelerApplication()
    myApp.run()
