#include <stdlib.h>
#include "compiler.h"
#include "utils/vector.h"

/**
 * for init lexing process
 * @param compileProcess
 * @param functions
 * @param private
 * @return
 */
struct lexing_process *create_lexing_process(struct compile_process *compileProcess,
                                             struct lexing_process_functions *functions,
                                             void *private) {
    struct lexing_process *lexingProcess = calloc(1, sizeof(struct lexing_process));
    lexingProcess->functions = functions;
    lexingProcess->token_vector = vector_create(sizeof(struct token));
    lexingProcess->compiler = compileProcess;
    lexingProcess->private = private;
    lexingProcess->position.line = 1;
    lexingProcess->position.column = 1;
    return lexingProcess;
}

/**
 * for free lexing_process
 * @param lexingProcess
 */
void free_lexing_process(struct lexing_process *lexingProcess) {
    vector_free(lexingProcess->token_vector);
    free(lexingProcess);
}

/**
 * get the private data of lexing process
 * @param lexingProcess
 * @return
 */
void *lexing_process_private(struct lexing_process *lexingProcess) {
    return lexingProcess->private;
}

/**
 * get the token vector of lexing process
 * @param lexingProcess
 * @return
 */
struct vector *lexing_process_tokens(struct lexing_process *lexingProcess) {
    return lexingProcess->token_vector;
}