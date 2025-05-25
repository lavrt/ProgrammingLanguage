#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "asm_interpreter.h"
#include "codeGenerator.h"
#include "vector.h"
#include "tokenizer.h"
#include "parser.h"
#include "tree.h"
#include "processor.h"
#include "stack.h"

static const char* DEFAULT_DATA_FILE = "./Backend/Processor/machine_code_in.txt";

int main() {
////////////////////////////////////////
    Vector tokens = tokenizer();

    tNode* root = runParser(tokens);

    dump(root);

    runCodeGenerator(root);

    tokenVectorDtor(&tokens);
    free(tokens.data);

    treeDtor(root);
////////////////////////////////////////
    Assembler ASM = {};

    asmCtor(&ASM);

    twoPassCompilation(&ASM);

    asmDtor(&ASM);
////////////////////////////////////////
    PROCESSOR spu = {};

    FILE* data_file = fopen(DEFAULT_DATA_FILE, "rb");
    assert(data_file);

    spuCtor(&spu, data_file);

    spuRun(&spu);

    spuDtor(&spu);

    return 0;
}