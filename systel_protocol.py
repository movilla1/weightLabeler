import serial
import time

# Class based on SYSTEL CROMA scale protocol as specified in the manual
# Scale manufacturer manuals: https://systel.com.ar/descargas-manuales-usuario/
class SystelProtocol:
    STX = b'\x02'
    ETX = b'\x03'
    ENQ = b'\x05'
    ACK = b'\x06'
    NACK = b'\x15'
    WACK = b'\x11'

    def __init__(self, port):
        self.port = port
        self.buffer = bytearray()

    def readWeight(self):
        port = serial.Serial(self.port, baudrate=9600,
                              parity=serial.PARITY_NONE,
                              stopbits=serial.STOPBITS_ONE,
                              bytesize=serial.EIGHTBITS,
                              timeout=2)  # classic 9600,8,n,1
        if (port.is_open == False):
            port.close()
            port.open()
        weight = -1
        port.write(self.ENQ)
        data = port.read()
        if (data == self.STX):
            while(data != self.ETX):
                data = port.read()
                self.buffer += data
            crc = port.read()  # last byte after ETX should be CRC
            port.write(self.ACK)
            if ord(crc) == self._calc_crc():
                weight = self._getWeight()
        return weight

    def _calc_crc(self):
        crc = 0x02
        for c in self.buffer:
            crc = crc ^ c
        return crc

    def _getWeight(self):
        self.buffer.pop()
        return (self.buffer.decode('ascii'))