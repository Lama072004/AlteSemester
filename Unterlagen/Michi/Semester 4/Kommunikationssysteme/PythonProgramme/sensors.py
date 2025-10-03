import abc
import random

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