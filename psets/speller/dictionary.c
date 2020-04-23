// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
// ハッシュテーブルのためのnode型
typedef struct _node
{
    char word[LENGTH + 1];
    struct _node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17756;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int h = hash(word);
    
    if (table[h] == NULL)
    {
        return false;
    }
    else if (table[h] != NULL)
    {
        node *c = table[h];
        while (c != NULL)
        {
            int i;
            i = strcasecmp(c->word, word);
            if(i == 0)
            {
                return true;
            }
            else
            {
                c = c->next;
            }
        }
    }
    return false;
}

// Hashes word to a number
/**
 * Adapted by Neel Mehta from
 * https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
 */
unsigned int hash(const char *word)
{
    // printf("strlen %lu\n", strlen(word));
    unsigned int h = 17756;
    unsigned int r = 0;
    for (const char* ptr = word; *ptr != '\0'; ptr++)
    {
        h = ((h << 5) + h) + tolower(*ptr);
    }
    r = h % N;
    return r;
}
FILE* dicptr = NULL;
unsigned int count = 0;
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // printf("%s", *&dictionary);
    //  -> dictionaries/large
    char w[LENGTH+1];
    unsigned int h = 0;

    // メモリが確保できなかった場合false
    dicptr = fopen(*&dictionary, "r");
    if (dicptr == NULL)
    {
        unload();
        return false;
    }
    
    // ファイルから文字列を読み込む
    while (fscanf(dicptr, "%s", w) != EOF)
    {
        
    node* tmp = NULL;
        h = hash(w);
        // printf("len %lu size %i\n", strlen(w), count);
        count += 1;
            // table[h]がNULLならそのまま代入
            // table[h]がNULl以外ならnextを参照しNULLなら代入
        tmp = (node*)malloc(sizeof(node));
        memset(tmp, 0, sizeof(node));
        if (tmp == NULL)
        {
            unload();
            return false;
        }
        strcpy(tmp->word, w);
        if (table[h] == NULL)
        {
            table[h] = tmp;
        }
        else
        {
            tmp->next = table[h];
            table[h] = tmp;
        }
    }
    
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // printf("count %i\n", count);
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp = NULL;
    node *list = NULL;
    for (int i = 0; i <= N; ++i)
    {
        tmp = table[i];
        while(tmp != NULL)
        {
            list = tmp->next;
            free(tmp);
            tmp = list;
        }
    }
    if (fclose(dicptr) == EOF)
    {
        return false;
    }
    return true;
}
// Loads dictionary into memory, returning true if successful else false
