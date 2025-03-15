#ifndef ENUM_H
#define ENUM_H

const double NULL_DOUBLE  = NAN;
const size_t NUM_DTOR_VAL = 0xACAB;

enum BIN_FILE_NUMBER_CELLS {
    SIGN_NUM_CELL    = 0,
    VER_CPU_NUM_CELL = 1,
    QUANT_COMMAND    = 2,
};

enum BITE_VAR {
    BITE_IMMEDIATE_CONST = 1 << 5,
    BITE_REG             = 1 << 6,
    BITE_MEM             = 1 << 7,
};

enum ERRORS {
    GOOD                            = 0,
    ERROR_MEM                       = 1,
    ERROR_READING_FILE              = 2,
    ERROR_FILE_OPEN                 = 3,
    ERROR_FILE_CLOSE                = 4,
    ERROR_FSEEK                     = 5,
    ERROR_FTELL                     = 6,
    ERROR_FPRINTF                   = 7,
    ERROR_FPUTS                     = 8,
    ERROR_BUFFER_CREATER            = 9,
    INCORRECT_COMMAND               = 10,
    ERROR_SIGNATURE                 = 11,
    ERROR_VERSION_CPU               = 12,
    ERROR_SIZE_FILE                 = 13,
    ERROR_CALLOC                    = 14,
    ERROR_REALLOC                   = 15,
    ERROR_MARK_FIND                 = 16,
    ERROR_SSCANF                    = 17,
    ERROR_COMMAND_CMP               = 18,
    ERROR_STACK_CTOR                = 19,
    ERROR_FWRITE                    = 20,
    ERROR_COMPILATION_FIRST_PASS    = 21,
    ERROR_SYNTAX_COMMAND            = 22,
};

#endif