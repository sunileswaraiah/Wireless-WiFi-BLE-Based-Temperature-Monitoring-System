from bluetooth import *
import locale
from locale import atof
import re
import time
from Adafruit_IO import Client,Feed

def input_and_send():
    print("\nType something\n")
    while True:
        data = input()
        if len(data) == 0: break
        sock.send(data)
        sock.send("\n")
        
def rx_and_echo():
    sock.send("\nsend data\n")
    while True:
        data = sock.recv(buf_size)
        temp = data.decode("utf-8")
        if data[0] != 13:
            value = float(temp)
            print ("Temperature : " )
            print(value)
            temperature = value
            aio.send(temp_feed.key, str(temperature))



#MAC address of ESP32
addr = "F0:08:D1:D3:07:26"
#uuid = "94f39d29-7d6d-437d-973b-fba39e49d4ee"
#service_matches = find_service( uuid = uuid, address = addr )
service_matches = find_service( address = addr )

buf_size = 1024;

ADAFRUIT_IO_KEY = 'Key from ada fruit'
ADAFRUIT_IO_USERNAME = 'User Name from ada fruit'

if len(service_matches) == 0:
    print("couldn't find the SampleServer service =(")
    sys.exit(0)

for s in range(len(service_matches)):
    print("\nservice_matches: [" + str(s) + "]:")
    print(service_matches[s])
    
first_match = service_matches[0]
port = first_match["port"]
name = first_match["name"]
host = first_match["host"]

port=1
print("connecting to \"%s\" on %s, port %s" % (name, host, port))

# Create the client socket
sock=BluetoothSocket(RFCOMM)
sock.connect((host, port))

print("connected")

aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

temp_feed = aio.feeds('temperature')

#input_and_send()
rx_and_echo()

sock.close()
print("\n--- bye ---\n")
