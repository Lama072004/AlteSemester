# This version runs with the theremin but it struggles when you hit the "Stimmung +/-" button. 
# Somehow, the thread waitForNotifications runs into a failure. The tuning usually gets set
# for the last time. The window is non responisive afterwards. BLE stack though is still running.
# Notifications can be seen in the terminal. 
#

import sys
import threading
import time

from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QLabel
from PyQt5 import QtCore
from bluepy.btle import DefaultDelegate,Scanner, Peripheral, ADDR_TYPE_PUBLIC, AssignedNumbers, UUID

#user imports
from pitches import noteMapping 
from configuration import *

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)
        self.device = None

    def handleDiscovery(self, scanEntry, isNewDev, isNewData):
        print("Discovered device", scanEntry.addr)

#define class to handle notifications, call to label in window
class PeripheralDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleNotification(self, cHandle, data):
        parsed = list(data)
        print(f"Received new note {parsed[1]}")
        if len(parsed) > 1:
            global window
            try: 
                window.playedNoteLabel.setText(f"Note {noteMapping[parsed[1]]}")
            except Exception:
                print("Note text setting failed.")
            print(f"Played note {parsed[1]}")

#scan for availaible BLE devices
scanner = Scanner().withDelegate(ScanDelegate())
scanEntries = scanner.scan(10)

device = None

for entry in scanEntries:
    name = entry.getValueText(9) 
    if name == "Theremin_v0_1":
        print(f"Found Theremin_v0_1 - address={entry.addr}")
        try: 
            device = Peripheral(entry.addr, ADDR_TYPE_PUBLIC)
        except Exception:
            print("Unknown Device connection failure")
            exit(-4)


if device:
    
    device.setDelegate(PeripheralDelegate())

    thereminService = device.getServiceByUUID(thereminServcieUUID)
    # TODO: implement device info read
    # deviceIDService = device.getServiceByUUID(deviceIDServiceUUID) 

    actualNoteChar = thereminService.getCharacteristics(thereminActualNoteCharUUID)[0]
    baseNoteChar = thereminService.getCharacteristics(thereminBaseNoteCharUUID)[0]

    # read of device id is not implemented. Bytes are being read already, but there is no conversion to string 
    # manufactuererChar = deviceIDService.getCharacteristics(manufacturereNameUUID)[0]
    # modelNumberChar = deviceIDService.getCharacteristics(modelNumberUUID)[0]
    # manufacturer = int.from_bytes(device.readCharacteristic(manufactuererChar.valHandle), byteorder='little')
    # str.from_bytes does not exist. 
    # modelNumber = str.from_bytes(device.readCharacteristic(modelNumberChar.valHandle), byteorder='little')
    
    # print(f"Connected to\nManufacturerer: {manufacturer}\nModel: {modelNumber}")

    descriptorBaseNote = baseNoteChar.getDescriptors()
    descriptorActualNote = actualNoteChar.getDescriptors()
    
    #set notify status to true
    device.writeCharacteristic(descriptorActualNote[0].handle, b"\x01\x00")
else:
    print("No compatible theremin found in proximity. Check device and restart application")
    exit(-3)


#create thread to wait for notifications. Set deamon to true to allow interruption of the task. Else, there is a fault if you spam a button
def waitForNotifications():
    while True:
        try:
            device.waitForNotifications(1.0)
            time.sleep(1/1000)
        except Exception:
            print("Unknown failure in Task waitForNotifications")
            exit(-5)
threadWaitForNotifications = threading.Thread(target=waitForNotifications, name="waitForNotifications", daemon=True)
threadWaitForNotifications.start()

#sends value to device. can only take values between 0 - 255. raises exception if val is out of bounds
def sendToDevice(value):
    print(f"attempting to send: {value}")
    if(value < 255 and value >= 0):
        bytes_to_send = value.to_bytes(1, byteorder='big')
    else:
        raise Exception(f"Value too high or too low. Cannot send to Device. Value was {value}")

    try:
        device.writeCharacteristic(baseNoteChar.valHandle, bytes_to_send)
        print("sending successful")
    except Exception:
        print("charactersitic not written")
        return False

    return True


# To create custom window we subclass QMainWindow
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()                                                          # initializes the super class

        self.setWindowTitle("Theremin Anzeige")                                     # set a title for the window

        self.baseNoteNumber = int.from_bytes(device.readCharacteristic(baseNoteChar.valHandle), byteorder='little')   # store the state of the current base note
        increaseButton = QPushButton("Stimmung +")
        increaseButton.clicked.connect(self.increasedClicked)                           # register the subscriber/slot for the button signal
        decreaseButton = QPushButton("Stimmung -")
        decreaseButton.clicked.connect(self.decreasedClicked) 
        
        self.playedNoteLabel = QLabel("Noch keine Daten verfügbar")                      # create the count label
        self.playedNoteLabel.setAlignment(QtCore.Qt.AlignCenter)                         # center the label
        self.tuningLabel = QLabel(f"Grundton {noteMapping[self.baseNoteNumber]}")                         # create the count label
        self.tuningLabel.setAlignment(QtCore.Qt.AlignCenter) 
        
        layout = QVBoxLayout()                                                      # create a layout
        layout.addWidget(self.playedNoteLabel)                                          # add the label to the layout
        layout.addWidget(self.tuningLabel)
        layout.addWidget(increaseButton)                                         # add the buttons to the layout
        layout.addWidget(decreaseButton)
        widget = QWidget()                                                       # create a widget
        widget.setLayout(layout)                                                 # set the layout for the widget
        self.setCentralWidget(widget)                                               # set the central widget (will take all available space)


    def increasedClicked(self):                                                           # the method registered as subscriber for the increase button
        try: 
            sendToDevice(self.baseNoteNumber + 1)
            self.baseNoteNumber += 1
            self.tuningLabel.setText(f"Grundton {noteMapping[self.baseNoteNumber]}")
        except Exception:
            #TODO add exception handling
            print(f"Exception in {__qualname__}")
            pass

    def decreasedClicked(self):                                   # the method registered as subscriber for the reset button
        try: 
            sendToDevice(self.baseNoteNumber - 1)
            self.baseNoteNumber -= 1
            self.tuningLabel.setText(f"Grundton {noteMapping[self.baseNoteNumber]}")
        except Exception:
            #TODO add exception handling
            print(f"Exception in {__qualname__}")
            pass
    
app = QApplication(sys.argv)
window = MainWindow()

window.show()
app.exec()
