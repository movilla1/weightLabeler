from elcandata.products_database import ProductsDatabase
from pprint import pprint


class Sale():
    def __init__(self, db):
        self._sale = dict(
            items=[],
            total=0
        )  # use a dictionary for now
        self.db = db

    def addItem(self, item_id, weight=0):
        item = self.db.get_record(item_id)
        if item:
            subtotal = (item['precio'] / 1000.0) * weight
            self._sale["items"].append({
                'item': item,
                'weight': weight,
                'subtotal': subtotal
            })
            self._sale["total"] += subtotal

    def removeItem(self, item_id):
        for item in self._sale["items"]:
            if item["id"] == item_id:
                self._sale["items"].remove(item)
                self._sale["total"] -= item["subtotal"]

    def listItems(self):
        return self._sale["items"]

    def getTotal(self):
        return self._sale["total"]
