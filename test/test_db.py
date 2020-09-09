import sys
from os import path

sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )

from elcandata.products_database import ProductsDatabase
import datetime

if path.exists("test_products.db"):
    db = ProductsDatabase("test_products.db")
else:
    db = ProductsDatabase("test_products.db")
    db.add_record("Test description", "test name", datetime.date.today(), 'testitm123', '77900939213837', 25.0)
    db.add_record("Test description2", "test name2", datetime.date.today(), 'testitm1234', '77900939213838', 50.0)
    db.add_record("Test description3", "test name3", datetime.date.today(), 'testitm1235', '77900939213839', 10.0)