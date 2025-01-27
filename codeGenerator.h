#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <stdio.h>

struct codeGenerator
{
    FILE* codeFile;
    tNode* node;
    size_t ifCounter;
    size_t whileCounter;
};

void runCodeGenerator(tNode* root);
void generateCode(codeGenerator* cGen);

#endif // CODEGENERATOR_H
