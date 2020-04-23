// Declares a dictionary's functionality

#ifndef DICTIONARY_H    // 重複定義の回避
#define DICTIONARY_H    // 定数定義

#include <stdbool.h>    // bool値を使用するためのヘッダファイル

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
// constを引数として与えられた値は変えられない
bool check(const char *word); 
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
