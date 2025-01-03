#ifndef NODE_H
#define NODE_H

enum NodeType
{
    Number     = 1,
    Operation  = 2,
    Identifier = 3,
};

struct tNode
{
    NodeType type;
    char* value;
    tNode* left;
    tNode* right;
};

enum Operations
{
    NoOperation = 0,
    Add  = 1,
    Sub  = 2,
    Mul  = 3,
    Div  = 4,
    Deg  = 5,
    Ln   = 6,
    Log  = 7,
    Lg   = 8,
    Sin  = 9,
    Cos  = 10,
    Tg   = 11,
    Ctg  = 12,
    uSub = 13,
    If   = 14,
};

const char* const keyAdd = "+"  ;
const char* const keySub = "-"  ;
const char* const keyMul = "*"  ;
const char* const keyDiv = "/"  ;
const char* const keyDeg = "^"  ;
const char* const keyLn  = "ln" ;
const char* const keyLog = "log";
const char* const keyLg  = "lg" ;
const char* const keySin = "sin";
const char* const keyCos = "cos";
const char* const keyTg  = "tg" ;
const char* const keyCtg = "ctg";
const char* const keyEnd = "end";
const char* const keyIf  = "if" ;

#endif // NODE_H
