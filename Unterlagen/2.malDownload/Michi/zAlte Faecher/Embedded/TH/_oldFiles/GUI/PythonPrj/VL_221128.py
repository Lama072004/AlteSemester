class Address:
    def __init__(self, place, street):
        self._place = place
        self._street = street

    def setAdress(self, place, street):
        self._place = place
        self._street = street
    
        #decorator in python??
    @property
    def getAdress(self):
        return self._place, self._street
        

class Customer:
    def __init__(self, name, place, street):
        self._custName = name
        self._address = Address(place, street)

    def __init__(self, name):
        self._custName = name
        self._address = Address(None, None)
        
    def setNewAdress(self, address):
        self._address = address

    def setNewAdress(self, a):
        self._address = a

    def describeYourself(self):
        print(f"My name is {self._custName}")
        place, street = self._address.getAdress()
        print(f"I live in {place} in {street}")

    def expectsDeliveryAt(self):
        return self._address.getAdress()


    

def main():
    a1 = Address("Sandstarte", "Lustnau")
    a2 = Address("Hochquellenstraße", "Hohenems")
    c1 = Customer("Michael", a1)
    c2 = Customer("Stefan", a2)

    customerList = [c1, c2]
    for c in customerList:
        c.describeYourself()

    


if __name__ == '__main__':
    main()

