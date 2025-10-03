from math import *

def alpha(T, b=3760):
    T += 273.15 
    return  -b/(T**2)

def r( T, r0 = 50e3, b=3760, T0=25):
    T += 273.15
    T0 += 273.15
    return r0 * exp(b*(1/T - 1/T0) )

def deltaR(T, T0 = 25, R=50e3, deltaR0=0.02, deltaB= 3760):
    T0 += 273.15
    T += 273.15
    return R*(deltaR + (1/T - 1/T0))

for T in (-20, 0, 20, 25, 50, 100):
    print (f'T = {T}: R = {round(r(T))} alpha = {round(alpha(T), 3)} ')

