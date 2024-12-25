#include "vector.h"
#include "tokenizer.h"

int main()
{
    Vector vec;
    vectorInit(&vec, 10);
    Vector a = tokenizer();
    // fprintf(stderr, "%s\n", ((Token*)vectorGet(&a, 2))->left->left->value);


    return 0;
}
