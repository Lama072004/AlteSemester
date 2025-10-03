from sensors import SensorIr, SensorUs

def turn_right():
    print("##### mache kurve nach rechts")
def turn_left():
    print("##### mache kurve nach links")
def turn_around():
    print("##### drehe um")

Sensors = [
    SensorUs("06:00", panic_value = None, panic_function = None),
    SensorUs("10:00", panic_value = 100,  panic_function = turn_right),
    SensorUs("14:00", panic_value = 100,  panic_function = turn_left),
    SensorIr("12:00", panic_value = 80,   panic_function = turn_around)
]