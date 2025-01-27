#include "codeGenerator.h"

#include <assert.h>

#include "tokenizer.h"
#include "node.h"
#include "tree.h"

void runCodeGenerator(tNode* root)
{
    assert(root);

    codeGenerator cGen = {};

    cGen.node = root;
    cGen.ifCounter = 0;
    cGen.whileCounter = 0;

    cGen.codeFile = fopen("asm_code_in", "wb"); // FIXME const
    assert(cGen.codeFile);



    //

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
            fprintf(cGen->codeFile, "push %s\n", cGen->node->value);

            // TODO nameTable

            break;
        }
        case Operation:
        {
            switch (isKeyWord(cGen->node->value))
            {
                case Add:
                {
                    generateCode(cGen->node->left);
                    generateCode(cGen->node->right);
                    fprintf(cGen->codeFile, "add\n");
                    break;
                }
                case Sub:
                {
                    generateCode(cGen->node->left);
                    generateCode(cGen->node->right);
                    fprintf(cGen->codeFile, "sub\n");
                    break;
                }
                case Mul:
                {
                    generateCode(cGen->node->left);
                    generateCode(cGen->node->right);
                    fprintf(cGen->codeFile, "mul\n");
                    break;
                }
                case Div:
                {
                    generateCode(cGen->node->left);
                    generateCode(cGen->node->right);
                    fprintf(cGen->codeFile, "div\n");
                    break;
                }
                case Sqrt:
                {
                    generateCode(cGen->node->left);
                    fprintf(cGen->codeFile, "sqrt\n");
                    break;
                }
                case Sin:
                {
                    generateCode(cGen->node->left);
                    fprintf(cGen->codeFile, "sin\n");
                    break;
                }
                case Cos:
                {
                    generateCode(cGen->node->left);
                    fprintf(cGen->codeFile, "cos\n");
                    break;
                }
                case If:
                {
                    generateCode(cGen->node->left);
                    fprintf(cGen->codeFile, "push 0\n");
                    fprintf(cGen->codeFile, "je LABEL_IF_%d\n", ++cGen->ifCounter);
                    generateCode(cGen->node->right);
                    fprintf(cGen->codeFile, "LABEL_IF_%d:\n", cGen->ifCounter);
                    break;
                }
                case While:
                {
                    int labelNumber = ++cGen->whileCounter;
                    fprintf(cGen->codeFile, "FIRST_LABEL_WHILE_%d:\n", labelNumber);
                    generateCode(cGen->node->left);
                    fprintf(cGen->codeFile, "push 0\n");
                    fprintf(cGen->codeFile, "je SECOND_LABEL_WHILE_%d", labelNumber);
                    generateCode(cGen->node->right);
                    fprintf(cGen->codeFile, "jmp FIRST_LABEL_WHILE_%d:\n", labelNumber);
                    fprintf(cGen->codeFile, "SECOND_LABEL_WHILE_%d", labelNumber);
                    break;
                }

                default: break;
            }
            break;
        }

        default: break;
    }
}
