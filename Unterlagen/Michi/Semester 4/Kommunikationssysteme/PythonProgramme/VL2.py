import  random
import abc

class Sensor(abc.ABC):

    def __init__(self, id: str, panic_value: float, panic_function: callable):
        self.__id = id
        self.__panic_value  = panic_value
        self._panic_function_ = panic_function

        self.__value = None


    def id(self, id = None):
        if id is None:
            return self.__id
        
        self.__id = id
        return self
    
    def value(self, value = None):
        if value is None:
            return self.__value
        
        self.__value = value
        return value
    
    @abc.abstractmethod
    def write(self):
        pass 

    @abc.abstractmethod
    def read(self):
        #an dieser Stelle ist read der Subclass ausgeführt worden und ein neuer Value liegt vor
        if None not in (self.__panic_value, self._panic_function_):
            #Panic handling possible
            if self.value() > self.__panic_value:
                self._panic_function_()

class SensorIr(Sensor):

    def __init__(self, id: str, panic_value: float = None, panic_function: callable = None):
        super().__init__(id, panic_value, panic_function)

    def write(self):
        print("Do nothing, is IR sensor.")

    def read(self):
        value = random.randint(5, 300)
        self.value(value)
        print(f"The acutal value is: {value}")
        super().read() #for panic handling if active

        return value


class SensorUs(Sensor):

    def __init__(self, id: str, panic_value: float = None, panic_function: callable = None):
        super().__init__(id, panic_value, panic_function)

    def write(self):
        print(f"USS {self.id()}: sending ping.")

    def read(self):
        value = random.randint(5, 300)
        self.value(value)
        print(f"The acutal value is: {value}")
        super().read() #for panic handling if active
        return value

def turn_right():
    print("##### mache kurve nach rechts")

if __name__ == '__main__':
    def turn_right():
        print("##### mache kurve nach rechts")
    def turn_left():
        print("##### mache kurve nach links")
    def turn_around():
        print("##### drehe um")

    #Sensor Base class
    #sensor = Sensor("10:00")
    #print(sensor.id())
    #sensor.id('Hollodrio')
    #print(sensor.id())

    #sensor.read()
    #sensor.write()}

    #Subclass: US Sensor
    Sensors = [
        SensorUs("06:00", panic_value = None, panic_function = None),
        SensorUs("10:00", panic_value = 100,  panic_function = turn_right),
        SensorUs("14:00", panic_value = 100,  panic_function = turn_left),
        SensorIr("12:00", panic_value = 80,   panic_function = turn_around)
    ]

    for _ in range(5):
        for sensor in Sensors:
            sensor.write()
            value_cm = sensor.read()





            # if value_cm < 50:
            #     if sensor.id() == "10:00":
            #         print("##### mache kurve nach rechts")
            #     elif sensor.id() == "12:00":
            #         print("##### Panic, wir drehen um ")
            #     elif sensor.id() == "14:00":
            #         print("##### mache kurve nach links")
            #     else:
                    
            #         print("##### Stopp!")
                    
                    
                    



        



