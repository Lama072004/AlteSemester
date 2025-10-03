import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QLabel
from PySide6 import QtCore

# To create custom window we subclass QMainWindow
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()                                      # initializes the super class



        self.setWindowTitle("Click Counter")                    # set a title for the window
        self.countLabel = QLabel("0")                           # create the count label
        self.countLabel.setAlignment(QtCore.Qt.AlignCenter)     # center the label

        self.currentCount = 0                                 # store the state of the current count
        increaseButton = QPushButton("Increase")
        increaseButton.clicked.connect(self.increasedClicked) # register the subscriber/slot for the button signal
        resetButton = QPushButton("Reset")
        resetButton.clicked.connect(self.resetClicked) 
        

        layout = QVBoxLayout()                                  # create a layout
        layout.addWidget(self.countLabel)                       # add the label to the layout
        layout.addWidget(increaseButton)                        # add the buttons to the layout
        layout.addWidget(resetButton)
        widget = QWidget()                                      # create a widget
        widget.setLayout(layout)                                # set the layout for the widget
        self.setCentralWidget(widget)                           # set the central widget (will take all available space)

    def increasedClicked(self):                               # the method registered as subscriber for the increase button
        self.currentCount += 1
        self.countLabel.setText(str(self.currentCount))

    def resetClicked(self):                                   # the method registered as subscriber for the reset button
        self.currentCount = 0
        self.countLabel.setText(str(self.currentCount))
        

app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec()














