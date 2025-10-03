from math import *

D =  {'eins': 1, 'zwei': 2, "monty":"Python"}

for k in D:
    print( "%s: %s" % (k, D[k]))
    print( f'{k}: {D[k]}')

for k, v in D.items():
    print( "%s: %s" % (k, v))

    try:
        print( v**2)

    except TypeError as err:
        print( f"sorry, das geht nicht weil: {err}. \nKey = {k}, Val = {v}")

for t in D.items():
    print( "%s: %s" % t)

print("Wir sind fertig")




