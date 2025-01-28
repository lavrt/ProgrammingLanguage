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
    const char* value;
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
    Semicolon = 10,
    Equal = 11,
    Print = 12,
};

const char* const keySemicolon = ";" ;
const char* const keyAdd   = "+"     ;
const char* const keySub   = "-"     ;
const char* const keyMul   = "*"     ;
const char* const keyDiv   = "/"     ;
const char* const keySin   = "sin"   ;
const char* const keyCos   = "cos"   ;
const char* const keySqrt  = "sqrt"  ;
const char* const keyEnd   = "end"   ;
const char* const keyIf    = "if"    ;
const char* const keyWhile = "while" ;
const char* const keyEqual = "="     ;
const char* const keyLeftParenthesis = "(";
const char* const keyRightParenthesis = ")";
const char* const keyLeftCurlyBracket = "{";
const char* const keyRightCurlyBracket = "}";
const char* const keyPrint = "print";

#endif // NODE_H
