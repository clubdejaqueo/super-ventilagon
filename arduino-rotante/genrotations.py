"""
This code precalculates the rotation and mirroring of walls in super ventilagon.
"""

def calculate(n, mirrored, rotated):
    mask1 = (0b111111 << rotated) & 0b111111
    mask2 = (0b111111 >> (6-rotated)) & 0b111111
    
    n = (((n << rotated) & mask1) | ((n >> (6-rotated)) & mask2))

    if mirrored:
        n1 = n
        n = 0
        for i in range(6):
            if n1 & (1<<i):
                n |= (1<<5-i)

    return n

for mirrored in [False, True]:
    print "// Mirrored: %s" % ("yes" if mirrored else "no")
    for rotated in range(6):
        print "// Rotated: %d" % rotated
        for n in range(64):
            x = calculate(n, mirrored, rotated)
            print format(x, '#08b') + ",",
        print
