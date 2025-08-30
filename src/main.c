#include <stdio.h>

#include "parser.h"

int main()
{
    yyparse();
    printf("Ok\n");
    return 0;
}
