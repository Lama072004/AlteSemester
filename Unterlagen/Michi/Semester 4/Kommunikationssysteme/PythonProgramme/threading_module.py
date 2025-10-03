from __future__ import annotations

import threading
import time
from typing import Any


GlobalValue = 0

class Counter(threading.Thread):

    _Lock = threading.Lock()

    def __init__(self, id:str):
        super().__init__(daemon=True)
        self.__value = 0
        self.__id = id
        self.__is_stop_requested = False

    def run(self):
        global GlobalValue
        while True:
            if self.__is_stop_requested:
                break

            self.__value += 1
            print(f"Thread {self.__id}: value = {self.__value}.")
            with Counter._Lock:
                GlobalValue += 1

            time.sleep(0.01)

    def request_stop(self):
        self.__is_stop_requested = True


class Zaehler(threading.Thread):
    def run(self):
        global GlobalValue
        while True:
            GlobalValue += 1

if __name__ == '__main__':
    counters = []
    for i in range(2): #create threadlist
        counters.append(Counter(i))

    for counter in counters:
        counter.start() #start threads

    # let the threads be
    time.sleep(1.0)

    #stop threads
    for counter in counters:
        counter.request_stop()

    for counter in counters:
        counter.join()#waits for run method to end.

    print("Done.")