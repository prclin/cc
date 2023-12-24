#include "compiler.h"
#include <stdarg.h>
#include <stdlib.h>

//default function implementations
struct lexing_process_functions compiler_lexing_functions = {
        compile_process_next_char,
        compile_process_peek_char,
        compile_process_push_char
};

/**
 * print the error message to standard error output.
 * @param compileProcess
 * @param msg
 * @param ...
 */
void compile_error(struct compile_process *compiler, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);

    fprintf(stderr, "on line %i, column %i in file %s \n", compiler->position.line,
            compiler->position.column, compiler->iFile.abs_path);
    exit(-1);
}

/**
 * print the warning message to standard error output.
 * @param compileProcess
 * @param msg
 * @param ...
 */
void compile_warning(struct compile_process *compiler, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);

    fprintf(stderr, "on line %i, column %i in file %s \n", compiler->position.line,
            compiler->position.column, compiler->iFile.abs_path);
}

/**
 * this function compile the input file and output to the specified destination with the particular flags.
 * @param in_filename input filename
 * @param out_filename output filename
 * @param flags compile flag: it suggest how to compile the input file
 * @return
 */
compiler_state compile_file(const char *in_filename, const char *out_filename, int flags) {
    //create compile process
    struct compile_process *compileProcess = create_compile_process(in_filename, out_filename, flags);
    if (!compileProcess) {
        return COMPILER_FAILED_WITH_ERRORS;
    }

    //perform lexical analysis

    //create lexing process
    struct lexing_process *lexingProcess = create_lexing_process(compileProcess, &compiler_lexing_functions, NULL);
    if (!lexingProcess) return COMPILER_FAILED_WITH_ERRORS;
    if (lex(lexingProcess) != LEXICAL_ANALYSIS_OK) return COMPILER_FAILED_WITH_ERRORS;

    //perform parsing

    //perform code generation

    return COMPILER_SUCCEED_WITH_OK;
}