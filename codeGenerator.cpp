#include "codeGenerator.h"

#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "tokenizer.h"
#include "tree.h"
#include "debug.h"

void runCodeGenerator(tNode* root)
{
    assert(root);

    codeGenerator cGen = {};

    cGen.node = root;
    cGen.ifCounter = 0;
    cGen.whileCounter = 0;

    cGen.codeFile = fopen("asm_code_in", "wb"); // FIXME const
    assert(cGen.codeFile);

    cGen.scopeTable = {};
    vectorInit(&cGen.scopeTable, 10); // FIXME const

    symbol* symbolTable = (symbol*)calloc(64, sizeof(symbol)); // FIXME const
    assert(symbolTable);
    vectorPush(&cGen.scopeTable, symbolTable);

    generateCode(&cGen);

    fprintf(cGen.codeFile, "hlt");

    FCLOSE(cGen.codeFile);
}

void generateCode(codeGenerator* cGen)
{
    if (!cGen->node)
    {
        return;
    }

    switch (cGen->node->type)
    {
        case Number:
        {
            fprintf(cGen->codeFile, "push %s\n", cGen->node->value);
            break;
        }
        case Identifier:
        {
            int i = cGen->nestingLevel;
            int j = 0;
            bool variableIsKnown = false;

            for (; i >= 0; i--)
            {
                for (; ((symbol*)vectorGet(&cGen->scopeTable, i))[j].ID; j++)
                {
                    if (!strcmp(((symbol*)vectorGet(&cGen->scopeTable, i))[j].ID, cGen->node->value))
                    {
                        variableIsKnown = true;
                        break;
                    }
                }
                if (variableIsKnown)
                {
                    break;
                }
            }

            if (variableIsKnown)
            {
                fprintf(cGen->codeFile, "[%d]\n", ((symbol*)vectorGet(&cGen->scopeTable, i))[j].IDAddress);
                break;
            }

            ((symbol*)vectorGet(&cGen->scopeTable, cGen->nestingLevel))[((symbol*)vectorGet(&cGen->scopeTable, cGen->nestingLevel))->numberOfIDsInScope++].ID = cGen->node->value;
            fprintf(cGen->codeFile, "[%d]\n", cGen->freeIndex++);

            // search for
            // if not, add
            // if there is, use

            break;
        }
        case Operation:
        {
            switch (returnNodeValue(cGen->node->value))
            {
                case Semicolon:
                {
                    tNode* node = cGen->node;
                    cGen->node = node->left;
                    generateCode(cGen);
                    cGen->node = node->right;
                    generateCode(cGen);
                    break;
                }
                case Equal:
                {
                    tNode* node = cGen->node;
                    cGen->node = node->right;
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "pop ");
                    cGen->node = node->left;
                    generateCode(cGen);
                    break;
                }
                case Add:
                {
                    tNode* node = cGen->node;
                    cGen->node = node->left;
                    if (node->left->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    cGen->node = node->right;
                    if (node->right->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "add\n");
                    break;
                }
                case Sub:
                {
                    tNode* node = cGen->node;
                    cGen->node = node->left;
                    if (node->left->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    cGen->node = node->right;
                    if (node->right->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "sub\n");
                    break;
                }
                case Mul:
                {
                    tNode* node = cGen->node;
                    cGen->node = node->left;
                    if (node->left->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    cGen->node = node->right;
                    if (node->right->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "mul\n");
                    break;
                }
                case Div:
                {
                    tNode* node = cGen->node;
                    cGen->node = node->left;
                    if (node->left->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    cGen->node = node->right;
                    if (node->right->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "div\n");
                    break;
                }
                case Sqrt:
                {
                    cGen->node = cGen->node->left;
                    if (cGen->node->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "sqrt\n");
                    break;
                }
                case Sin:
                {
                    cGen->node = cGen->node->left;
                    if (cGen->node->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "sin\n");
                    break;
                }
                case Cos:
                {
                    cGen->node = cGen->node->left;
                    if (cGen->node->type == Identifier)
                    {
                        fprintf(cGen->codeFile, "push ");
                    }
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "cos\n");
                    break;
                }
                case If:
                {
                    cGen->nestingLevel++;
                    symbol* symbolTable = (symbol*)calloc(64, sizeof(symbol)); // FIXME const
                    assert(symbolTable);
                    vectorPush(&cGen->scopeTable, symbolTable);

                    tNode* node = cGen->node;
                    cGen->node = node->left;
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "push 0\n");
                    fprintf(cGen->codeFile, "je LABEL_IF_%d\n", ++cGen->ifCounter);
                    cGen->node = node->right;
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "LABEL_IF_%d:\n", cGen->ifCounter);
                    break;
                }
                case While:
                {
                    cGen->nestingLevel++;
                    symbol* symbolTable = (symbol*)calloc(64, sizeof(symbol)); // FIXME const
                    assert(symbolTable);
                    vectorPush(&cGen->scopeTable, symbolTable);

                    int labelNumber = ++cGen->whileCounter;
                    fprintf(cGen->codeFile, "FIRST_LABEL_WHILE_%d:\n", labelNumber);
                    tNode* node = cGen->node;
                    cGen->node = node->left;
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "push 0\n");
                    fprintf(cGen->codeFile, "je SECOND_LABEL_WHILE_%d\n", labelNumber);
                    cGen->node = node->right;
                    generateCode(cGen);
                    fprintf(cGen->codeFile, "jmp FIRST_LABEL_WHILE_%d\n", labelNumber);
                    fprintf(cGen->codeFile, "SECOND_LABEL_WHILE_%d:\n", labelNumber);
                    break;
                }

                default: break;
            }
            break;
        }

        default: break;
    }
}

Operations returnNodeValue(const char* const word)
{
    if      (!strcmp(word, keyAdd  )) return Add  ;
    else if (!strcmp(word, keySub  )) return Sub  ;
    else if (!strcmp(word, keyMul  )) return Mul  ;
    else if (!strcmp(word, keyDiv  )) return Div  ;
    else if (!strcmp(word, keySqrt )) return Sqrt ;
    else if (!strcmp(word, keySin  )) return Sin  ;
    else if (!strcmp(word, keyCos  )) return Cos  ;
    else if (!strcmp(word, keyIf   )) return If   ;
    else if (!strcmp(word, keyWhile)) return While;
    else if (!strcmp(word, keyEqual)) return Equal;
    else if (!strcmp(word, keySemicolon)) return Semicolon;

    else return NoOperation;
}
