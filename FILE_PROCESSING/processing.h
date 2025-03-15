#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "../enum.h"

struct Text {
    char*   file_buff_c;
    double* file_buff_d;
    size_t  size_of_buff;
};

struct FileInfo{
    const char* file_name;
    size_t size_file;
};

int strcmpr (const char* str1, const char* str2);

int sizeFile (FILE* text, struct Text* text_info);

int buffCharCreate (struct FileInfo* file_info, struct  Text* text_info);

int buffDoubleCreate (struct FileInfo* file_info, struct  Text* text_info);

#endif // PROCESSING_H