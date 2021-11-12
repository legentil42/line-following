
#%%
import time
import serial
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from IPython import display
import random
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
arduino = serial.Serial('COM9',9600) # set your COM port here
time.sleep(1)



class block:
    instances = []
    def __init__(self):
        self.x = random.randint(500,1000)
        self.y = random.randint(0,600)
        self.__class__.instances.append(self)

    def update(self):
        self.x += -20
        if self.x < 0:
            self.x = 1000
            self.y = random.randint(0,600)

    def draw(self):
        pygame.draw.rect(screen, [0,180,0], pygame.Rect(self.x, self.y, 30, 200))



def generate_x_blocks(nb):
    for x in range(nb):
        block()
    Les_X = np.linspace(100,1000,nb)

    for i  in range(nb):
        block.instances[i].x = Les_X[i]
        
generate_x_blocks(4)
while True:
   
    sys.stdout.write('\r')
    text = str(arduino.readline())

    Y = float(text.split('\\')[0][2:])
    sys.stdout.write(text)
    sys.stdout.flush()
    y_game = 550 + ((50 - 550) / (3000 - 800)) * (Y - 800)
    screen.fill((0, 0, 0))


    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
    
    # Update.
    

    # Draw.
    screen.fill(brown)
    screen.blit(image, (50, y_game))

    for block in block.instances:
        block.update()
        block.draw()

    pygame.display.flip()


   #sys.stdout.write(str(float(text.split(",")[0][2:]))+" "+str(float(text.split(",")[1])) + " " + str(float(text.split(",")[2][:-6]))+"\n")

   

# %%

# %%
