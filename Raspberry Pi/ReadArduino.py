#!/usr/bin/env python
import serial
from serial.tools import list_ports
import random
from threading import Thread
import time
import sys
from sense_hat import SenseHat
import logging
#from logging.handlers import RotatingFileHandler

cycle = 0.0
inRunHours = False
lightState = False

LOG_LEVEL = logging.INFO
#LOG_LEVEL = logging.DEBUG
LOG_FILE = "/var/log/ReadArduino.txt"
#LOG_FILE = "/dev/stdout"
LOG_FORMAT = "%(asctime)s %(levelname)s %(message)s"
logging.basicConfig(filename=LOG_FILE, format=LOG_FORMAT, level=LOG_LEVEL)
#handler = RotatingFileHandler(LOG_FILE, maxBytes = 1024, backupCount = 20)
#logging.addHandler(handler)

#logging.info("This is a test")
#logging.debug("This is a test")
#logging.error("This is a test")

sense = SenseHat()
sense.set_rotation(270)

X = [255, 0, 0]
O = [255, 255, 255]
B = [0, 0, 0]

question_mark = [
    O, O, O, X, X, O, O, O,
    O, O, X, O, O, X, O, O,
    O, O, O, O, O, X, O, O,
    O, O, O, O, X, O, O, O,
    O, O, O, X, O, O, O, O,
    O, O, O, X, O, O, O, O,
    O, O, O, O, O, O, O, O,
    O, O, O, X, O, O, O, O
    ]

sense.set_pixels(question_mark)

time.sleep(2)
blank = [
    B, B, B, B, B, B, B, B,
    B, B, B, B, B, B, B, B,
    B, B, B, B, B, B, B, B,
    B, B, B, B, B, B, B, B,
    B, B, B, B, B, B, B, B,
    B, B, B, B, B, B, B, B,
    B, B, B, B, B, B, B, B,
    B, B, B, B, B, B, B, B
    ]
    
sense.set_pixels(blank)


class TimeMonitor:
    runHours = [0,1,2,3,4,5,6,7,17,18,19,20,21,22,23,24]
    ##runHours = [0,1,2,3,4,5,6,7,11,12,13,17,18,19,20,21,22,23,24]
    
    def __init__(self):
        self._running = True
        self.localTime = time.localtime(time.time())
        
    def terminate(self):
        self._running = False
        
    def run(self):
        global cycle
        global inRunHours
        global lightState
        time.sleep(30) #Five second delay
        cycle = cycle + 5.0
        while self._running:        
            self.localTime = time.localtime(time.time())
            loginfo("The local time is {0}".format(time.asctime( time.localtime(time.time()))))
            
            if self.localTime.tm_hour in self.runHours:
                inRunHours = True
                if not lightState:
                    serialMsg.write(str(7).encode())
                    lightState ^= True
                    time.sleep(2)
                    loginfo("It's dark - turn on the lights")
                    
            else:
                inRunHours = False
                if lightState:
                    serialMsg.write(str(8).encode())
                    lightState ^= True
                    time.sleep(2)
                    loginfo("It's light outside - turn off some lights")
                    
                                 
            time.sleep(15 * 60) #Five second delay
            loginfo( "15 * 60 second Thread cycle+1.0 - ", cycle) 
            

def serial_ports():
    ports = list(list_ports.comports())
    myport = ' '
    for port_no, description, address in ports:
        if 'Circuit Playground Expres' in description:
            loginfo(port_no)
            myport = port_no
    return myport

def loginfo(message):
    sense.set_rotation(270)
    print(message)
    sense.show_message(message)
    logging.info(message)
    time.sleep(10)

def reconnect():
    loginfo("Starting Reconnect")
    count = 0
    maxTries = 1000
    keepTrying = True
    connectionAlive = False
    
    while(connectionAlive == False and keepTrying == True):
        #loginfo("Retried connection " + str(count) + " times!")
        count = count + 1
        try:
            serialMsg = serial.Serial(serial_ports(), 57600, timeout = 1)
            connectionAlive = True
        except:
            connectionAlive = False
            #loginfo("Unexpected error:", sys.exc_info()[0])
            time.sleep(2)
            #loginfo("Didn't work this time!");
            if(count >= maxTries):
                keepTrying = False
            else:
                #loginfo("Sleeping for 5 seconds")
                time.sleep(5)
    #loginfo("Ending Reconnect")
    return serialMsg


#runHours

lightState = False
inRunHours = False

#Create Class
timeMonitor = TimeMonitor()
#Create Thread
timeMonitorThread = Thread(target=timeMonitor.run)
#Start Thread
timeMonitorThread.start()
while True:
    try:
        rawMsg = serialMsg.readline()
        message = (rawMsg.decode().strip())
        
        if(message[:5] == "tempF"):
            loginfo(message);
            tempTxt,tempVal = message.split(": ")
            tempVal = float(tempVal)
            if inRunHours:
                tempStr = "7"
                lightState = True
            else:
                if (tempVal < 50):
                    tempStr = "7"
                    lightState = True
                elif (tempVal < 70):
                    tempStr = "8"
                    lightState = False

            
            loginfo("temp code " + tempStr)
            serialMsg.write(tempStr.encode())
        elif (len(message) == 0):
            time.sleep(1)
        
        else:
            loginfo(message)
            
        
    except:
        serialMsg = reconnect()
        
timeMonitor.terminate()
