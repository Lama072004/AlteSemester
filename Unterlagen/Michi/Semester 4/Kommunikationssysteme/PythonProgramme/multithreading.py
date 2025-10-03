"""
Schreiben Sie ein Programm, das aus m Producer-Threads und n Consumer-Threads besteht:

Die Producer erzeugen normalverteilte Zufallszahlen, die Consumer geben Sie auf den Bildschirm aus.

Jedem Thread kann die Frequenz mitgegeben werden, mit der er seine Aufgabe erfüllt.

Realisieren Sie die Kommunikation der beiden Threads über eine Queue.

Wie würden Sie sie in der Größe dimensionieren?
Was tun Sie gegen Underflow (Angebotsverknappung, Queue leer) u/o Overflow (Überangebot, Queue ist voll)?
"""

import queue
import threading
import random
import time


class Consumer:
    def __init__(self, cycle_time, q: queue, start_immediately: bool = False) -> None:
        self.__cycle_time = cycle_time
        self.__q = q
        self.__start_immediately = start_immediately
        self.__thread = threading.Thread(target=self.consume, daemon=True)
        self.__request_stop = False
        if start_immediately:
            self.__thread.start()
        pass

    def consume(self):
        while True:
            if self.__request_stop:
                break                
            try:
                number = self.__q.get()
            except Exception:
                print(Exception)
            print("Number %s was conusmed" % number)
            time.sleep(self.__cycle_time)
            #self.__thread.wait(self.__cycle_time)
            pass

    def start(self):
        self.__thread.start()

    def stop(self):
        self.__request_stop = True
    def join(self):
        self.__thread.join()


class Producer:
    def __init__(self, cycle_time, q: queue, start_immediately: bool = False) -> None:
        self.__cycle_time = cycle_time
        self.__q = q
        self.__start_immediately = start_immediately
        self.__thread = threading.Thread(target=self.produce, daemon=True)
        self.__request_stop = False
        if start_immediately:
            self.__thread.start()
        pass

    def produce(self):
        while True:
            if self.__request_stop:
                break
            number = random.gauss(1, 4)
            try:
                self.__q.put(number)
            except Exception:
                print(Exception)
            print("Number %s was produced" % number)
            time.sleep(self.__cycle_time)
            

    def start(self):
        self.__thread.start()

    def stop(self):
        self.__request_stop = True

    def join(self):
        self.__thread.join()




if __name__ == "__main__":
    def _Lab_():
        q = queue.Queue( 8)
        c = Consumer( 0.01, q, False)
        p = Producer( 0.1, q, False)
        p.start()
        c.start()

        time.sleep( 5.0)
        print( "T h a t ' s   i t   f o r   n o w   - we stop everything.")
        p.stop()
        p.join()

        c.stop()
        c.join()

        return

    _Lab_()