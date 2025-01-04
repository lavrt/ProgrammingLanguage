#include "vector.h"
#include "tokenizer.h"
#include "parser.h"
#include "tree.h"

int main()
{
    Vector a = tokenizer();

    // fprintf(stderr, "%s\n", ((Token*)vectorGet(&a, 0))->value);
    // fprintf(stderr, "%s\n", ((Token*)vectorGet(&a, 1))->value);
    // fprintf(stderr, "%s\n", ((Token*)vectorGet(&a, 2))->value);

    tNode* root = runParser(a);

    dump(root);

    //_________________________________________________// //TODO func
    FREE(((Token*)vectorGet(&a, 0))->left->value);
    FREE(((Token*)vectorGet(&a, 0))->left);
    for (int i = 0; i < a.capacity; i++)
    {
        free(vectorGet(&a, i));
    }
    //_________________________________________________//

    treeDtor(root);

    return 0;
}
