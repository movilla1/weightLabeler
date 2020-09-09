import sys
from os import path

sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )

from elcandata.systel_protocol import SystelProtocol

def test():
    st = SystelProtocol('/dev/ttyUSB0')
    p = st.readWeight()
    print(int(p))

if __name__ == "__main__":
    test()