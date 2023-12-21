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
struct compile_process* create_compile_process(const char* in_filename, const char* out_filename,int flags){
    //open input file as read only mode
    FILE* in_file= fopen(in_filename,"r");

    //if input file is not exist or can not open return null;
    if(!in_file) return NULL;

    FILE* out_file= NULL;
    //if out filename is not null open it as write only mode
    if (out_filename){
        out_file=fopen(out_filename,"w");
        if(!out_file) return NULL;
    }
    struct compile_process* process= calloc(1,sizeof (struct compile_process));
    process->flags=flags;
    process->iFile.fp=in_file;
    process->oFile=out_file;
    return process;
}