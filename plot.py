#%%
import time
import serial
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from IPython import display

import sys
import os

import pygame
from pygame.locals import *
 
pygame.init()
 
fps = 60
fpsClock = pygame.time.Clock()

image = pygame.image.load(r'img.png')

width, height = 1000, 600
screen = pygame.display.set_mode((width, height))
brown = [255, 255, 150]
white = [255,255,255]
arduino = serial.Serial('COM8',9600) # set your COM port here
time.sleep(1)

while True:
   
    sys.stdout.write('\r')
    text = str(arduino.readline())

    X =float(text.split(",")[0][2:])
    Y =float(text.split(",")[1])
    old_theta = theta
    theta = float(text.split(",")[2].split('\\')[0])
    
    sys.stdout.write(str(X) + " ")
    sys.stdout.write(str(Y) + " ")
    sys.stdout.write(str(theta))
    sys.stdout.flush()

    screen.fill((0, 0, 0))
    image_rotated = pygame.transform.rotate(image, 90-theta*360/(2*3.1415))
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
    
    # Update.
    
    # Draw.
    screen.fill(brown)
   
    screen.blit(image_rotated, (X, Y))
    pygame.display.flip()
    fpsClock.tick(fps)

    
   #sys.stdout.write(str(float(text.split(",")[0][2:]))+" "+str(float(text.split(",")[1])) + " " + str(float(text.split(",")[2][:-6]))+"\n")

   

# %%
