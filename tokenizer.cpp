#include "tokenizer.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"
#include "tree.h"
#include "debug.h"

Vector tokenizer()
{
    FILE* inputFile = fopen(kNameOfFileWithCode, "r");
    assert(inputFile);

    size_t fileSize = getFileSize(inputFile);

    char* dataArray = (char*)calloc(fileSize + 1, sizeof(char));
    assert(dataArray);

    fread(dataArray, sizeof(char), fileSize, inputFile);

    Vector tokenVector;
    vectorInit(&tokenVector, kInitialSizeOfTokenVector);

    for (char* pointerToWord = strtok(dataArray, " \n"); pointerToWord; pointerToWord = strtok(NULL, " \n"))
    {
        Token* currentToken = (Token*)calloc(1, sizeof(Token));
        assert(currentToken);

        currentToken->value = pointerToWord;

        if (tokenVector.size)
        {
            currentToken->left = (Token*)vectorGet(&tokenVector, tokenVector.size - 1);
            ((Token*)vectorGet(&tokenVector, tokenVector.size - 1))->right = currentToken;
        }
        else
        {
            Token* serviceToken = (Token*)calloc(1, sizeof(Token));
            assert(serviceToken);

            currentToken->left = serviceToken;

            serviceToken->value = dataArray;
        }

        if (isKeyWord(pointerToWord))
        {
            currentToken->type = Operation;
        }
        else if (isdigit(pointerToWord[0]))
        {
            currentToken->type = Number;
        }
        else
        {
            currentToken->type = Identifier;
        }

        vectorPush(&tokenVector, currentToken);
    }

    return tokenVector;
}

size_t getFileSize(FILE* file)
{
    assert(file);

    long currentPos = ftell(file);
    fseek(file, 0, SEEK_END);
    size_t size = (size_t)ftell(file);
    fseek(file, currentPos, SEEK_SET);

    return size;
}

Operations isKeyWord(const char* const word)
{
    if      (!strcmp(word, keyAdd)) return Add;
    else if (!strcmp(word, keySub)) return Sub;
    else if (!strcmp(word, keyMul)) return Mul;
    else if (!strcmp(word, keyDiv)) return Div;
    else if (!strcmp(word, keyDeg)) return Deg;
    else if (!strcmp(word, keyLn )) return Ln ;
    else if (!strcmp(word, keyLog)) return Log;
    else if (!strcmp(word, keyLg )) return Lg ;
    else if (!strcmp(word, keySin)) return Sin;
    else if (!strcmp(word, keyCos)) return Cos;
    else if (!strcmp(word, keyTg )) return Tg ;
    else if (!strcmp(word, keyCtg)) return Ctg;
    else if (!strcmp(word, keyIf )) return If ;
    else                            return NoOperation;
}
