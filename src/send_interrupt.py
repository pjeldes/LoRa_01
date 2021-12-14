import serial
import time

ser = serial.Serial(
    port='com6',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout = None
    #timeout = 1
)

interrupt = "interrupt mesage";

if ser.is_open:
    print("com6 esta abierto")
    ##ser.write(0x01)
    for k in range(0,100):
        time.sleep(1)
        print("interrupt number {}".format(k))
        ser.write(0x01)
    ##ser.write("hello world".encode())