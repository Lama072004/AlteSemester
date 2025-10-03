import math

def solve_quadratic_equations(a, b, c):
    try: 
        a = float(a)
        b = float(b)
        c = float(c)
    except:
        print("Only numbers allowed. Check input")
        return

    if a == 0.0 and b != 0.0:
        return (-c/b, "linear")
    else:
        raise Exception

    if 1.0 != a:
        b = b/a
        c = c/a
        a = a/a

    D = ((b/2)**2 - c) 
    if D >= 0:
        solutions = (
            (-b/2 + math.sqrt(D)),
            (-b/2 - math.sqrt(D)),
            "real" 
        )

    else:
        D *= -1
        solutions = (
            (-b/2, math.sqrt(D)),
            (-b/2, -math.sqrt(D)),
            "complex"
        )
    return solutions
        

if __name__ == '__main__':
    while True:
        try:
            vals = input("Enter the coeffiecents for the equation ax^2+bx+c, spaced. X to close program:")
            if vals.lower() == "x":
                exit()

            valList = vals.split()
            print(valList)
            print(solve_quadratic_equations(valList[0], valList[1], valList[2]))
        except KeyboardInterrupt as k:
            exit()





