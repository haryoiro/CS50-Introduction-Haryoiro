// Caleman-Liau-index
#include "cs50.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

int count_letters(char text[]);
int count_words(char text[]);
int count_sentences(char text[]);
int calc_cli(int letters, int words, int senences);
void cli_grade(int index);


int main(void)
{
    int letters, words, sentences, index;
    string text = get_string("Text: ");
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);
    printf("%i letter(s)\n", letters);
    printf("%i word(s)\n", words);
    printf("%i sentence(s)\n", sentences);
    index = calc_cli(letters, words, sentences);
    cli_grade(index);
}


// 文字数の計測
// a-z, A-Zのみを対象として文字数をカウントする。
int count_letters(char text[])
{
    int count = 0;
    for(int i = 0, len = strlen(text); i < len; i++)
    {
        if  ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            count++;
        }
    }
    return count;
}

// 単語数の計測
// スペースで区切られた文字を単語"sister-in-law"をみなす。
// ハイフンで繋がれた単語は、まとめて一つの単語として考える。
int count_words(char text[])
{
    int count = 1;
    for(int i = 0, len = strlen(text); i < len; i++)
    {
        if  (text[i] == 32)
        {
            count++;
        }
    }
    return count;
}

// 文章の計測
// '.', '!', '?' を文の終わりとする。
int count_sentences(char text[])
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if(text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

int calc_cli(int letters, int words, int sentences)
{
    float l = (float)letters / (float)words * 100;
    float s = (float)sentences / (float)words * 100;
    float index = 0.0588 * l - 0.296 * s - 15.8;
    return round(index);
}

void cli_grade(int index)
{
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}