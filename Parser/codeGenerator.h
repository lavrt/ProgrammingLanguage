#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <stdio.h>

#include "vector.h"
#include "node.h"

struct codeGenerator
{
    FILE* codeFile;
    tNode* node;
    size_t ifCounter;
    size_t whileCounter;

    Vector scopeTable;
    size_t nestingLevel;
    size_t freeIndex;
};

struct symbol
{
    char* ID;
    size_t IDAddress;
    size_t numberOfIDsInScope;
};

const size_t SCOPE_SIZE = 64;
const size_t INITIAL_NUMBER_OF_SCOPES = 5;

void runCodeGenerator(tNode* root);

#endif // CODEGENERATOR_H
