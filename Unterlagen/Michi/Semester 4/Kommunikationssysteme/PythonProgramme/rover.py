from sensordb import Sensors

if __name__ == '__main__':
    for sensor in Sensors:
        sensor.write()
        value_cm = sensor.read()
    
