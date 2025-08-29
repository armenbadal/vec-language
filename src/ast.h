#ifndef AST_H
#define AST_H

typedef enum _operation {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_CONC,
    OP_PROD,
    OP_EQ,
    OP_NE,
    OP_LT,
    OP_LE,
    OP_GT,
    OP_GE,
    OP_ELEM,
    OP_LEN,
} operation_t;

typedef struct _expression expression_t;

typedef struct _binary {
    operation_t oper;
    expression_t *left;
    expression_t *right;
} binary_t;

typedef struct _length {
    expression_t *expr;
} length_t;

typedef struct _apply {
    char *callee;
    expression_t **arguments;
    size_t arguments_count;
} apply_t;

typedef struct _value {
    /* vector_t *vec; */
} value_t;

typedef struct _variable {
    char *name;
} variable_t;

typedef enum _expression_kind {
    EX_BINOP,
    EX_LENGTH,
    EX_APPLY,
    EX_VALUE,
    EX_VARIABLE
} expression_kind_t;

struct _expression {
    expression_kind_t kind;
    union {
        binary_t *binop;
        length_t *length;
        apply_t *apply;
        value_t *value;
        variable_t *variable;
    };
};


typedef struct _statement statement_t;

typedef struct _sequence {
    statement_t **items;
    size_t count;
} sequence_t;

typedef struct _assignment {
    char *name;
    expression_t *index;
    expression_t *value;
} assignment_t;

typedef struct _branching {
    expression_t *condition;
    statement_t *decision;
    statement_t *alternative;
} branching_t;

typedef struct _iteration {
    char *parameter; // variable_t
    expression_t *collection;
    statement_t *body;
} iteration_t;

typedef struct _return {
    expression_t *value;
} return_t;

typedef struct _call {
    apply_t *apply;
} call_t;

typedef enum _statement_kind {
    ST_SEQUENCE,
    ST_ASSIGN,
    ST_BRANCH,
    ST_ITERATE,
    ST_RETURN,
    ST_CALL
} statement_kind_t;

struct _statement {
    statement_kind_t kind;
    union {
        sequence_t *sequence;
        assignment_t *assign;
        branching_t *branch;
        iteration_t *iterate;
        return_t *result;
        call_t *call;
    };
};


typedef struct _function {
    char *name;
    char **parameters;
    size_t parameters_count;
    statement_t *body;
} function_t;

typedef struct _program {
    function_t **functions;
    size_t count;
} program_t;

#endif /* AST_H */
