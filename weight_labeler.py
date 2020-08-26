#!/usr/bin/env python

import npyscreen
import sqlite3
import datetime
from products_database import ProductsDatabase
from edit_record import EditRecord
from record_list import RecordList
from show_record import ShowRecord


class RecordListDisplay(npyscreen.FormMuttActiveWithMenus):
    MAIN_WIDGET_CLASS = RecordList

    def __init__(self, *args, **keywords):
        menu = self.new_menu("Principal")
        menu.addItem("Filtrar", onSelect=self.filter)
        menu.addItem("Ayuda", onSelect=self.show_help)
        menu.addItem("Salir", onSelect=self.do_exit)
        super(RecordListDisplay, self).__init__(*args, **keywords)

    def beforeEditing(self):
        self.update_list()

    def update_list(self):
        self.wMain.values = self.parentApp.myDatabase.list_all_records()
        self.wMain.display()

    def do_exit(self, *args, **keywords):
        message_to_display = 'Seguro que desea salir?'
        conf = npyscreen.notify_yes_no(
            message_to_display, title='Confirmar Salida')
        if conf:
            self.parentApp.switchForm(None)

    def show_help(self, *args, **kwd):
        message = "\
        Para editar un articulo pulse sobre el mismo y luego Ctrl+E y proceda a editar.\n\
        Para agregar un nuevo articulo use Ctrl+A.\n\
        Borre seleccionando un articulo y luego Ctrl+D.\n\
        Imprima una etiqueta desde la interfaz de mostrar y pulse Ctrl+X para ver el menu.\n"
        npyscreen.notify_confirm(message)

    def filter(self, *args, **kwd):
        self.wMain.values = self.parentApp.myDatabase.list_records_matching(
            kwd)
        self.wMain.display()


class ProductLabelerApplication(npyscreen.NPSAppManaged):
    def onStart(self):
        self.myDatabase = ProductsDatabase()
        self.addForm("MAIN", RecordListDisplay)
        self.addForm("EDITRECORDFM", EditRecord)
        self.addForm("SHOWRECORDFM", ShowRecord)


if __name__ == '__main__':
    myApp = ProductLabelerApplication()
    myApp.run()
