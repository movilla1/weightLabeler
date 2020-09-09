import sqlite3
import sys
from pprint import pprint


class ProductsDatabase(object):
    def __init__(self, filename="productos.db"):
        self.dbfilename = filename
        db = sqlite3.connect(self.dbfilename)
        c = db.cursor()
        c.execute(
            "CREATE TABLE IF NOT EXISTS productos ( "
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "nombre TEXT NOT NULL, "
            "descripcion  TEXT NOT NULL, "
            "precio REAL, "
            "sku CHAR(20) NOT NULL, "
            "upc CHAR(20),"
            "fecha CHAR(10)"
            " )"
        )
        db.commit()
        c.close()

    def add_record(self, descripcion='', nombre='', fecha='', sku='', upc='', precio=0.0):
        db = sqlite3.connect(self.dbfilename)
        c = db.cursor()
        c.execute('INSERT INTO productos(descripcion, fecha, nombre, precio, sku, upc) \
                    VALUES(?,?,?,?,?,?)', (descripcion, fecha, nombre, precio, sku, upc))
        db.commit()
        c.close()

    def update_record(self, record_id,  descripcion='', nombre='', fecha='', sku='', upc='', precio=0.0):
        db = sqlite3.connect(self.dbfilename)
        c = db.cursor()
        c.execute('UPDATE productos SET nombre=?, descripcion=?, fecha=?, precio=?, sku=?, upc=? \
                    WHERE id=?', (nombre, descripcion, fecha, precio, sku, upc, record_id))
        db.commit()
        c.close()

    def delete_record(self, record_id):
        db = sqlite3.connect(self.dbfilename)
        c = db.cursor()
        c.execute('DELETE FROM productos WHERE id=?', (record_id,))
        db.commit()
        c.close()

    def list_all_records(self, ):
        db = sqlite3.connect(self.dbfilename)
        c = db.cursor()
        c.execute('SELECT * FROM PRODUCTOS')
        records = c.fetchall()
        c.close()
        return records

    def list_records_matching(self, kwds):
        db = sqlite3.connect(self.dbfilename)
        c = db.cursor()
        c.execute("SELECT * FROM productos WHERE sku LIKE ? OR upc LIKE ?",
                  (kwds + "%", kwds + "%"))
        records = c.fetchall()
        c.close()
        return records

    def get_record(self, record_id):
        db = sqlite3.connect(self.dbfilename)
        db.row_factory = dict_factory
        c = db.cursor()
        c.execute('SELECT * FROM productos WHERE id=?', (record_id,))
        records = c.fetchone()
        c.close()
        return records


def dict_factory(cursor, row):
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d
