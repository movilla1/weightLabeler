# -*- coding: utf-8 -*-
import npyscreen


class RecordList(npyscreen.MultiLineAction):
    def __init__(self, *args, **keywords):
        super(RecordList, self).__init__(*args, **keywords)
        self.add_handlers({
            "^A": self.when_add_record,
            "^E": self.when_edit_record,
            "^D": self.when_delete_record,
            "^P": self.when_weight_print,
            "^F": self.when_filter,
        })

    def display_value(self, vl):
        return '{:5} - {:20} - {:15} - {:8} - {:>15}'.format(vl[0], vl[1], vl[4], vl[3], vl[5])

    def actionHighlighted(self, act_on_this, keypress):
        self.parent.parentApp.getForm('SHOWRECORDFM').value = act_on_this[0]
        self.parent.parentApp.switchForm('SHOWRECORDFM')

    def when_add_record(self, *args, **keywords):
        self.parent.parentApp.getForm('EDITRECORDFM').value = None
        self.parent.parentApp.switchForm('EDITRECORDFM')

    def when_delete_record(self, *args, **keywords):
        self.parent.parentApp.myDatabase.delete_record(
            self.values[self.cursor_line][0])
        self.parent.update_list()

    def when_weight_print(self, vl):
        print("Not ready yet")
        #self.parent.parentApp.getForm("PRINTRECORDFM").value = vl[0]
        # self.parent.parentApp.switchForm("PRINTRECORDFM")

    def when_filter(self, vl):
        self.parent.parentApp.getForm(
            "FILTERFORM").value = self.parent.parentApp.keywords
        self.parent.parentApp.switchForm("FILTERFORM")

    def when_edit_record(self, act_on_this):
        self.parent.parentApp.getForm('EDITRECORDFM').value = act_on_this
        self.parent.parentApp.switchForm('EDITRECORDFM')
