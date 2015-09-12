# Thermistor_B57861S.py
#
# Description: Python 3 module for use with B57861S thermistor
#
# Revision History
# 12 Sep 2015 - Created and debugged
#
# Author: Lars Soltmann
#

import numpy as np

global THERM_CAL_MAT


## Calibration matrix for B57861S thermistor with R/T characteristic 8016
#              TempF  TempC  RT/R25
THERM_CAL_MAT=np.array([[-67, -55, 96.3],
                [-58, -50, 67.01],
                [-49, -45, 47.17],
                [-40, -40, 33.65],
                [-31, -35, 24.26],
                [-22, -30, 17.7],
                [-13, -25, 13.04],
                [-4, -20, 9.707],
                [5, -15, 7.293],
                [14, -10, 5.533],
                [23, -5, 4.232],
                [32, 0, 3.265],
                [41, 5, 2.539],
                [50, 10, 1.99],
                [59, 15, 1.571],
                [68, 20, 1.249],
                [77, 25, 1],
                [86, 30, 0.8057],
                [95, 35, 0.6531],
                [104, 40, 0.5327],
                [113, 45, 0.4369],
                [122, 50, 0.3603],
                [131, 55, 0.2986],
                [140, 60, 0.2488],
                [149, 65, 0.2083],
                [158, 70, 0.1752],
                [167, 75, 0.1481],
                [176, 80, 0.1258],
                [185, 85, 0.1072],
                [194, 90, 0.09177],
                [203, 95, 0.07885],
                [212, 100, 0.068],
                [221, 105, 0.05886],
                [230, 110, 0.05112],
                [239, 115, 0.04454],
                [248, 120, 0.03893],
                [257, 125, 0.03417],
                [266, 130, 0.03009],
                [275, 135, 0.02654],
                [284, 140, 0.02348],
                [293, 145, 0.02083],
                [302, 150, 0.01853],
                [311, 155, 0.01653]])

def getTempF(R25,RDIV,VREF,VMEAS):
    if VMEAS==VREF:
        RTR25=100
    else:
        RTR25=VMEAS*RDIV/(R25*(VREF-VMEAS))
    if RTR25>=THERM_CAL_MAT[0,2]:
        tempF=THERM_CAL_MAT[0,0]
    elif RTR25<=THERM_CAL_MAT[len(THERM_CAL_MAT[:,2])-1,2]:
        tempF=THERM_CAL_MAT[len(THERM_CAL_MAT[:,2])-1,0]
    else:
        UB=(THERM_CAL_MAT[:,2]<=RTR25).argmax()
        LB=UB-1
        tempF=THERM_CAL_MAT[LB,0]+(THERM_CAL_MAT[UB,0]-THERM_CAL_MAT[LB,0])*(RTR25-THERM_CAL_MAT[LB,2])/(THERM_CAL_MAT[UB,2]-THERM_CAL_MAT[LB,2])
    return tempF

def getTempC(R25,RDIV,VREF,VMEAS):
    if VMEAS==VREF:
        RTR25=100
    else:
        RTR25=VMEAS*RDIV/(R25*(VREF-VMEAS))
    if RTR25>=THERM_CAL_MAT[0,2]:
        tempC=THERM_CAL_MAT[0,1]
    elif RTR25<=THERM_CAL_MAT[len(THERM_CAL_MAT[:,2])-1,2]:
        tempC=THERM_CAL_MAT[len(THERM_CAL_MAT[:,2])-1,1]
    else:
        UB=(THERM_CAL_MAT[:,2]<=RTR25).argmax()
        LB=UB-1
        tempC=THERM_CAL_MAT[LB,1]+(THERM_CAL_MAT[UB,1]-THERM_CAL_MAT[LB,1])*(RTR25-THERM_CAL_MAT[LB,2])/(THERM_CAL_MAT[UB,2]-THERM_CAL_MAT[LB,2])
    return tempC
