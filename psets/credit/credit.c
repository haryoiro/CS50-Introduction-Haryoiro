#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_digit(long int num);
int is_even(int num);

int main(void)
{
    int result;
    long int number = get_long("Number: ");
    printf("getlong%ld\n", number);
    // printf("pow%1.0Lf", powl(10, 2));
    get_digit(number);
}

int get_digit(long int num)
{
    int max = 16;
    int a[max + 2];
    int ec, oc;
    ec = 0;
    oc = 0;
    int odd[max / 2 + 1];
    int even_sum = 0;
    int odd_sum = 0;
    a[0] = 0;
    int r = 0;
    for (int i = 1; i <= max; i++)
    {
        long int digit, pre_digit;
        digit = powl(10, i);
        pre_digit = powl(10, i - 1);
        // printf("%1.0ld\n", digit);
        a[i] = (num % digit - num % pre_digit) / pre_digit;
        // printf("%i: ", i);
        // printf("%i\n", a[i]);
    }
    for (int j = 1; j <= max; j++)
    {
        if (is_even(j) == 1)
        {
            even_sum += a[j];
        }
        else
        {
            odd[oc] = a[j];
            oc++;
        } 
    }
    for (int k = 0; k < oc; k++)
    {
        if ((odd[k] * 2) >= 10)
        {
            even_sum += (odd[k] * 2) - 9;
        }
        else
        {
            odd_sum += odd[k] * 2;
        }
    }
    // printf("%i\n",(odd_sum + even_sum)%10);
    if ((odd_sum + even_sum) % 10 == 0) // チェックサム成功
    {
        if ((a[16] + a[15] + a[14]) == 0)
        {
            if (a[13] == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (a[16] == 0)
        {
            if (a[15] == 3)
            {
                if (a[14] == 4 || a[14] == 7)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (a[16] > 0)
        {
            if (a[16] == 4)
            {
                printf("VISA\n");
            }
            else if (a[16] == 5)
            {
                if (a[15] >= 6)
                {
                    printf("INVALID\n");
                }
                else if (a[15] >= 1 || a[15] <= 5)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else    // チェックサム失敗
    {
        printf("INVALID\n");
    }
    return r;
}
int is_even(int a)
{
    if (a % 2 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
