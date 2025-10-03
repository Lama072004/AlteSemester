def startup():
    """This function prints hello world\nReturns nothing"""
    print("Hello World")
    
    temperature = "23.5" + "C"
    print(temperature)

def func2():
    a = 10
    #if statements are NOT scoped!
    if a == 5:
        b = 1
    elif a == 10:
        b = 2
    print(b)
    lang = "pyth"
    match lang:
        case "pyth":
            print(1)
        case "js" | "php":
            print(2)
        case _:
            print(3)
    i = 0
    while i < 5:
        print (i)
        i += 1




if __name__ == '__main__':
    startup()
    myList = [1, "test", True, 23.5]
    print(type(myList))
    print(id(myList))
    a = 32.0 + 4j
    b = 13.2 - 5j
    print(a+b)
    print(a**2)
    if "test" in myList:
        print("yes")
    else:
        print("no")

    func2()

    i = 0
    
    for entry in myList:
        print(i)
        print(entry)
        i += 1


    for count in range(10, 20 , 2):
        print(count)
    

    
