#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdbool.h>

struct compile_process;
struct position;
struct token;
struct lexing_process;
struct lexing_process_functions;

/**
 * position represents the position of the token in the source file
 */
struct position {
    int line;
    int column;
    const char *filename;
};

#define CASE_NUMBER \
    case '0':         \
    case '1':         \
    case '2':         \
    case '3':         \
    case '4':         \
    case '5':         \
    case '6':         \
    case '7':         \
    case '8':         \
    case '9'

typedef enum {
    LEXICAL_ANALYSIS_OK,
    LEXICAL_ANALYSIS_INPUT_ERROR,
} lexing_state;

/**
 * token type enumeration
 */
typedef enum {
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE,
} token_type;

/**
 * token represents lexical units in Lexical analysis phase.
 */
struct token {
    token_type type;
    int flags;
    struct position position;
    //this union represents the value of different token type
    union {
        char cVal; //char
        const char *sVal; // string
        unsigned int iNum; // int
        unsigned long lNum; // long
        unsigned long long llNum; // long long
        void *any; // any pointer
    };

    // True if there is a whitespace between this and the next token
    bool whitespace;

    // this variable is for test
    // if this token is in brackets, this pointer pointing to the beginning of the expression
    // eg: (10+2+3), between_brackets -> (
    const char *between_brackets;
};

//compiler state enum
typedef enum {
    COMPILER_SUCCEED_WITH_OK,
    COMPILER_FAILED_WITH_ERRORS
} compiler_state;

/**
 * this struct represents the very compile process
 */
struct compile_process {
    // flags in regards to how this file should be compiled
    int flags;
    struct position position;
    struct compile_process_input_file {
        FILE *fp;//file pointer
        const char *abs_path; //the absolute file path
    } iFile; //input file
    FILE *oFile;//output file
};

// following function pointers definition provide operations of character for lexer.

typedef char (*LEXING_PROCESS_NEXT_CHAR)(struct lexing_process *lexingProcess);

typedef char (*LEXING_PROCESS_PEEK_CHAR)(struct lexing_process *lexingProcess);

typedef void (*LEXING_PROCESS_PUSH_CHAR)(struct lexing_process *lexingProcess, char character);

struct lexing_process_functions {
    LEXING_PROCESS_NEXT_CHAR next_char;
    LEXING_PROCESS_PEEK_CHAR peek_char;
    LEXING_PROCESS_PUSH_CHAR push_char;
};

/**
 * the lexical analysis process struct
 */
struct lexing_process {
    struct position position;
    struct vector *token_vector;
    struct compile_process *compiler;

    // eg: ((50)) , this will be to same as the bracket counts
    int current_expression_count;
    struct buffer *parentheses_buffer;
    struct lexing_process_functions *functions;

    // the private data lexer does not understand but the user does.
    void *private;
};

compiler_state compile_file(const char *in_filename, const char *out_filename, int flags);

struct compile_process *create_compile_process(const char *in_filename, const char *out_filename, int flags);

char compile_process_next_char(struct lexing_process *lexingProcess);

char compile_process_peek_char(struct lexing_process *lexingProcess);

void compile_process_push_char(struct lexing_process *lexingProcess, char character);

struct lexing_process *create_lexing_process(struct compile_process *compileProcess,
                                             struct lexing_process_functions *functions,
                                             void *private);

void free_lexing_process(struct lexing_process *lexingProcess);

void *lexing_process_private(struct lexing_process *lexingProcess);

struct vector *lexing_process_tokens(struct lexing_process *lexingProcess);

lexing_state lex(struct lexing_process *lexingProcess);

void compile_error(struct compile_process *compileProcess, const char *msg, ...);

void compile_warning(struct compile_process *compileProcess, const char *msg, ...);

#endif