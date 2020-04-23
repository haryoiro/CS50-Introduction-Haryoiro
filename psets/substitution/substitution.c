#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void is_error(int argc, string argv[]);
int is_alphabetic_chars(char chars[], int length);
void substitution(char text[], char chars[], int length);
void ctos(int c, string sub, int len);

int main(int argc, string argv[])
{
    is_error(argc, argv);
    int len = strlen(argv[1]);


    string plain = get_string("plaintext:  ");

    substitution(plain, argv[1], len);
}

void is_error(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        exit(1);
    }  
    else if (is_alphabetic_chars(argv[1], strlen(argv[1])) == 1)
    {
        printf("Key must only contain alphabetic characters.\n");
        exit(1);
    }
}

int is_alphabetic_chars(char chars[], int length)
{
    int res = 2015;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j <= length; j++)
        {
            if (chars[i] == chars[j] && i != j)
            {
                exit(1);
            }
        }
        if (chars[i] >= 'A' && chars[i] <= 'Z')
        {
            res -= chars[i];
            // printf("res: %i\n", res);
        }
        else if (chars[i] >= 'a' && chars[i] <= 'z')
        {
            res -= chars[i] - 32;
            // printf("res: %i\n", res);
        }
    }
    if (res == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void substitution(char text[], char chars[], int length)
{
    for (int i = 0, txlen = strlen(text); i < txlen; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            ctos(text[i], chars, length);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}

void ctos(int c, string sub, int len)
{
    for (int i = 0; i <= 26; i++)
    {
        if (64 + i == c)
        {
            if (sub[i] >= 'a' && sub[i] <= 'z')
            {
                // printf("[%i]", i);
                printf("%c", (int)sub[i - 1] - 32);
            }
            else
            {
                printf("%c", (int)sub[i - 1]);
            }
        }
        else if (96 + i == c)
        {
            if (sub[i] >= 'a' && sub[i] <= 'z')
            {
                printf("%c", (int)sub[i - 1]);
            }
            else
            {
                printf("%c", (int)sub[i - 1] + 32);
            }
        }
    }
}