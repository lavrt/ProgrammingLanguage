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
static tNode* getExpression(Vector tokenVector, size_t* pos);
static tNode* getMultiplication(Vector tokenVector, size_t* pos);
static tNode* getParentheses(Vector tokenVector, size_t* pos);
static tNode* getNumber(Vector tokenVector, size_t* pos);
static tNode* getVariable(Vector tokenVector, size_t* pos);
static tNode* getFunction(Vector tokenVector, size_t* pos);
static tNode* getIf(Vector tokenVector, size_t* pos);
static tNode* getWhile(Vector tokenVector, size_t* pos);
static tNode* getAssignment(Vector tokenVector, size_t* pos);
static tNode* getOperation(Vector tokenVector, size_t* pos);
[[noreturn]] static void syntaxError(int line);

// global --------------------------------------------------------------------------------------------------------------

tNode* runParser(Vector tokenVector)
{
    tNode* root = getGrammar(tokenVector);

    return root;
}

// static --------------------------------------------------------------------------------------------------------------

static tNode* getGrammar(Vector tokenVector)
{
    size_t pos = 0;

    tNode* leftNode = getOperation(tokenVector, &pos);
    if (strcmp(GET_TOKEN(pos++), ";")) syntaxError(__LINE__);
    while (strcmp(GET_TOKEN(pos), keyEnd))
    {
        tNode* rightNode = getOperation(tokenVector, &pos);
        if (strcmp(GET_TOKEN(pos++), ";")) syntaxError(__LINE__);
        leftNode = newNode(Operation, ";", leftNode, rightNode);
    }

    // leftNode = newNode(Operation, "end", leftNode, nullptr);


    // if (strcmp(GET_TOKEN(pos), keyEnd))
    // {  fprintf(stderr, "%s\n", GET_TOKEN(pos));
    //     syntaxError(__LINE__);
    //     pos++;
    // }

    return leftNode;
}

static tNode* getExpression(Vector tokenVector, size_t* pos)
{
    tNode* leftNode = getMultiplication(tokenVector, pos);

    while (!strcmp(GET_TOKEN(*pos), "+") || !strcmp(GET_TOKEN(*pos), "-"))
    {
        size_t op = *pos;
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

static tNode* getMultiplication(Vector tokenVector, size_t* pos)
{
    tNode* leftNode = getParentheses(tokenVector, pos);

    while (!strcmp(GET_TOKEN(*pos), "*") || !strcmp(GET_TOKEN(*pos), "/"))
    {
        size_t op = *pos;
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

static tNode* getParentheses(Vector tokenVector, size_t* pos)
{
    if (!strcmp(GET_TOKEN(*pos), "("))
    {
        (*pos)++;
        tNode* node = getExpression(tokenVector, pos);
        if (strcmp(GET_TOKEN(*pos), ")"))
            syntaxError(__LINE__);
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

static tNode* getFunction(Vector tokenVector, size_t* pos)
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
//         syntaxError(__LINE__);
//     }
}

static tNode* getNumber(Vector tokenVector, size_t* pos)
{
    return NUM(GET_TOKEN((*pos)++));
}

static tNode* getVariable(Vector tokenVector, size_t* pos)
{
    return VAR(GET_TOKEN((*pos)++));
}

static tNode* getOperation(Vector tokenVector, size_t* pos)
{
    if (!strcmp(GET_TOKEN(*pos), keyIf))
    {
        (*pos)++;
        tNode* node = getIf(tokenVector, pos);
        return node;
    }
    if (!strcmp(GET_TOKEN(*pos), keyWhile))
    {
        (*pos)++;
        tNode* node = getWhile(tokenVector, pos);
        return node;
    }
    else if (!strcmp(GET_TOKEN(*pos), "{"))
    {
        (*pos)++;
        tNode* leftNode = getOperation(tokenVector, pos);
        if (strcmp(GET_TOKEN((*pos)++), ";")) syntaxError(__LINE__);
        while (strcmp(GET_TOKEN(*pos), "}"))
        {
            tNode* rightNode = getOperation(tokenVector, pos);
            if (strcmp(GET_TOKEN((*pos)++), ";")) syntaxError(__LINE__);
            leftNode = newNode(Operation, ";", leftNode, rightNode);
        }

        if (strcmp(GET_TOKEN((*pos)++), "}")) syntaxError(__LINE__);

        return leftNode;
    }
    else if (!isKeyWord(GET_TOKEN(*pos)))
    {
        return getAssignment(tokenVector, pos);
    }
    else syntaxError(__LINE__);
}

static tNode* getIf(Vector tokenVector, size_t* pos) // TODO
{
    CHECK_LEFT_PARENTHESIS;
    (*pos)++;
    tNode* leftNode = getExpression(tokenVector, pos);
    CHECK_RIGHT_PARENTHESIS;
    (*pos)++;

    tNode* rightNode = getOperation(tokenVector, pos);

    return newNode(Operation, "if", leftNode, rightNode);
}

static tNode* getWhile(Vector tokenVector, size_t* pos) // TODO
{
    CHECK_LEFT_PARENTHESIS;
    (*pos)++;
    tNode* leftNode = getExpression(tokenVector, pos);
    CHECK_RIGHT_PARENTHESIS;
    (*pos)++;

    tNode* rightNode = getOperation(tokenVector, pos);

    return newNode(Operation, "while", leftNode, rightNode);
}

static tNode* getAssignment(Vector tokenVector, size_t* pos) // TODO
{
    tNode* leftNode = getVariable(tokenVector, pos);
    if (strcmp(GET_TOKEN(*pos), "=")) syntaxError(__LINE__);
    (*pos)++;
    tNode* rightNode = getExpression(tokenVector, pos);
    return newNode(Operation, "=", leftNode, rightNode);
}

static void syntaxError(int line)
{
    fprintf(stderr, "Syntax error in %d\n", line);

    exit(EXIT_FAILURE);
}
