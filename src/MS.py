import serial, time
ser = serial.Serial(
    port='com5',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout = None
    #timeout = 1
)
packet = bytearray()
cmd_get_param = bytearray()
params = bytearray()

cmd_get_param.append(0xc1)
cmd_get_param.append(0xc1)
cmd_get_param.append(0xc1)

## {0xC0, 0x00, 0x00, 0x3D, 0x17, 0xC4}
packet.append(0xC0)
packet.append(0x00)
packet.append(0x00)
packet.append(0x3D)
packet.append(0x17)
packet.append(0xC4)


if ser.is_open:
    print("s1 esta abierto")
    print("cmd {}".format(cmd_get_param))


for k in range(0,10):
    ser.write(cmd_get_param)
    time.sleep(0.1)
    params = ser.read()

    print("params: {}".format(params))
ser.close()
if ser.closed:
    print("com5 cerrado")