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
    OP_LE,
    OP_LEN
} operation_t;

typedef struct _expression expression_t;

typedef enum _expression_kind {
    EX_BINOP,
    EX_LENGTH,
    EX_APPLY,
    EX_INDEX,
    EX_SLICE
} expression_kind_t;

typedef struct _binary {
    operation_t oper;
    expression_t *left;
    expression_t *right;
} binary_t;

typedef struct _length {
} length_t;

typedef struct _apply {
} apply_t;

typedef struct _index {
} index_t;

typedef struct _slice {
} slice_t;

struct _expression {
    /* kind */
    union {
        binary_t *binop;
        length_t *length;
        apply_t *apply;
        index_t *index;
        slice_t *slice;
    };
};


typedef struct _statement statement_t;

typedef struct _assignment {
} assignment_t;

typedef struct _branching {
} branching_t;

typedef struct _iteration {
} iteration_t;

typedef struct _return {
} return_t;

typedef struct _call {
} call_t;

struct _statement {
    /* kind */
    union {
        assignment_t *assign;
        branching_t *branch;
        iteration_t *iterate;
        return_t *ret;
        call_t *cal;
    };
};


typedef struct _function {
} function_t;

typedef struct _program {
    function_t **functions;
    size_t count;
} program__t;

#endif /* AST_H */
