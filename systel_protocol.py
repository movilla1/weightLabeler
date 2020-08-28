import serial
import time

# Class based on SYSTEL CROMA scale protocol as specified in the manual
# Scale manufacturer manuals: https://systel.com.ar/descargas-manuales-usuario/
class SystelProtocol:
    STX = 0x02
    ETX = 0x03
    ENQ = 0x05
    ACK = 0x06
    NACK = 0x15
    WACK = 0x11

    def __init__(self, port):
        self.port = serial.Serial(port, baudrate=9600,
                                  parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)  # classic 9600,8,n,1
        self.buffer = ''

    def readWeight(self):
        weight = -1
        self.port.write(self.ENQ)
        data = self.WACK
        while(data== self.WACK):
            data = self.port.read()
            time.sleep(1)
        if (data == self.STX):
            while(data != self.ETX):
                data = self.port.read()
                self.buffer += data
            crc = self.port.read()  # last byte after ETX should be CRC
            if crc == self._calc_crc:
                weight = self.buffer
        return weight

    def _calc_crc(self):
        crc = self.STX
        for c in self.buffer[:: 1]:
            crc = crc ^ c
        crc = crc ^ self.ETX
        return crc
