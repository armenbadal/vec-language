# Վեկտորների ուսուցողական լեզու

> «Ծրագրավորման լեզուների մշակում եւ իրականացում» դասընթացի համար։

Սա միաչափ վեկտորների հետ աշխատող ծրագրավորման լեզու է ու դրա ինտերպրետատորը։
Լեզուն ունի միակ տիպ՝ `vector`։ Բոլոր գործողությունները, հրամանները կատարվում են
այդ տիպի շուրջը։

## Շարահյուսություն

```yacc
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
    | %empty
    ;

Statement
    : 'let' Place '=' Expression
    | 'if' Expression 'then' StatementList 'end'
    | 'if' Expression 'then' StatementList 'else' StatementList 'end'
    | 'for' 'each' IDENT 'in' Expression 'do' StatementList 'end'
    | 'return' Expression
    | IDENT '(' ExpressionListOpt ')'
    ;

Place
    : IDENT
    | IDENT '[' Expression ']'
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
    | UnaryExpression
    ;

UnaryExpression
    : '-' UnaryExpression
    | PostfixExpression
    ;

PostfixExpression
    : PrimaryExpression
    | PostfixExpression '(' ExpressionListOpt ')'
    | PostfixExpression '[' Expression ']'
    | PostfixExpression '[' Expression ':' Expression ']'
    ;

PrimaryExpression
    : NUMBER
    | IDENT
    | VectorLiteral
    | '(' Expression ')'
    | '|' Expression '|'
    ;

ExpressionListOpt
    : ExpressionList
    | %empty
    ;

ExpressionList
    : ExpressionList ',' Expression
    | Expression
    ;

VectorLiteral
    : '[' ExpressionListOpt ']'
    ;
```

Այս նկարագրությամբ՝

- ծրագիրը բաղկացած է զրո կամ ավելի ֆունկցիաներից,
- ֆունկցիայի և կառավարման բլոկի մարմինը կարող է դատարկ լինել,
- հրամանները բաժանվում են `;`-ով, իսկ վերջին հրամանից հետո `;` պարտադիր չէ,
- `=`-ն օգտագործվում է և՛ վերագրման, և՛ հավասարության համեմատման համար․ `let Place = Expression` ձևը վերագրում է, իսկ արտահայտության ներսում `Expression = Expression` ձևը համեմատում է,
- վերագրման թիրախը կարող է լինել identifier կամ մեկ ինդեքսավորմամբ տարր․ շղթայված ինդեքսավորումը, օրինակ՝ `let matrix[i][j] = value`, չի թույլատրվում,
- ֆունկցիայի կանչը, ինդեքսավորումը և slice-ը postfix գործողություններ են և կարող են շղթայվել,
- `v[a:b]`-ը վերցնում է `v`-ի՝ `a`-ից մինչև `b` սահմաններով հատվածը,
- slice-ը չի կարող լինել վերագրման թիրախ, հետևաբար `let v[a:b] = value` ձևն անվավեր է,
- `|v|`-ը վերադարձնում է վեկտորի երկարությունը՝ մեկ տարրանոց վեկտորի տեսքով,
- vector literal-ի յուրաքանչյուր անդամ կարող է լինել ցանկացած արտահայտություն․ անդամների արդյունք վեկտորները հերթականությամբ միավորվում են մեկ հարթ վեկտորի մեջ,
- `[1, 2, 3]`-ը երեք տարր ունեցող հարթ վեկտոր է, իսկ `[a, f(b)]`-ն համարժեք է `a ++ f(b)` արտահայտությանը։

Ինդեքսը, slice-ի սահմանները և չափ նշանակող մյուս արժեքները նույնպես վեկտորներ են։ Կատարման ժամանակ դրանք պետք է լինեն մեկ տարրանոց թվային վեկտորներ։ Այդ պատճառով `v[0]`-ը `v[[0]]`-ի համարժեք, ավելի կարճ գրությունն է։

### Բառային միավորներ

- `IDENT` — սկսվում է լատինական տառով, որին կարող են հաջորդել լատինական տառեր, թվանշաններ կամ `_`,
- `NUMBER` — ոչ բացասական ամբողջ կամ տասնորդական թիվ, օրինակ՝ `0`, `12`, `3.14`,
- մեկնաբանությունը սկսվում է `'` նշանով և շարունակվում մինչև տողի վերջը,
- բացատները, tab-երը և տողադարձերը նշանակություն չունեն, բացի բառային միավորներն իրարից բաժանելուց։

Ծառայողական բառերն են՝ `function`, `end`, `let`, `if`, `then`, `else`, `for`, `each`, `in`, `do`, `return`։

### Օպերատորների առաջնահերթություն

Բարձրից ցածր առաջնահերթությամբ՝

1. ֆունկցիայի կանչ `()`, ինդեքսավորում `[]` և slice `[a:b]`,
2. ունար `-`,
3. `*`, `/`, `%`, `**`,
4. երկտեղանի `+`, `-`, `++`,
5. `=`, `<>`, `<`, `<=`, `>`, `>=`։

Թվաբանական և վեկտորային գործողությունները ձախ ասոցիատիվ են։ Համեմատությունները ոչ ասոցիատիվ են, հետևաբար `a < b < c` գրառումը չի թույլատրվում և պետք է արտահայտվի առանձին համեմատություններով։


## Սեմանտիկա

1. Լեզվի միակ տիպը `vector` է։ Բոլոր փոփոխականները, պարամետրերը, ֆունկցիաների արդյունքները և արտահայտությունների արժեքները վեկտորներ են։
2. Արտահայտության դիրքում `NUMBER`-ը մեկ տարրանոց վեկտորի syntactic sugar է, օրինակ՝ `1` ≡ `[1]`։ Այն նոր սկալյար տիպ չի ստեղծում։
3. Ունար `-`-ը վեկտորի բոլոր տարրերի նշանները փոխում է։ Բացասական թվային literal առանձին գոյություն չունի․ `-1`-ը `-[1]` արտահայտության կարճ գրությունն է, իսկ `-[1, 2]`-ի արժեքը `[-1, -2]` է։
4. Vector literal-ի անդամ արտահայտությունները գնահատվում են ձախից աջ, և դրանց արդյունք վեկտորները կոնկատենացվում են։ Օրինակ՝ եթե `a = [1, 2]`, ապա `[0, a, 3]`-ի արժեքը `[0, 1, 2, 3]` է։ Ներդրված վեկտորներ չեն ստեղծվում։
5. `if` հրամանի պայմանում _կեղծ_ (_false_) արժեքը դատարկ վեկտորն է՝ `[]`։


## Ներդրված ֆունկցիաներ

* `input()` և `print(v)` -- ներմուծման ու արտածման համար,
* `vector(e, n)` -- ստեղծում է `n` հատ `e`-երով արժեքավորված նոր վեկտոր,
* `iota(b, n)` -- ստեղծում է `b`, `b+1`, `b+2`, `...`, `n` հաջորդական տարրերով վեկտոր,
* `slice(v, a, b)` -- նոր վեկտոր, որի տարրերը `v`-ի `a`-ից `b` տարրերի պատճեններն են։


## Օրինակներ

### Վեկտորի ամենամեծ տարրը որոշելը

```
function max(v)
    let m = v[0];
    for each e in v do
        if e > m then
            let m = e
        end
    end;
    return m
end
```

### Էրատոսթենեսի մաղը

```
function prime_numbers(n)
    let nums = iota(1, n);
    for each d in iota(2, n/2) do
        for each e in nums do
            if e % d = [0] then
                let e = [0]
            end
        end
    end;
    
    let primes = [];
    for each e in nums do
        if e <> [0] then
            let primes = primes ++ e
        end
    end;
    return primes
end
```
