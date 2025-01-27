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
    Add   =  1,
    Sub   =  2,
    Mul   =  3,
    Div   =  4,
    Sqrt  =  5,
    Sin   =  6,
    Cos   =  7,
    If    =  8,
    While =  9,
};

char* const keySemicolon = ";" ;
char* const keyAdd   = "+"     ;
char* const keySub   = "-"     ;
char* const keyMul   = "*"     ;
char* const keyDiv   = "/"     ;
char* const keySin   = "sin"   ;
char* const keyCos   = "cos"   ;
char* const keySqrt  = "sqrt"  ;
char* const keyEnd   = "end"   ;
char* const keyIf    = "if"    ;
char* const keyWhile = "while" ;
char* const keyEqual = "="     ;
char* const keyLeftParenthesis = "(";
char* const keyRightParenthesis = ")";
char* const keyLeftCurlyBracket = "{";
char* const keyRightCurlyBracket = "}";

#endif // NODE_H
