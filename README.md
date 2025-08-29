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
    : 'function' IDENT '(' IdentifierListOpt ')' StatementList 'end'
    ;

IdentifierListOpt
    : IdentifierList
    | %empty
    ;

IdentifierList
    : IdentifierList ',' IDENT
    ;

StatementList
    : StatementList ';' Statement
    ;

Statement
    : IDENT '=' Expression
    | IDENT '[' Expression ']' = Expression
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
    | VectorLiteral
    | IDENT '[' Expression ']'
    | IDENT '[' Expression ':' Expression ']'
    | IDENT '(' ExpressionListOpt ')'
    | IDENT
    ;

ExpressionListOpt
    : ExpressionList
    | %empty
    ;

ExpressionList:
    : ExpressionList ',' Expression
    ;

VectorLiteral
    : '[' ExpressionListOpt ']'
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

### Էրատոսթենեսի մաղը

```
function prime_numbers(n)
    nums = iota(1, n);
    for each d in iota(2, n/2) do
        for each e in nums do
            if e % d = [0] then
                e = [0]
            end
        end
    end
    
    primes = []
    for each e in nums do
        if e <> [0] then
            primes = primes ++ e
        end
    end
    return primes
end
```
