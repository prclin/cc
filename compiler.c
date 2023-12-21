#include "compiler.h"
/**
 * this function compile the input file and output to the specified destination with the particular flags.
 * @param in_filename input filename
 * @param out_filename output filename
 * @param flags compile flag: it suggest how to compile the input file
 * @return
 */
int compile_file(const char* in_filename, const char* out_filename,int flags){
    struct compile_process* process= create_compile_process(in_filename,out_filename,flags);
    if (!process){
        return COMPILER_FAILED_WITH_ERRORS;
    }

    //perform lexical analysis

    //perform parsing

    //perform code generation

    return COMPILER_SUCCEED_WITH_OK;
}