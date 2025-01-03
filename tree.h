#ifndef TREE_H
#define TREE_H

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FREE(ptr_) \
    do { free(ptr_); ptr_ = NULL; } while(0);
#define FCLOSE(ptr_) \
    do { fclose(ptr_); ptr_ = NULL; } while(0);

const char* const kDumpFileName = "dump.gv";
const char* const kFirstDerivativeDumpFileName = "dumpFirstDerivative.gv";
const char* const kSecondDerivativeDumpFileName = "dumpSecondDerivative.gv";

const char* const kNumber = "number";
const char* const kVariable = "variable";
const char* const kOperation = "operation";

const char* const kAdd = "+"  ;
const char* const kSub = "-"  ;
const char* const kMul = "*"  ;
const char* const kDiv = "/"  ;
const char* const kDeg = "^"  ;
const char* const kLn  = "ln" ;
const char* const kLog = "log";
const char* const kLg  = "lg" ;
const char* const kSin = "sin";
const char* const kCos = "cos";
const char* const kTg  = "tg" ;
const char* const kCtg = "ctg";

tNode* newNode(NodeType type, char* value, tNode* left, tNode* right);
void treeDtor(tNode* node);
void dump(tNode* root);
tNode* copyNode(tNode* node);
bool subtreeContainsVariable(tNode* node);

#endif // TREE_H
