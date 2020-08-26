# -*- coding: utf-8 -*-
import npyscreen
import datetime


class FilterForm(npyscreen.ActionPopup):
    def create(self):
        self.value = None
        self.wgFilter = self.add(npyscreen.TitleText, name="SKU o UPC:")
        self.wfClear = self.add(npyscreen.ButtonPress, name="Clear All Filters", relx=5, rely=5)
        self.wfClear.whenPressed = self.clearFilters
        self.OK_BUTTON_TEXT = "Filtrar"

    def beforeEditing(self):
        self.wgFilter.value = self.parentApp.keywords

    def on_ok(self):
        self.parentApp.keywords = self.wgFilter.value
        self.parentApp.switchFormPrevious()

    def on_cancel(self):
        self.parentApp.switchFormPrevious()

    def clearFilters(self):
        self.parentApp.keywords = ''
        self.parentApp.switchFormPrevious()
