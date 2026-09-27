#include <stdio.h>

#include "parser.h"

int main()
{
    if (yyparse() != 0)
        return 1;

    printf("Ok\n");
    return 0;
}
