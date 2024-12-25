#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>

#include "node.h"
#include "vector.h"

const int kInitialSizeOfTokenVector = 64;
const char* const kNameOfFileWithCode = "code.txt";

struct Token
{
    NodeType type;
    char* value;
    Token* left;
    Token* right;
};

Vector tokenizer();
size_t getFileSize(FILE* file);
Operations isKeyWord(const char* const word);

#define FREE(ptr_) \
    do { free(ptr_); ptr_ = nullptr; } while(0);
#define FCLOSE(ptr_) \
    do { fclose(ptr_); ptr_ = NULL; } while(0);

#endif // TOKENIZER_H
