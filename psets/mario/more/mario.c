#include <cs50.h>
#include <stdio.h>

int get_one_eight_int(string str);

int main(void)
{
    int h, c, d;
    h = get_one_eight_int("Height: ");
    c = h - 1;
    d = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (j == c)
            {
                for (int k = 0; k < h; k++)
                {
                    if (d > 0)
                    {
                        printf("#");
                        d--;
                    }
                }
                printf("#  ");
            }
            if (c <= j)
            {
                printf("#");
                d++;
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
        c--;
    }
}

int get_one_eight_int(string str)
{
    int x;
    x = get_int("%s", str);
    if (x < 1 || x > 8)
    {
        return x = get_int("%s", str);
    }
    else
    {
        return x;
    }
}
