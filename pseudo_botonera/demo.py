#!/usr/bin/arch -i386 /usr/bin/python

import os
import pygame
import serial
import sys

from serial.tools import list_ports

size = width, height = 640, 480
white = (255, 255, 255)

# ------
# serial

ports = list_ports.comports()
for name, desc, hwid in ports:
    print name

#wixel = serial.Serial(port=ports[0][0], baudrate=57600, timeout=0)
#wixel.open()

wixel = sys.stdout

# ------
# pygame

pygame.mixer.pre_init(44100)
pygame.init()
screen = pygame.display.set_mode(size)
screen.fill(white)

sounds = {}
for n, filename in enumerate(os.listdir("audio")):
    char = chr(ord("a") + n)
    sounds[char] = pygame.mixer.Sound("audio/%s" % filename)
    print "%s) %s" % (char, filename)
        
def send(what):
    wixel.write(what)
    wixel.flush()

def received(char):
    if "0" <= char <= "5":
        pygame.mixer.music.load("music/music%s.ogg" % char)
        pygame.mixer.music.play()

    if "a" <= char <= chr(ord("a") + len(sounds)):
        sounds[char].play()

while 1:
#    while wixel.inWaiting():
#        c = wixel.read()
#        received(c)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if pygame.K_1 <= event.key <= pygame.K_6:
                level = event.key - pygame.K_1
                char = chr(ord("0") + level)
                send(char)
                received(char)
            if pygame.K_a <= event.key < (pygame.K_a + len(sounds)):
                n = event.key - pygame.K_a
                char = chr(ord("a") + n)
                received(char)
            if event.key == pygame.K_LEFT:
                send("L")
            if event.key == pygame.K_RIGHT:
                send("R")
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT:
                send("l")
            if event.key == pygame.K_RIGHT:
                send("r")
    pygame.display.flip()
