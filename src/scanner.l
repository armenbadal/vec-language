%{

%}

%option noyywrap
%option yylineno

number      [0-9]+(\.[0-9]+)?
ident       [a-zA-Z][_a-zA-Z0-9]*
comment     \'.*$

%%
[ \t\n\r]   { /**/ }
{comment}   { /**/ }
{number}    { return xNumber; }
"function"  { return xFunction; }
"end"       { return xEnd; }
"if"        { return xIf; }
"then"      { return xThen; }
"else"      { return xElse; }
"for"       { return xFor; }
"each"      { return xEach; }
"in"        { return xIn; }
"do"        { return xDo; }
"return"    { return xReturn; }
{ident}     { return xIdent; }
"++"        { return xConc; }
"**"        { return xProd; }
"+"         { return xAdd; }
"-"         { return xSub; }
"*"         { return xMul; }
"/"         { return xDiv; }
"="         { return xEq; }
"<>"        { return xNe; }
">"         { return xGt; }
">="        { return xGe; }
"<"         { return xLt; }
"<="        { return xLe; }
"("         { return xLeftPar; }
")"         { return xRightPar; }
"["         { return xLeftBr; }
"]"         { return xRightBr; }
"|"         { return xVert; }
","         { return xComma; }
";"         { return xSemicolon; }
.           { return (int)yytext[0]; }
