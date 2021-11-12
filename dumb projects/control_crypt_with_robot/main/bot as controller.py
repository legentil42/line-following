#%%#
import time
import serial
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from IPython import display

from pynput.keyboard import Key, Controller


import sys
import os

import pygame
from pygame.locals import *
 
arduino = serial.Serial('COM7',9600) # set your COM port here
time.sleep(1)
keyboard = Controller()

old_X = 0
old_Y = 0
G_flag = False
D_flag = False

while True:
   
    sys.stdout.write('\r')
    text = str(arduino.readline())
    try:
        L_text = text.split(",")
        X = float(L_text[0].split("'")[1])
        Y = float(L_text[1])
        bump_G = float(L_text[2])
        bump_D = float(L_text[3].split("\\")[0])
        print(X,Y,bump_G,bump_D)
    except:
        print("error : ",text)
    
    if X-old_X > 5:
        old_X = X
        keyboard.press(Key.up)
        keyboard.release(Key.up)
        print("up")

    elif X-old_X < -5:
        old_X = X
        keyboard.press(Key.down)
        keyboard.release(Key.down)
        print("down")

    elif bump_G > 1200 and G_flag == False:
        keyboard.press(Key.left)
        keyboard.release(Key.left)
        print("left")
        G_flag = True

    elif bump_D > 1500 and D_flag == False:
        keyboard.press(Key.right)
        keyboard.release(Key.right)
        print("right")
        D_flag = True
    
    if  bump_G < 1200 and G_flag == True:
        G_flag = False
    
    if  bump_D < 1200 and D_flag == True:
        D_flag = False

    # theta = float(text.split(",")[2].split('\\')[0])
    # X =float(text.split(",")[0][2:])
    # Y =float(text.split(",")[1])
    # sys.stdout.write(str(X) + " ")
    # sys.stdout.write(str(Y) + " ")
    # sys.stdout.write(str(theta))
    # sys.stdout.flush()
    
   #sys.stdout.write(str(float(text.split(",")[0][2:]))+" "+str(float(text.split(",")[1])) + " " + str(float(text.split(",")[2][:-6]))+"\n")

keyboard.press(Key.up)
keyboard.release(Key.up)



# %%
