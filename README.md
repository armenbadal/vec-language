# Վեկտորների ուսուցողական լեզու

> «Ծրագրավորման լեզուների մշակում եւ իրականացում» դասընթացի համար։

## Շարահյուսություն

```
Program
    : FunctionList
    ;

FunctionList
    : FunctionList Function
    | %empty
    ;

Function
    : 'function' IDENT '(' IdentifierList ')' StatementList 'end'
    ;

IdentifierList
    : IdentifierList ',' IDENT
    ;

StatementList
    : StatementList ';' Statement
    ;

Statement
    : IDENT '=' Expression
    | 'if' Expression 'then' StatementList 'end'
    | 'if' Expression 'then' StatementList 'else' StatementList 'end'
    | 'for' 'each' IDENT 'in' Expression 'do' StatementList 'end'
    | 'return' Expression
    | IDENT '(' ExpressionList ')'
    ;

Expression
    : Expression '+' Expression
    | Expression '-' Expression
    | Expression '*' Expression
    | Expression '/' Expression
    | Expression '++' Expression
    | Expression '**' Expression
    | Expression '=' Expression
    | Expression '<>' Expression
    | Expression '>' Expression
    | Expression '>=' Expression
    | Expression '<' Expression
    | Expression '<=' Expression
    | '|' Expression '|'
    | VectorLiteral
    | IDENT '[' Expression ']'
    | IDENT '[' Expression ':' Expression ']'
    | IDENT
    ;

VectorLiteral
    : '[' ExpressionList ']'
    ;
```


## Սեմանտիկա

1. `if` հրամանի պայմանում _կեղծ_ (_false_) արժեքը որոշվում է դատարկ վեկտորով. `[]`։


## Օրինակներ

### Վեկտորի ամենամեծ տարրը որոշելը

```
function max(v)
    m = v[0];
    for each e in v do
        if e > m then
            m = e
        end
    end
    return m
end
```


