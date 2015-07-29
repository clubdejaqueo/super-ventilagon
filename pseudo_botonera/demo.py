#!/usr/bin/arch -i386 /usr/bin/python

import os
import pygame
import serial
import sys

#from serial.tools import list_ports

size = width, height = 640, 480
black = (0, 0, 0)

ARDUINO = "/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_753383235353518141E1-if00"
WIXEL = "/dev/serial/by-id/usb-Pololu_Corporation_Wixel_52-C6-A2-41-if00"

# ------
# serial

#ports = list_ports.comports()
#for name, desc, hwid in ports:
    #print name

wixel = serial.Serial(WIXEL, baudrate=57600, timeout=0)
wixel.open()

arduino = serial.Serial(ARDUINO, baudrate=57600, timeout=0)
arduino.open()

#wixel = sys.stdout

# ------
# pygame

pygame.mixer.pre_init(44100)
pygame.init()
screen = pygame.display.set_mode(size)
screen.fill(black)

sounds = {}
for n, filename in enumerate(sorted(os.listdir("audio"))):
    char = chr(ord("a") + n)
    sounds[char] = pygame.mixer.Sound("audio/%s" % filename)
    print "%s) %s" % (char, filename)
        
def send(what):
    wixel.write(what)
    wixel.flush()

def received(char):
    if "0" == char:
        pygame.mixer.music.stop()

    if "1" <= char <= "3":
        print "loading music", char
        pygame.mixer.music.load("music/ventilagon%s.wav" % char)
        pygame.mixer.music.play(-1)

    if "a" <= char <= chr(ord("a") + len(sounds)):
        sounds[char].play()

selected_level = "0"

while 1:
    while arduino.inWaiting():
        c = arduino.read()
	if c in "012345":
	    if selected_level != c:
	        selected_level = c
	        print "\nSelecting level", c
	        send(c)
    while wixel.inWaiting():
        c = wixel.read()
        print c,
        received(c)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if pygame.K_1 <= event.key <= pygame.K_6:
                level = event.key - pygame.K_1 + 1
                char = chr(ord("0") + level)
                send(char)
                print "\nSelecting level", char
#                received(char)
            if pygame.K_a <= event.key < (pygame.K_a + len(sounds)):
                n = event.key - pygame.K_a
                char = chr(ord("a") + n)
                received(char)
            if event.key in (pygame.K_LEFT, pygame.K_9):
                send("L")
            if event.key in (pygame.K_RIGHT, pygame.K_7):
                send("R")
        elif event.type == pygame.KEYUP:
            if event.key in (pygame.K_LEFT, pygame.K_9):
                send("l")
            if event.key in (pygame.K_RIGHT, pygame.K_7):
                send("r")
    
    pygame.display.flip()
