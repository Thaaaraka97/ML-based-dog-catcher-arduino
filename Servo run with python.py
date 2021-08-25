
import serial
ser1 = serial.Serial('COM7',9600)


def ss():
    
    ser1.write('1'.encode())
    
t=0
while(t<200000):
    if(t%10==0):
        print (t)
    t+=1

ss()

print("Animal Captured!!")
