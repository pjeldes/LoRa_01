import serial, time
se1 = serial.Serial("com3")
se2 = serial.Serial("com7")
if se1.is_open and se2.is_open:
    print("s1 y s2 estan abiertos")
while True:
    time.sleep(1)
    ## todas las lineas llevan \n, de no llevar esta indicacion esta no imprime
    if (se2.write(b'hello \n')):
        print("write True")
    cadena = se1.readline()
    print(cadena)

