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

void runCodeGenerator(tNode* root);
void generateCode(codeGenerator* cGen);
Operations returnNodeValue(const char* const word);

#endif // CODEGENERATOR_H
