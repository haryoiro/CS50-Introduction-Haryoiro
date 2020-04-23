from cs50 import get_int


def main():
    height = 0
    while True:
        height = get_int("Height: ")
        if height > 0:
            break
    printmario(height)


# printmario(int height)
# @param int height 出力する#の高さ＆幅
#       iで高さを出力，jで横幅を出力
# 
#   入力された高さの左よりピラミッドを標準出力
def printmario(height):
    for i in range(height):
        for j in range(height):
            if j + i < height-1:
                print(" ", end="")
            else:
                print("#", end="")
        print()


main()