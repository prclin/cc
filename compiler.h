#ifndef COMPILER_H
#define COMPILER_H
#include <stdio.h>

//compiler state enum
enum {
    COMPILER_SUCCEED_WITH_OK,
    COMPILER_FAILED_WITH_ERRORS
};

/**
 * this struct represents the very compile process
 */
struct compile_process{
    // flags in regards to how this file should be compiled
    int flags;
    struct compile_process_input_file{
        FILE* fp;//file pointer
        const char* abs_path; //the absolute file path
    } iFile; //input file
    FILE* oFile;//output file
};

int compile_file(const char* in_filename, const char* out_filename,int flags);
struct compile_process* create_compile_process(const char* in_filename, const char* out_filename,int flags);
#endif