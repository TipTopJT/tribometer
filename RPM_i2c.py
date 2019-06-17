#!/usr/bin/env python
from time import sleep
import smbus2
import struct
import array
bus = smbus2.SMBus(1)
address = 0x08

# Give the I2C device time to settle
#sleep(2)
#print(888)
index=1


def RPM():
    data = bus.read_i2c_block_data(address, 0, 4)
    DATA=struct.unpack('i', bytes(data))
    return DATA[0]
print(RPM())
    