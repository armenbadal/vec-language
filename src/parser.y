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
%token xLet
%token xIdent
%token xNumber

%token xAdd xSub xConc
%token xMul xDiv xMod xProd
%token xEq xNe xLt xLe xGt xGe
%token xLeftPar xRightPar
%token xLeftBr xRightBr
%token xBar
%token xComma xSemicolon xColon

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
    : xLet Place xEq Expression
    | xIf Expression xThen StatementList xEnd
    | xIf Expression xThen StatementList xElse StatementList xEnd
    | xFor xEach xIdent xIn Expression xDo StatementList xEnd
    | xReturn Expression
    | xIdent xLeftPar ExpressionListOpt xRightPar
    ;

Place
    : xIdent
    | xIdent xLeftBr Expression xRightBr
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
    | UnaryExpression
    ;

UnaryExpression
    : xSub UnaryExpression
    | PostfixExpression
    ;

PostfixExpression
    : PrimaryExpression
    | PostfixExpression xLeftPar ExpressionListOpt xRightPar
    | PostfixExpression xLeftBr Expression xRightBr
    | PostfixExpression xLeftBr Expression xColon Expression xRightBr
    ;

PrimaryExpression
    : xBar Expression xBar
    | xLeftPar Expression xRightPar
    | VectorLiteral
    | xIdent
    | xNumber
    ;

ExpressionListOpt
    : ExpressionList
    | %empty
    ;

ExpressionList
    : ExpressionList xComma Expression
    | Expression
    ;

VectorLiteral
    : xLeftBr ExpressionListOpt xRightBr
    ;

%%

static int yyerror( const char* message )
{
  fprintf(stderr, "ERROR: (%d) %s\n", yylineno, message);
  return 1;
}
