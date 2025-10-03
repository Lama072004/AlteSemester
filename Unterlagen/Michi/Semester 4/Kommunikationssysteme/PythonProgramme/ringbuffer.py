from __future__ import annotations

from collections import deque

class PieRingbuffer:
    def __init__(self, num_elems):
        self.__elems = deque( maxlen = num_elems)

    def clear(self):
        """
        Clears whole buffer.
        """
        self.__elems.clear()

    def elem_add(self, elem):
        """
        Adds element to the buffer
        """
        self.__elems.append(elem)

    def elems(self, index=None):
        """
        Returns all elements if no parameter is given. 
        Returns parameter with given index if paramter is given.
        """
        if index:
            return self.__elems[index]
        else:
            return self.__elems
    
    def num_elems(self):
        return len(self.__elems)


if __name__ == "__main__":
    buffer =  PieRingbuffer(5)
    print(buffer.elems())

    # plus is equal to extend list, not append!!
    for something in [i for i in range(10)] + ["hallo", "dies ist", "test"]: 
        buffer.elem_add(something)
        print(buffer.elems())


    for i in range(10):
        buffer.elem_add(i)
        print(buffer.elems())



