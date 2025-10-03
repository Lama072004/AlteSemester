def rTheta(thetaM, r0 = 100,alpha = 3.85e-3, theta0=0):
    return r0 * (1+alpha*(thetaM-theta0))

def iM (rTheta, rV=20050, rM=1000, uB=10):
    return uB * rTheta / (rV *(rTheta  + rM) + rTheta *rM)

def n(iM, n0= 400, i0=  100e-6):
    return round (n0 * iM / i0)

for thetaM in (0, 100, 200, 300, 400):
    print( "thetaM = %d: n = %d" % (thetaM , n( iM (rTheta(thetaM) ) ) ) )

