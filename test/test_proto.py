from systel_protocol import SystelProtocol

st = SystelProtocol('/dev/ttyUSB0')
p = st.readWeight()
print(int(p))