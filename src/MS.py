import serial, time
se1 = serial.Serial("com3")
if se1.is_open:
    print("s1 esta abierto")
while True:
    time.sleep(1)
    ## todas las lineas llevan \n, de no llevar esta indicacion esta no imprime
    cadena = se1.readline()
    print(cadena[1:])
