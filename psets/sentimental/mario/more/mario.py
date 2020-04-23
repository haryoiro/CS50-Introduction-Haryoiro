from cs50 import get_int

def getheight():
    height = get_int("Height: ")
    if height <= 0:
        return getheight()
    elif height is None:
        return getheight()
    else:
        return int(height)

height = getheight()
k = 0
for i in range(height):
    for j in range(height*2+1):
        if height > j:
            if j + i < height-1:
                print(" ", end="")
            else:
                print("#", end="")
        elif height == j:
            print("  ", end="")
        elif height < j:
            if height + i + 1 >= j:
                print("#", end="")
            else:
                print(" ", end="")
    print()