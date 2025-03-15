#include "processing.h"

int strcmpr (const char* str1, const char* str2){
    assert(str1);
    assert(str2);

    int i = 0;
    while(tolower(str1[i]) == tolower(str2[i]) && (str1[i] != '\0' && str2[i++])){
        i++;
    }

    return tolower(str1[i]) - tolower(str2[i]);
}

int sizeFile (FILE* text, struct Text* text_info){
    assert(text);

    if(fseek(text, 0, SEEK_END) != 0){
        return ERROR_FSEEK;
    }

    text_info->size_of_buff = ftell(text);

    if(!(text_info->size_of_buff)){
        return ERROR_FTELL;
    }

    if(fseek(text, 0, SEEK_SET) != 0){
        return ERROR_FSEEK;
    }

    return GOOD;
}

int buffCharCreate (struct FileInfo* file_info, struct  Text* text_info){
    assert(file_info->file_name);

    FILE* text = fopen(file_info->file_name, "rb");
    if(!text){
        return ERROR_FILE_OPEN;
    }

    if(sizeFile(text, text_info) != GOOD){
        return ERROR_SIZE_FILE;
    }

    text_info->file_buff_c = (char*)calloc(text_info->size_of_buff+1, sizeof(char));
    if(!(text_info->file_buff_c)){
        fclose(text);
        return ERROR_MEM;
    }

    size_t num_simbols = fread(text_info->file_buff_c, sizeof(char), text_info->size_of_buff, text);
    if(num_simbols != text_info->size_of_buff){
        free(text_info->file_buff_c);
        text_info->file_buff_c = NULL;
        fclose (text);
        return ERROR_READING_FILE;
    }

    if(fclose(text) != 0){
        free(text_info->file_buff_c);
        text_info->file_buff_c = NULL;

        return ERROR_FILE_CLOSE;
    }

    return GOOD;
}

int buffDoubleCreate (struct FileInfo* file_info, struct  Text* text_info){
    assert(file_info->file_name);

    FILE* text = fopen (file_info->file_name, "rb");
    if (!text)
    {
        return ERROR_FILE_OPEN;
    }

    if (SizeFile (text, text_info) != GOOD)
    {
        return ERROR_SIZE_FILE;
    } 

    text_info->file_buff_d = (double*) calloc (text_info->size_of_buff+ 1, sizeof (double));
    if (!(text_info->file_buff_d))
    {
        fclose (text);
        return ERROR_MEM;
    }

    size_t count_simbols = fread (text_info->file_buff_d, sizeof (char), text_info->size_of_buff, text);
    if (count_simbols != text_info->size_of_buff)
    {
        free (text_info->file_buff_d);
        text_info->file_buff_d = NULL;

        fclose (text);
        return ERROR_READING_FILE;
    }

    if (fclose (text) != 0)
    {
        free (text_info->file_buff_d);
        text_info->file_buff_d = NULL;
        
        return ERROR_FILE_CLOSE;
    }

    return GOOD;
}