#include<stdio.h>
#include<cs50.h>
#include<math.h>

float get_unsigned_float(string str);
int minimize(int n);
int number_of_coins(int cash, int coin);

int main(void)
{
    float dollers;
    int cent;
    dollers = get_unsigned_float("Change: ");
    cent = round(dollers * 100);
    printf("%i\n", minimize(cent));
}

float get_unsigned_float(string str)
{
    float n;
    n = get_float("%s", str);
    if (n < 0)
    {
        return n = get_unsigned_float(str);
    }
    else
    {
        return n;
    }
}

int minimize(int cent)
{
    int result, quaters, dimes, nickels, pennies; 
    result = cent;

    quaters = number_of_coins(result, 25);
    result = cent % 25;
    dimes = number_of_coins(result, 10);
    result = result % 10;
    nickels = number_of_coins(result, 5);
    result = result % 5;
    pennies = number_of_coins(result, 1);
    result = result % 1;
    return pennies + nickels + dimes + quaters;
}

int number_of_coins(int cash, int coin)
{
    int r = cash % coin;
    int coins = (cash - r) / coin;
    return coins;
}
