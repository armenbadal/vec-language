%{
#include <stdio.h>

extern int yylineno;

extern int yylex();
static int yyerror(const char *s);
%}

%define parse.error verbose

%token xFunction
%token xEnd
%token xIf
%token xThen
%token xElse
%token xFor
%token xEach
%token xIn 
%token xDo
%token xReturn
%token xIdent
%token xNumber

%token xAdd xSub xConc
%token xMul xDiv xMod xProd
%token xEq xNe xLt xLe xGt xGe
%token xLeftPar xRightPar
%token xLeftBr xRightBr
%token xAssign
%token xBar
%token xComma xSemicolon

%left xAdd xSub xConc
%left xMul xDiv xMod xProd
%nonassoc xEq xNe xLt xLe xGt xGe

%start Program
%%
Program
    : FunctionList
    ;

FunctionList
    : FunctionList Function
    | %empty
    ;

Function
    : xFunction xIdent xLeftPar IdentifierListOpt xRightPar StatementList xEnd
    ;

IdentifierListOpt
    : IdentifierList
    | %empty
    ;

IdentifierList
    : IdentifierList xComma xIdent
    | xIdent
    ;

StatementList
    : StatementList xSemicolon Statement
    | Statement
    | %empty
    ;

Statement
    : xIdent xAssign Expression
    | xIdent xLeftBr Expression xRightBr xAssign Expression
    | xIf Expression xThen StatementList xEnd
    | xIf Expression xThen StatementList xElse StatementList xEnd
    | xFor xEach xIdent xIn Expression xDo StatementList xEnd
    | xReturn Expression
    | xIdent xLeftPar ExpressionListOpt xRightPar
    ;

Expression
    : Expression xAdd Expression
    | Expression xSub Expression
    | Expression xMul Expression
    | Expression xDiv Expression
    | Expression xMod Expression
    | Expression xConc Expression
    | Expression xProd Expression
    | Expression xEq Expression
    | Expression xNe Expression
    | Expression xGt Expression
    | Expression xGe Expression
    | Expression xLt Expression
    | Expression xLe Expression
    | Postfix
    ;

Postfix
    : Primary
    | Postfix xLeftBr Expression xRightBr
    ;

Primary
    : xBar Expression xBar
    | xLeftPar Expression xRightPar
    | Postfix xLeftPar ExpressionListOpt xRightPar
    | Vector
    | xIdent
    ;

ExpressionListOpt
    : ExpressionList
    | %empty
    ;

ExpressionList
    : ExpressionList xComma Expression
    | Expression
    ;

Vector
    : xLeftBr ElementListOpt xRightBr
    ;

ElementListOpt
    : ElementList
    | %empty
    ;

ElementList
    : ElementList xComma Element
    | Element
    ;

Element
    : xIdent
    | xNumber
    ;

%%

static int yyerror( const char* message )
{
  fprintf(stderr, "ERROR: (%d) %s\n", yylineno, message);
  return 1;
}
