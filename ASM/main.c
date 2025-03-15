#include "asm.h"

int main() {
    struct Text text_input = {};
    struct FileInfo file_input = {.file_name = "../ASM_FUNC/factorial.txt"};
    struct AsmCodeCreate code_input = {.max_line_cmd = 0, .free_mark = 0, .text_info_asm = &text_input, .file_info_asm = &file_input};
    
    if (TextCtor (&code_input) != GOOD)
    {
        printf ("TextCtor failed, line = %d", __LINE__);
        return 1;
    }

    if (Compilation (&code_input) != GOOD)
    {
        printf ("Compilation failed, line = %d", __LINE__);
        return 1;
    }

    if (FileCodeCmd (&code_input) != GOOD)
    {
        printf ("FileCodeCmd failed, line = %d", __LINE__);
        return 1;
    }

    TextDtor (&code_input);

    return 0;
}