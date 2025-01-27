#include "vector.h"
#include "tokenizer.h"
#include "parser.h"
#include "tree.h"

int main()
{
    Vector a = tokenizer();

    tNode* root = runParser(a);

    dump(root);

    //_________________________________________________// //TODO func
    FREE(((Token*)vectorGet(&a, 0))->left->value);
    FREE(((Token*)vectorGet(&a, 0))->left);
    for (size_t i = 0; i < a.size; i++)
    {
        free(vectorGet(&a, i));
    }
    //_________________________________________________//

    treeDtor(root);

    return 0;
}
