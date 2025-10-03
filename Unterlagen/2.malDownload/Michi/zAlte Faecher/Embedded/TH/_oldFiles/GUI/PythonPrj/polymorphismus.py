class Animal:
    def __eq__(self, __o: object) -> bool:
        pass

    def __init__(self, name=None) -> None:
        self._name = name

    def makeNoise(self):
        pass

class Cow(Animal):
    def __init__(self, name=None) -> None:
        super().__init__(name)

    def makeNoise(self):
        print(f"{self._name} makes Moooh")

class Dog(Animal):
    def __init__(self, name=None) -> None:
        super().__init__(name)

    def makeNoise(self):
        print(f"{self._name} makes Woof")


class Person:
    def __init__(self, name) -> None:
        self._name = name

    def __repr__(self) -> str:
        return self._name
    
animals = [Cow(), Dog("Hans"), Animal()]

p1 = Person("Hanns")

print(p1)

for animal in animals:
    animal.makeNoise()