import sys
from os import path

sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )

from elcandata.sale import Sale
import test_db
from expects import *

sale = Sale(test_db.db)
sale.addItem(1, 1000)
sale.addItem(2, 2000)
sale.addItem(3, 1000)

print(sale.getTotal())
