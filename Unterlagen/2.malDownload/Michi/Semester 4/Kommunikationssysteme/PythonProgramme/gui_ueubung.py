import sys, random, time
import typing
from PyQt6 import QtWidgets as qtw
from PyQt6 import QtCore as qtc
#from PyQt6.QtWidgets import QWidget

from pieDataManagement import PieBox

class MainWindow(qtw.QWidget):
    def __init__(self) -> None:
        super().__init__()
        
        self._build_gui_()
        self.show()

    def _build_gui_(self):
        cb = qtw.QCheckBox("Show text", self)
        cb.move(20, 20)
        cb.toggle()
        cb.stateChanged.connect(self._change_title_)
        self.setGeometry(300, 300, 350, 250)
        self.setWindowTitle("Testprogramm")

    def _change_title_(self, state):
        if state == qtc.Qt.CheckState.Checked.value:
            self.setWindowTitle(str(time.time()))
        else:
            self.setWindowTitle("")
        

if __name__=='__main__':
    app = qtw.QApplication(sys.argv)
    win = MainWindow()
    app.exec()



