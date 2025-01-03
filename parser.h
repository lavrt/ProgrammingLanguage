#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "node.h"
#include "tokenizer.h"

const size_t kBufferSize = 32;
const size_t kInputStringSize = 128;

const char* const kNameOfInputFile = "expression.txt";

struct Data
{
    char string[kInputStringSize];
    size_t pos;
};

#define MOVE_POS_BY_LENGTH_OF_WORD \
    do { token->pos += strlen(word); FREE(word); } while (0);
#define CHECK_LEFT_PARENTHESIS \
    do { if (strcmp(GET_TOKEN(*pos), "(")) syntaxError(); } while(0);
#define CHECK_RIGHT_PARENTHESIS \
    do { if (strcmp(GET_TOKEN(*pos), ")")) syntaxError(); } while(0);

#define GET_TOKEN(pos_) \
    (((Token*)vectorGet(&tokenVector, pos_))->value)
#define GET_TOKEN_TYPE(pos_) \
    (((Token*)vectorGet(&tokenVector, pos_))->type)

tNode* runParser(Vector tokenVector);

#endif // PARSER_H
