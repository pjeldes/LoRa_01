import serial, time
se1 = serial.Serial("/dev/ttys0")
##se2 = serial.Serial("com7")
read = bytearray()
if se1.is_open:
    print("com5 abierto")
while True:
    time.sleep(1)
    ## todas las lineas llevan \n, de no llevar esta indicacion esta no imprime
    read = se1.read()
    print("recive params: {}".format(read))

