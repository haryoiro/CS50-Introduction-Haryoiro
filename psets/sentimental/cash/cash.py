from cs50 import get_float


def getnumber():
    num = get_float("Change owed: ")
    if num <= 0:
        return getnumber()
    elif num is None:
        return getnumber()
    else:
        return float(num)


cash = getnumber()
cash *= 100
res = 0

quaters, dimes, nickels, pennies = 0, 0, 0, 0

while cash != 0:
    if cash / 25 >= 1:
        quaters = (cash - (cash % 25)) / 25
        cash = cash - quaters * 25
    elif cash / 10 >= 1:
        dimes = (cash - (cash % 10)) / 10
        cash = cash - dimes * 10
    elif cash / 5 >= 1:
        nickels = (cash - (cash % 5)) / 5
        cash = cash - nickels * 5
    elif cash / 1 >= 1:
        pennies = (cash - (cash % 1)) / 1
        cash = cash - pennies * 1
    else:
        break

res = quaters + dimes + nickels + pennies
print(f"{int(res)}")