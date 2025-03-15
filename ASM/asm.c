#include "asm.h"

int TextCtor(struct AsmCodeCreate* code_info){
    assert (code_info->text_info_asm);
    assert (code_info->file_info_asm);
    assert (code_info->file_info_asm->file_name);

    if (BufferCharCreater (code_info->file_info_asm, code_info->text_info_asm))
    {
        return ERROR_BUFFER_CREATER;
    }

    return GOOD;
}

int CompilationFirstPass (struct AsmCodeCreate* code_info){
    assert (code_info);
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buff_c);

    int length_cmd = 0;
    int counter = 0;
    int ip = 0;

    char* buffer = code_info->text_info_asm->file_buff_c;

    char* cmd = (char*) calloc (code_info->text_info_asm->size_of_buff, sizeof(char));
    if(cmd == NULL){
        return ERROR_CALLOC;
    }

    while (counter < code_info->text_info_asm->size_of_buff)
    {
        sscanf (buffer + counter, "%s %n", cmd, &length_cmd);

        char* find_colon_in_cmd = strchr (cmd, ':');

        if (find_colon_in_cmd != NULL)
        {
            if (find_colon_in_cmd - cmd == strlen (cmd) - 1)
            {
                code_info->mark_array[code_info->free_mark].meaning = ip; 
                code_info->mark_array[code_info->free_mark].name = strdup (cmd);

                code_info->mark_array[code_info->free_mark].name[strlen(code_info->mark_array[code_info->free_mark].name) - 1] = '\0';
                code_info->free_mark++;

                ip--; //(*ip)--??
            }
        }
        
        if(length_cmd > code_info->max_line_cmd){
            code_info->max_line_cmd= length_cmd;
        }

        counter += length_cmd;

        if (strchr(cmd, '+') != NULL & strchr (cmd, '+') != cmd)
        {
            ip++;
        }

        if ((*cmd != ']') && (*cmd != '[') != 0 && (*cmd != '+')) // сравнение симвлов
        {
            ip++;
        }
    }

    code_info->number_cmd = ip + 3;

    free(cmd);

    return GOOD;
}

void PutMark (char* cmd, int* ip, struct AsmCodeCreate* code_info){
    char* find_colon_in_cmd = strchr (cmd, ':');

    if (find_colon_in_cmd != NULL); ///????

    if(find_colon_in_cmd - cmd == strlen(cmd) - 1){

        code_info->mark_array[code_info->free_mark].meaning = *ip; 
        code_info->mark_array[code_info->free_mark].name = strdup (cmd);

        code_info->mark_array[code_info->free_mark].name[strlen(code_info->mark_array[code_info->free_mark].name) - 1] = '\0';
        code_info->free_mark++;

        (*ip)--;
    }
}

int Compilation (struct AsmCodeCreate* code_info){
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buff_c);

    char* buffer = code_info->text_info_asm->file_buff_c;

    if (CompilationFirstPass (code_info) != GOOD)
    {
        return ERROR_COMPILATION_FIRST_PASS;
    }

    code_info->cmd_array = (double*) calloc (code_info->number_cmd, sizeof (double));
    if (code_info->cmd_array == NULL)
    {
        return ERROR_CALLOC;
    }

    code_info->cmd_array[0] = SIGN; 
    code_info->cmd_array[1] = VERSION_CPU;
    code_info->cmd_array[2] = code_info->number_cmd;

    code_info->ip = 3, code_info->counter_string = 0, code_info->counter_symbol = 0;

    code_info->cmd = (char*) calloc (code_info->max_line_cmd, sizeof(char));
    if (code_info->cmd == NULL)
    {
        return ERROR_CALLOC;
    }

    int length_cmd = 0;

    while (code_info->counter_symbol < code_info->text_info_asm->size_of_buff)
    {
        sscanf (buffer + code_info->counter_symbol, "%s %n", code_info->cmd, &length_cmd);

        code_info->counter_symbol += length_cmd;

        if (CommandCmp (code_info) != GOOD)
        {
            return ERROR_COMMAND_CMP;
        }
    }

    if (code_info->cmd)
    {
        free (code_info->cmd);
        code_info->cmd = NULL;
    }

    return GOOD;
}

int CommandCmp (struct AsmCodeCreate* code_info){
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buff_c);
    assert (code_info->cmd_array);

    #define DEF_COMMAND(name_cmd, code_cmd, there_is_argument, ...)     if (stricmp (code_info->cmd, #name_cmd) == 0)                               \
                                                                        {                                                                               \
                                                                            code_info->cmd_array[(code_info->ip)++] = code_cmd;                         \
                                                                            if (there_is_argument == 1)                                                 \
                                                                            {                                                                           \
                                                                                GetPushPopArgument (code_info);                                         \
                                                                            }                                                                           \
                                                                            else if (there_is_argument == 2)                                            \
                                                                            {                                                                           \
                                                                                GetJmpArgument (code_info);                                             \
                                                                            }                                                                           \
                                                                        }                                                                               \
                                                                        else 

    #define DEF_REG(name_cmd, code_cmd) /////???^^^

    #include "../command.h"

    #undef DEF_COMMAND
    #undef DEF_REG

    if (!(strchr(code_info->cmd, ':') != NULL && 
         (strchr(code_info->cmd, ':') - code_info->cmd == strlen (code_info->cmd) - 1))){
        
            return INCORRECT_COMMAND;
    }

    return GOOD;
}

int GetPushPopArgument (struct AsmCodeCreate* code_info){
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buff_c);
    assert (code_info->cmd_array);

    int length_cmd = 0;

    char* buffer = code_info->text_info_asm->file_buff_c;
        
    if (*(buffer + code_info->counter_symbol) == '[')
    {
        code_info->cmd_array[code_info->ip - 1] += BITE_MEM;
        code_info->counter_symbol++;
    }

    if (sscanf(buffer + code_info->counter_symbol, "%lf %n", &code_info->cmd_array[code_info->ip], &length_cmd) != 0)
    {
        code_info->cmd_array[code_info->ip - 1] += BITE_IMMEDIATE_CONST;

        if (*(buffer + code_info->counter_symbol + length_cmd) == '+')
        {
            code_info->counter_symbol += length_cmd + 1;
            code_info->cmd_array[code_info->ip - 1] += BITE_REG;
            code_info->ip++;
    
            return RegistrArgument (code_info);
        }

        code_info->ip++;
    }
    else if (sscanf(buffer + code_info->counter_symbol, "%lf %n", &code_info->cmd_array[code_info->ip], &length_cmd) == 0)
    {
        code_info->cmd_array[code_info->ip - 1] += BITE_REG;

        return RegistrArgument (code_info);
    }
        
    code_info->counter_symbol += length_cmd;

    if (*(buffer + code_info->counter_symbol) == ']')
    {
        code_info->counter_symbol++;
    }

    return GOOD;
}

int RegistrArgument (struct AsmCodeCreate* code_info){
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buff_c);
    assert (code_info->cmd_array);

    int length_cmd = 0;

    char* buffer = code_info->text_info_asm->file_buff_c;

    if (sscanf(buffer + code_info->counter_symbol, "%s %n", code_info->cmd, &length_cmd) != 1)
    {
        return ERROR_SSCANF;
    }

    char* find_square_bracket = strchr (code_info->cmd, ']');
    if (find_square_bracket != NULL)
    {
        *find_square_bracket = '\0';
    }

    #define DEF_REG(name_cmd, code_cmd)     if (stricmp (code_info->cmd, #name_cmd) == 0)                       \
                                            {                                                                   \
                                                code_info->cmd_array[code_info->ip++] = code_cmd;               \
                                            }                                                                   \
                                            else 

    #define DEF_COMMAND(name_cmd, code_cmd, there_is_argument, ...)

    #include "../command.h"
    
    #undef DEF_COMMAND
    #undef DEF_REG
    // /* else */  ?????????????????
    // {   
    //     return INCORRECT_COMMAND;
    // }

    code_info->counter_symbol += length_cmd;
    if (find_square_bracket == NULL)
    {
        sscanf(buffer + code_info->counter_symbol, "%s %n", code_info->cmd, &length_cmd);
        find_square_bracket = strchr (code_info->cmd, ']');

        if (find_square_bracket != NULL)
        {
            code_info->counter_symbol += length_cmd;
        }
    }

    return GOOD;
}

int GetJmpArgument (struct AsmCodeCreate* code_info){
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buff_c);
    assert (code_info->cmd_array);

    int length_cmd = 0;

    char* buffer = code_info->text_info_asm->file_buff_c;

    if (sscanf(buffer + code_info->counter_symbol, "%lf %n", &code_info->cmd_array[code_info->ip], &length_cmd) != 0)
    {
        code_info->ip++;
    }
    else
    {
        sscanf(buffer + code_info->counter_symbol, "%s %n", code_info->cmd, &length_cmd);

        for (int j = 0; j < code_info->free_mark; j++)
        {   
            if (stricmp (code_info->cmd + 1, code_info->mark_array[j].name) == 0)
            {
                code_info->cmd_array[code_info->ip] = code_info->mark_array[j].meaning;
                code_info->ip++;

                break;
            }
        }
    }

    code_info->counter_symbol += length_cmd;
    
    return GOOD;
}

int FileCodeCmd (struct AsmCodeCreate* code_info){
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buff_c);
    assert (code_info->cmd_array);

    FILE* code_cmd_file = fopen ("code_command.bin", "wb");
    if (code_cmd_file == NULL)
    {
       return ERROR_FILE_OPEN;
    }

    if (fwrite (code_info->cmd_array, sizeof(double), code_info->number_cmd + 3, code_cmd_file) != code_info->number_cmd + 3)
    {
        return ERROR_FWRITE;
    }

    if (fclose (code_cmd_file))
    {
        return ERROR_FILE_CLOSE;
    }

    return GOOD;
}

void TextDtor (struct AsmCodeCreate* code_info){
    char* buffer = code_info->text_info_asm->file_buff_c;

    if (code_info->cmd_array)
    {
        free (code_info->cmd_array);
        code_info->cmd_array = NULL;
    }

    for (int i = 0; i < MARK_ARR_SIZE; i++)
    {
        code_info->mark_array[i].name = NULL;
        code_info->mark_array[i].meaning = NAN;
    }

    if (buffer)
    {
        free(buffer);
        buffer = NULL;
    }

    code_info->text_info_asm->size_of_buff = NUM_DTOR_VAL;
    code_info->number_cmd                  = NUM_DTOR_VAL;
    code_info->max_line_cmd                = NUM_DTOR_VAL;
    code_info->free_mark                   = NUM_DTOR_VAL;
    code_info->ip                          = NUM_DTOR_VAL;
    code_info->counter_string              = NUM_DTOR_VAL;
    code_info->counter_symbol              = NUM_DTOR_VAL;
    code_info->cmd                         = NULL;
}