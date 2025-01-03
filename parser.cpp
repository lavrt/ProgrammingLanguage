#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "vector.h"
#include "tree.h"
#include "debug.h"
#include "dsl.h"

// static --------------------------------------------------------------------------------------------------------------

static tNode* getGrammar(Vector tokenVector);
static tNode* getExpression(Vector tokenVector, int* pos);
static tNode* getMultiplication(Vector tokenVector, int* pos);
static tNode* getParentheses(Vector tokenVector, int* pos);
static tNode* getNumber(Vector tokenVector, int* pos);
static tNode* getVariable(Vector tokenVector, int* pos);
static tNode* getFunction(Vector tokenVector, int* pos);
static tNode* getIf(Vector tokenVector, int* pos);
static tNode* getAssignment(Vector tokenVector, int* pos);
static tNode* getOperation(Vector tokenVector, int* pos);
[[noreturn]] static void syntaxError();

// global --------------------------------------------------------------------------------------------------------------

tNode* runParser(Vector tokenVector)
{
    tNode* root = getGrammar(tokenVector);

    return root;
}

// static --------------------------------------------------------------------------------------------------------------

static tNode* getGrammar(Vector tokenVector)
{
    int pos = 0;

    tNode* node = getExpression(tokenVector, &pos);

    if (strcmp(GET_TOKEN(pos), keyEnd))
    {
        syntaxError();
        pos++;
    }

    return node;
}

static tNode* getExpression(Vector tokenVector, int* pos)
{
    tNode* leftNode = getMultiplication(tokenVector, pos);

    while (!strcmp(GET_TOKEN(*pos), "+") || !strcmp(GET_TOKEN(*pos), "-"))
    {
        int op = *pos;
        (*pos)++;
        tNode* rightNode = getMultiplication(tokenVector, pos);
        if (!strcmp(GET_TOKEN(op), "+"))
        {
            leftNode = ADD(leftNode, rightNode);
        }
        else
        {
            leftNode = SUB(leftNode, rightNode);
        }
    }
    return leftNode;
}

static tNode* getMultiplication(Vector tokenVector, int* pos)
{
    tNode* leftNode = getParentheses(tokenVector, pos);

    while (!strcmp(GET_TOKEN(*pos), "*") || !strcmp(GET_TOKEN(*pos), "/"))
    {
        int op = *pos;
        (*pos)++;
        tNode* rightNode = getParentheses(tokenVector, pos);
        if (!strcmp(GET_TOKEN(op), "*"))
        {
            leftNode = MUL(leftNode, rightNode);
        }
        else
        {
            leftNode = DIV(leftNode, rightNode);
        }
    }
    return leftNode;
}

static tNode* getParentheses(Vector tokenVector, int* pos)
{
    if (!strcmp(GET_TOKEN(*pos), "("))
    {
        (*pos)++;
        tNode* node = getExpression(tokenVector, pos);
        if (strcmp(GET_TOKEN(*pos), ")"))
            syntaxError();
        (*pos)++;
        return node;
    }
    else if (GET_TOKEN_TYPE(*pos) == Identifier)
    {
        // fprintf(stderr, "[SERV]   %s\n", GET_TOKEN(*pos));
        tNode* node = getVariable(tokenVector, pos);
        // fprintf(stderr, "[SERV]   %s\n", GET_TOKEN(*pos));
        return node;
    }
    else if (GET_TOKEN_TYPE(*pos) == Number)    return getNumber  (tokenVector, pos);
    else if (GET_TOKEN_TYPE(*pos) == Operation) return getFunction(tokenVector, pos);
    else assert(0);
}

static tNode* getFunction(Vector tokenVector, int* pos)
{
    if (!strcmp(GET_TOKEN(*pos), keyIf))
    {

    }

//     if (!strcmp(GET_TOKEN(*pos), kLn))
//     {
//         (*pos)++;
//
//         CHECK_LEFT_PARENTHESIS;
//         tNode* node = newNode(Operation, GET_TOKEN(*pos), getExpression(tokenVector, pos), NULL);
//         CHECK_RIGHT_PARENTHESIS;
//
//         return node;
//     }
//     else if (!strcmp(GET_TOKEN(*pos), kLog))
//     {
//         CHECK_LEFT_PARENTHESIS;
//         tNode* leftNode = getExpression(token);
//         CHECK_RIGHT_PARENTHESIS;
//
//         CHECK_LEFT_PARENTHESIS;
//         tNode* node = newNode(Operation, Log, leftNode, getExpression(token));
//         CHECK_RIGHT_PARENTHESIS;
//
//         return node;
//     }
//     else if (!strcmp(GET_TOKEN(*pos), kLg))
//     {
//         MOVE_POS_BY_LENGTH_OF_GET_TOKEN(*pos);
//
//         CHECK_LEFT_PARENTHESIS;
//         tNode* node = newNode(Operation, Lg, getExpression(token), NULL);
//         CHECK_RIGHT_PARENTHESIS;
//
//         return node;
//     }
//     else if (!strcmp(GET_TOKEN(*pos), kSin))
//     {
//         MOVE_POS_BY_LENGTH_OF_GET_TOKEN(*pos);
//
//         CHECK_LEFT_PARENTHESIS;
//         tNode* node = newNode(Operation, Sin, getExpression(token), NULL);
//         CHECK_RIGHT_PARENTHESIS;
//
//         return node;
//     }
//     else if (!strcmp(GET_TOKEN(*pos), kCos))
//     {
//         MOVE_POS_BY_LENGTH_OF_GET_TOKEN(*pos);
//
//         CHECK_LEFT_PARENTHESIS;
//         tNode* node = newNode(Operation, Cos, getExpression(token), NULL);
//         CHECK_RIGHT_PARENTHESIS;
//
//         return node;
//     }
//     else if (!strcmp(GET_TOKEN(*pos), kTg))
//     {
//         MOVE_POS_BY_LENGTH_OF_GET_TOKEN(*pos);
//
//         CHECK_LEFT_PARENTHESIS;
//         tNode* node = newNode(Operation, Tg, getExpression(token), NULL);
//         CHECK_RIGHT_PARENTHESIS;
//
//         return node;
//     }
//     else if (!strcmp(GET_TOKEN(*pos), kCtg))
//     {
//         MOVE_POS_BY_LENGTH_OF_GET_TOKEN(*pos);
//
//         CHECK_LEFT_PARENTHESIS;
//         tNode* node = newNode(Operation, Ctg, getExpression(token), NULL);
//         CHECK_RIGHT_PARENTHESIS;
//
//         return node;
//     }
//     else
//     {
//         FREE(GET_TOKEN(*pos));
//         syntaxError();
//     }
}

static tNode* getNumber(Vector tokenVector, int* pos)
{
    return NUM(GET_TOKEN((*pos)++));
}

static tNode* getVariable(Vector tokenVector, int* pos)
{
    return VAR(GET_TOKEN((*pos)++));
}

// static tNode* getOperation(Vector tokenVector, int* pos)
// {
//     if (!strcmp(GET_TOKEN(*pos), keyIf))
//     {
//         return getIf(tokenVector, pos);
//     }
//     else if (!isKeyWord(GET_TOKEN(*pos)))
//     {
//         getAssignment(tokenVector, pos);
//     }
//     else
//     {
//
//     }
// }
//
// static tNode* getIf(Vector tokenVector, int* pos) // TODO
// {
//     CHECK_LEFT_PARENTHESIS;
//     tNode* node = getExpression(tokenVector, pos);
//     CHECK_RIGHT_PARENTHESIS;
// }
//
// static tNode* getAssignment(Vector tokenVector, int* pos) // TODO
// {
//
// }

static void syntaxError()
{
    fprintf(stderr, "Syntax error\n");

    exit(EXIT_FAILURE);
}
