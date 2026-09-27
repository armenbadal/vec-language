#pragma once

#include <stddef.h>
#include <stdbool.h>

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
    OP_GE
} operation_t;

typedef struct _expression expression_t;

typedef struct _number {
    double value;
} number_t;

typedef struct _vector_literal {
    expression_t **items;
    size_t count;
} vector_literal_t;

typedef struct _variable {
    char *name;
} variable_t;

typedef struct _unary {
    expression_t *operand;
} unary_t;

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

typedef struct _index {
    expression_t *object;
    expression_t *position;
} index_t;

typedef struct _slice {
    expression_t *object;
    expression_t *begin;
    expression_t *end;
} slice_t;

typedef enum _expression_kind {
    EX_NUMBER,
    EX_VECTOR_LITERAL,
    EX_VARIABLE,
    EX_UNARY,
    EX_BINOP,
    EX_LENGTH,
    EX_APPLY,
    EX_INDEX,
    EX_SLICE
} expression_kind_t;

struct _expression {
    expression_kind_t kind;
    union {
        number_t number;
        vector_literal_t vector_literal;
        variable_t variable;
        unary_t unary;
        binary_t binop;
        length_t length;
        apply_t apply;
        index_t index;
        slice_t slice;
    };
};


typedef struct _statement statement_t;

typedef struct _block {
    statement_t **items;
    size_t count;
} block_t;

typedef enum _assignment_target_kind {
    TARGET_VARIABLE,
    TARGET_INDEX
} assignment_target_kind_t;

typedef struct _assignment_target {
    assignment_target_kind_t kind;
    char *name;
    expression_t *index;
} assignment_target_t;

typedef struct _assignment {
    assignment_target_t target;
    expression_t *value;
} assignment_t;

typedef struct _branching {
    expression_t *condition;
    block_t decision;
    bool has_alternative;
    block_t alternative;
} branching_t;

typedef struct _iteration {
    char *parameter;
    expression_t *collection;
    block_t body;
} iteration_t;

typedef struct _return {
    expression_t *value;
} return_t;

typedef struct _call {
    apply_t apply;
} call_t;

typedef enum _statement_kind {
    ST_ASSIGN,
    ST_BRANCH,
    ST_ITERATE,
    ST_RETURN,
    ST_CALL
} statement_kind_t;

struct _statement {
    statement_kind_t kind;
    union {
        assignment_t assign;
        branching_t branch;
        iteration_t iterate;
        return_t result;
        call_t call;
    };
};


typedef struct _function {
    char *name;
    char **parameters;
    size_t parameters_count;
    block_t body;
} function_t;

typedef struct _program {
    function_t **functions;
    size_t count;
} program_t;
