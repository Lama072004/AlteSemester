import sys
import numpy as np
from PyQt6.QtWidgets import QApplication, QMainWindow, QTabWidget, QWidget, QVBoxLayout, QLabel, QPushButton, QLineEdit, QCheckBox, QRadioButton, QGroupBox, QHBoxLayout, QScrollArea
from PyQt6.QtCore import Qt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Tabbed GUI")
        self.resize(800, 600)

        self.scroll_area = QScrollArea()
        self.scroll_area.setWidgetResizable(True)

        self.tab_widget = QTabWidget()
        self.scroll_area.setWidget(self.tab_widget)

        self.setCentralWidget(self.scroll_area)

        self.create_tabs()

    def create_tabs(self):
        for i in range(5):
            tab = QWidget()
            layout = QVBoxLayout(tab)

            for j in range(3):
                label = QLabel(f"Label {j+1}")
                layout.addWidget(label)

                button = QPushButton(f"Button {j+1}")
                layout.addWidget(button)

                text_field = QLineEdit()
                layout.addWidget(text_field)

                checkbox_group = QGroupBox("Checkboxes")
                checkbox_layout = QVBoxLayout(checkbox_group)
                for k in range(3):
                    checkbox = QCheckBox(f"Checkbox {k+1}")
                    checkbox_layout.addWidget(checkbox)
                layout.addWidget(checkbox_group)

                radio_group = QGroupBox("Radio Buttons")
                radio_layout = QVBoxLayout(radio_group)
                for k in range(3):
                    radio = QRadioButton(f"Radio {k+1}")
                    radio_layout.addWidget(radio)
                layout.addWidget(radio_group)

                plot_canvas = PlotCanvas(tab)
                layout.addWidget(plot_canvas)

            tab.setLayout(layout)
            self.tab_widget.addTab(tab, f"Tab {i+1}")

        # Add the sixth tab with only a numpy plot
        sixth_tab = QWidget()
        sixth_layout = QVBoxLayout(sixth_tab)
        plot_canvas = PlotCanvas(sixth_tab)
        sixth_layout.addWidget(plot_canvas)
        sixth_tab.setLayout(sixth_layout)
        self.tab_widget.addTab(sixth_tab, "Tab 6")


class PlotCanvas(FigureCanvas):
    def __init__(self, parent=None, width=2, height=2, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(131)
        super().__init__(fig)
        self.setParent(parent)

        self.plot_random_data()

    def plot_random_data(self):
        x = np.linspace(0, 10, 100)
        y = np.random.rand(100)
        self.axes.plot(x, y)
        self.axes.set_xlabel('X')
        self.axes.set_ylabel('Y')
        self.axes.set_title('Random Plot')
        self.draw()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec())
