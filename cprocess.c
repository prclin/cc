#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * this function create the exactly compiler process
 * when open input or output file fail, it will return null.
 * @param in_filename input filename
 * @param out_filename output filename
 * @param flags compile mode flags
 * @return compile_process pointer
 */
struct compile_process *create_compile_process(const char *in_filename, const char *out_filename, int flags) {
    //open input file as read only mode
    FILE *in_file = fopen(in_filename, "r");

    //if input file is not exist or can not open return null;
    if (!in_file) return NULL;

    FILE *out_file = NULL;
    //if out filename is not null open it as write only mode
    if (out_filename) {
        out_file = fopen(out_filename, "w");
        if (!out_file) return NULL;
    }
    struct compile_process *process = calloc(1, sizeof(struct compile_process));
    process->flags = flags;
    process->iFile.fp = in_file;
    process->oFile = out_file;
    return process;
}

/**
 * get the next char from source file
 * @param lexingProcess
 * @return
 */
char compile_process_next_char(struct lexing_process *lexingProcess) {
    struct compile_process *compiler = lexingProcess->compiler;
    compiler->position.column += 1;
    //read a character from source file
    char next_char = getc(compiler->iFile.fp);

    // catch new line reset position
    if (next_char == '\n') {
        compiler->position.line += 1;
        compiler->position.column = 1;
    }

    return next_char;
}

/**
 * get the next char from source file without move the pointer
 * @param lexingProcess
 * @return
 */
char compile_process_peek_char(struct lexing_process *lexingProcess) {
    struct compile_process *compiler = lexingProcess->compiler;
    //read a character from source file
    char next_char = getc(compiler->iFile.fp);
    //return the character back
    ungetc(next_char, compiler->iFile.fp);
    return next_char;
}

/**
 * push the character to file stream
 * @param lexingProcess
 * @param character
 */
void compile_process_push_char(struct lexing_process *lexingProcess, char character) {
    struct compile_process *compiler = lexingProcess->compiler;
    //push the character to file stream
    ungetc(character, compiler->iFile.fp);
}