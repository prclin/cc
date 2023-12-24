#include "compiler.h"
#include "utils/vector.h"
#include "utils/buffer.h"
#include <string.h>
/**
 * this macro writes each digit of the number into the buffer.
 */
#define LEX_GET_CHAR_IF(buffer, c, expression) \
 for(c=peekChar();expression;c=peekChar()){    \
    buffer_write(buffer,c);                    \
    nextChar();                                 \
 }


static struct lexing_process *lp;
static struct token tmpToken;

struct token *read_next_token();

static char peekChar() {
    return lp->functions->peek_char(lp);
}

static void pushChar(char c) {
    lp->functions->push_char(lp, c);
}

static char nextChar() {
    return lp->functions->next_char(lp);
}

static struct position lex_file_position() {
    return lp->position;
}

struct token *create_token(struct token *_token) {
    memcpy(&tmpToken, _token, sizeof(struct token));
    tmpToken.position = lex_file_position();
    return &tmpToken;
}

/**
 * read the full number string from source file.
 * @return
 */
const char *read_number_string() {
    const char *number = NULL;
    struct buffer *sb = buffer_create();
    char c = peekChar();
    LEX_GET_CHAR_IF(sb, c, c >= '0' && c <= '9');
    buffer_write(sb, 0x00);
    return buffer_ptr(sb);
}

/**
 * read the exact number.
 * @return
 */
unsigned long long read_number() {
    const char *ns = read_number_string();
    return atoll(ns);
}

/**
 * get the last token, which had been read.
 * @return
 */
static struct token *lexer_last_token() {
    return vector_back_or_null(lp->token_vector);
}


/**
 * when read whitespace or \t, ignore it, and continue to read next token.
 * @return
 */
static struct token *handle_whitespace() {
    struct token *lastToken = lexer_last_token();
    if (lastToken) lastToken->whitespace = true;
    nextChar();
    return read_next_token();
}

struct token *create_number_token_for_value(unsigned long number) {
    return create_token(&(struct token) {.type= TOKEN_TYPE_NUMBER, .llNum =number});
}

/**
 * create a token of TOKEN_TYPE_NUMBER
 * @return
 */
struct token *create_number_token() {
    return create_number_token_for_value(read_number());
}

/**
 * this function is main logic of reading a token.
 * read the characters from file stream, then construct a token to return.
 * @return
 */
struct token *read_next_token() {
    struct token *token = NULL;
    char c = peekChar();
    switch (c) {
        CASE_NUMBER:
            token = create_number_token();
            break;
        case ' ':
        case '\t':
            // ignore whitespaces
            token = handle_whitespace();
            break;
        case EOF: //lexical analysis finished
            break;
        default: //unexpected token, our lexer does not support unicode
            compile_error(lp->compiler, "Unexpected token!\n");
            break;
    }
    return token;
}

lexing_state lex(struct lexing_process *lexingProcess) {
    lexingProcess->current_expression_count = 0;
    lexingProcess->parentheses_buffer = NULL;
    lexingProcess->position.filename = lexingProcess->compiler->iFile.abs_path;
    lp = lexingProcess;

    struct token *token = read_next_token();
    while (token) {
        vector_push(lexingProcess->token_vector, token);
        token = read_next_token();
    }
    return LEXICAL_ANALYSIS_OK;
}