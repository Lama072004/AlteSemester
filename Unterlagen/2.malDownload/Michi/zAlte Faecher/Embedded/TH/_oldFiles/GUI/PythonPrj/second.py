import sys
import location 


def kwArgs(**kwargs):
    for m in kwargs:
        print(m)
        print(kwargs[m])


def spam(*args):
    print(type(args))
    for arg in args:
        print(type(arg))
        #arg += 1




if __name__ == '__main__':

    a = location.getLocation("Lustenau")
    print(a)

