%{
#include "parser.h"
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
"let"       { return xLet; }
{ident}     { return xIdent; }
"++"        { return xConc; }
"**"        { return xProd; }
"+"         { return xAdd; }
"-"         { return xSub; }
"*"         { return xMul; }
"/"         { return xDiv; }
"%"         { return xMod; }
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
"|"         { return xBar; }
","         { return xComma; }
";"         { return xSemicolon; }
":"         { return xColon; }
.           { return (int)yytext[0]; }
