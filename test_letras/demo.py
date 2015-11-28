import pygame

c1 = (255,255,255,255)
l = "01"

g = pygame.image.load("zupay.bmp")

for n in range(256):
    row, col = divmod(n, 16)
    for v in range(6):
        x = col * 6 + v
        byte = []
        for b in range(8):
            y = row * 8 + b
            v = g.get_at((x, y))
            byte.append( l[int(v==c1)])
        print "0b" + "".join(byte) + ","

