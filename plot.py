#%%
import time
import serial
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from IPython import display



x = y = []
counter = 1
cycle = 20
step = 0.1 # seconds


%matplotlib inline
arduino = serial.Serial('COM9',9600) # set your COM port here
time.sleep(1)
pprintpri
while counter <= cycle:
   time.sleep(step)
   
   #arduino.write('X'.encode())


   #espeed = float(arduino.readline())
   #x = np.append(x, espeed)
   #arduino.write('Y'.encode())
   #power = float(arduino.readline())
   #y = np.append(y, poer)
   text = str(arduino.readline())
   x.append((float(text.split(",")[0][2:])))
   y.append((float(text.split(",")[1][:-6])))
   

   
   counter += 1
arduino.close()
print(x)
print(y)
plt.figure(figsize=(20, 10), dpi= 200, facecolor='w', edgecolor='k')
plt.xlabel('X', fontsize = 13)
plt.ylabel('Y', fontsize = 13)
plt.grid(True)
plt.scatter(x, y)

plt.show()
# %%
