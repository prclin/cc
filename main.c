#include <stdio.h>
#include "compiler.h"
int main() {
    int res = compile_file("/path/to/input", "/path/to/output", 0);
    if (res==COMPILER_SUCCEED_WITH_OK){
        printf("everything are going fine!\n");
    } else if (res==COMPILER_FAILED_WITH_ERRORS){
        printf("compile process failed!\n");
    } else{
        printf("unknown error!\n");
    }

    return 0;
}
