from bluepy.btle import DefaultDelegate, Scanner, Peripheral, ADDR_TYPE_PUBLIC, AssignedNumbers, UUID
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QTableWidget, QTableWidgetItem, QVBoxLayout, QWidget


import pyqtgraph as pg

# to view GUI type "sudo python3 /home/emanuel/Python_Files/Projekt_3_Semester.py" into comand line on Raspberry

GATT_SERVICE_UUID = 0x345f
GATT_CHARACTERISTIC_UUID = 0x744b


class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)
        self.device = None

    def handleDiscovery(self, scanEntry, isNewDev, isNewData):
        print("Discovered device", scanEntry.addr)



xAccel = []
yAccel = []
counter = 0
positionFirst20 = []
positionSecond20 = []
wholePosition = []

class PeripheralDelegate(DefaultDelegate):
    
    
    def __init__(self):
        DefaultDelegate.__init__(self)
    
    def handleNotification(self, cHandle, data):
        global counter
        global positionFirst20
        global positionSecond20 
        global wholePosition
        global xAccel
        global yAccel
        parsed = list(data)
        if len(parsed) > 1:
  
            if counter == 0:
                xAccel.append(float(data[0:8]))
                yAccel.append(float(data[10:18]))

    
            if (counter == 1):                                                  #First 20 characters of the position
                positionFirst20 = data[0:19]

            if(counter == 2):                                                   #Second 20 characters of the position
                positionSecond20 = data[0:19]


            if counter == 3:                                                    #Whole position
                wholePosition.append(positionFirst20 + positionSecond20 + data[0:11])
     
            counter = counter + 1

            if(counter == 4):
                counter = 0
               
                positionFirst20 = {0}
                positionSecond20 = {0}



            

scanner = Scanner().withDelegate(ScanDelegate())
scanEntries = scanner.scan(10)

device = None


for entry in scanEntries:
    name = entry.getValueText(9) 
    if name == "AccelGPS":
        print(f"Found proxy - address={entry.addr}")
        device = Peripheral(entry.addr, ADDR_TYPE_PUBLIC)


if device:
    device.setDelegate(PeripheralDelegate())
    hrService = device.getServiceByUUID(GATT_SERVICE_UUID)
    hrChar = hrService.getCharacteristics(GATT_CHARACTERISTIC_UUID)[0]
    desc = hrChar.getDescriptors(AssignedNumbers.client_characteristic_configuration)
    device.writeCharacteristic(desc[0].handle, b"\x01\x00")

    while True:
        if device.waitForNotifications(1.0) == True:
       
            continue
        if(device.waitForNotifications(1.0) == False):                          #Exit while loop if device is disconnected
            device.disconnect
            print("Device disconnected")
            
            break
            
    

#----------------Acceleration plot-------------------------------------------------------------
class MainWindow(QMainWindow):

    def __init__(self):
        super(MainWindow, self).__init__()
        plot = pg.PlotWidget()                                                  # create a plot widget
        plot.setBackground('w')                                                 # set the background color to white
   


        
        numberOfEntries = []

        for count in range(len(wholePosition)):
            numberOfEntries.append(count + 1)                                   #start plot at 1 and not 0


        xAccelPen = pg.mkPen(color=(255, 0, 0), width=5)                        # create a pen to 'draw' the plot
        yAccelPen = pg.mkPen(color=(0, 255, 0), width=5)                        
        plot.setTitle("Position and Acceleration")                              # set the title of the plot
        styles = {'font-size':'20px'}                                           # prepare the style for the plot
        plot.setLabel('left', 'Acceleration (X = Red Y = Green)', **styles)     # label the y axis
        plot.setLabel('bottom', 'Position Number', **styles)                    # label the x axis
        plot.showGrid(x=True, y=True)                                           # display the grid of the plot
        plot.plot(numberOfEntries, xAccel, pen=xAccelPen)                       # plot the provided data written xAccel
        plot.plot(numberOfEntries, yAccel, pen=yAccelPen) 
        self.setCentralWidget(plot)

app = QApplication(sys.argv)
window = MainWindow()
window.show()


#-------------position table---------------------------------------------------------

qwidget = QWidget()
qwidget.setWindowTitle("Position")
qwidget.resize(300,400)
ayout = QVBoxLayout()


layout = QVBoxLayout()
tableWidget = QTableWidget()
tableWidget.setHorizontalHeaderItem(1,QTableWidgetItem("Position"))
tableWidget.setColumnCount(1)
tableWidget.setRowCount(len(wholePosition))


for count in range(len(wholePosition)): 
    tableWidget.setItem(count,0,QTableWidgetItem(f"{wholePosition[count]}"))    #set all positions in the table


layout.addWidget(tableWidget)
qwidget.setLayout(layout)
qwidget.show()

app.exec()                                                                      #execute app


