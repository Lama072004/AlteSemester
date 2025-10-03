from PySide6.QtWidgets import QApplication, QMainWindow
from PySide6 import QtCore
import pyqtgraph as pg
import sys, random

class MainWindow(QMainWindow):

    def __init__(self):
        super(MainWindow, self).__init__()
        self.plot = pg.PlotWidget()
        self.plot.setBackground('w')

        self.xValues = list(range(50))                            # initialize the x values with 0-49 
        self.yValues = [random.randint(0,50) for _ in range(50)]  # initialize 50 random y values

        pen = pg.mkPen(color=(255, 0, 0), width=3)
        self.currentPlot =  self.plot.plot(self.xValues, self.yValues, pen=pen)
        self.setCentralWidget(self.plot)

    def updatePlot(self):
        self.xValues = self.xValues[1:]                             # slice the xValues (remove the first value)
        xMax = self.xValues[-1]                                     # get max xValue
        self.xValues.append(xMax + 1)                               # add a new, higher xValue
        self.yValues = self.yValues[1:]                             # slice the yValues (remove the first value)
        self.yValues.append( random.randint(0,50))                  # Add a new random yValue
        self.currentPlot.setData(self.xValues, self.yValues)        # update the plot

app = QApplication(sys.argv)
window = MainWindow()
timer = QtCore.QTimer()                                             # create a timer
timer.setInterval(100)                                              # set the timer to timeout every 100ms
timer.timeout.connect(window.updatePlot)                            # set the timeout method to call    
timer.start()                                                       # start the timer
window.show()
app.exec()