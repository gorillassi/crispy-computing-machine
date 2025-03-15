#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "../FILE_PROCESSING/processing.h"
#include "../enum.h"

const size_t MARK_ARR_SIZE = 50;
const size_t VERSION_CPU   = 1;
const size_t SIGN          = 0xCAC;

struct Mark{
    char* name;
    double meaning;
};

struct AsmCodeCreate {
    double* cmd_array;
    size_t number_cmd;
    size_t max_line_cmd;

    struct Mark mark_array[MARK_ARR_SIZE];
    size_t free_mark;   ///??

    struct Text* text_info_asm;
    struct FileInfo* file_info_asm;

    size_t ip;
    size_t counter_string;
    size_t counter_symbol;

    char* cmd;   
};

int TextCtor (struct AsmCodeCreate* code_info);

int CompilationFirstPass (struct AsmCodeCreate* code_info);

void PutMark (char* cmd, int* ip, struct AsmCodeCreate* code_info);

int Compilation (struct AsmCodeCreate* code_info);

int CommandCmp (struct AsmCodeCreate* code_info);

int GetPushPopArgument (struct AsmCodeCreate* code_info);

int GetJmpArgument (struct AsmCodeCreate* code_info);

int RegistrArgument (struct AsmCodeCreate* code_info);

int FileCodeCmd (struct AsmCodeCreate* code_info);

void TextDtor (struct AsmCodeCreate* code_info);

#endif // ASM_H