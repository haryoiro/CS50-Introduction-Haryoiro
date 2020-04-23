#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_number(char arr[]);
void caesar_cipher(int num, char text[]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        exit(1);
    }
    else
    {
        if (is_number(argv[1]) == 0)
        {
            string text = get_string("plaintext:  ");
            int num = atoi(argv[1]);
            caesar_cipher(num, text);
        }
        else
        {
            printf("Usage: ./caesar key\n");
            exit(1);
        }
    }
}

int is_number(char arr[])
{
    int result = 0;
    for (int i = 0, len = strlen(arr); i < len; i++)
    {
        if (!(arr[i] >= '0' && arr[i] <= '9'))
        {
            result = 1;
        }
    }
    return result;
}

void caesar_cipher(int n, char text[])
{
    int num = n % 26;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            text[i] += num;
            if (text[i] < 'A')
            {
                text[i] = 'Z' - ('@' - text[i]);
            }
            else if (text[i] > 'Z')
            {
                text[i] = '@' + (text[i] - 'Z');
            }
        } // 大文字アルファベット判定

        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            int sum = (text[i] + num);
            if (sum < 'a')
            {
                text[i] = 'z' - ('`' - sum);
            }
            else if (sum > 'z')
            {
                text[i] = '`' + (sum - 'z');
            }
            else
            {
                text[i] += num;
            }
        } // 小文字アルファベット判定

        else
        {
            text[i] = text[i];
        }

        // printf("%i ", text[i]);
    } // テキスト全体に暗号化

    printf("ciphertext: %s\n", text);
}