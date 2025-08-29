%{
%}

%error-verbose

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

%token xLeftPar xRightPar
%token xLeftBr xRightBr
%token xVert
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
    : 'function' IDENT '(' IdentifierListOpt ')' StatementList 'end'
    ;

IdentifierListOpt
    : IdentifierList
    | %empty
    ;

IdentifierList
    : IdentifierList ',' IDENT
    | IDENT
    ;

StatementList
    : StatementList ';' Statement
    | Statement
    ;

Statement
    : IDENT '=' Expression
    | IDENT '[' Expression ']' '=' Expression
    | 'if' Expression 'then' StatementList 'end'
    | 'if' Expression 'then' StatementList 'else' StatementList 'end'
    | 'for' 'each' IDENT 'in' Expression 'do' StatementList 'end'
    | 'return' Expression
    | IDENT '(' ExpressionListOpt ')'
    ;

Expression
    : Expression '+' Expression
    | Expression '-' Expression
    | Expression '*' Expression
    | Expression '/' Expression
    | Expression '%' Expression
    | Expression '++' Expression
    | Expression '**' Expression
    | Expression '=' Expression
    | Expression '<>' Expression
    | Expression '>' Expression
    | Expression '>=' Expression
    | Expression '<' Expression
    | Expression '<=' Expression
    | '|' Expression '|'
    | IDENT '[' Expression ']'
    | IDENT '[' Expression ':' Expression ']'
    | IDENT '(' ExpressionListOpt ')'
    | Vector
    | IDENT
    ;

ExpressionListOpt
    : ExpressionList
    | %empty
    ;

ExpressionList:
    : ExpressionList ',' Expression
    | Expression
    ;

Vector
    : '[' ExpressionListOpt ']'
    ;

