#include "debug.h"

char * getMessageSourceString(MessageSource msgSrc) {
    switch (msgSrc) {
        case MESSAGE_SOURCE_GLOBAL:                   return "GLOBAL";
        case MESSAGE_SOURCE_ARGUMENT:                 return "ARGUMENT";
        case MESSAGE_SOURCE_LEXICAL_ANALYSIS:         return "LEXICAL_ANALYSIS";
        case MESSAGE_SOURCE_SINTAX_ANALYSIS:          return "SINTAX_ANALYSIS";
        case MESSAGE_SOURCE_SEMANTIC_ANALYSIS:        return "SEMANTIC_ANALYSIS";
        case MESSAGE_SOURCE_IR_GENERATION:            return "IR_GENERATION";
        case MESSAGE_SOURCE_ASSEMBLY_GENERATION:      return "ASSEMBLY_GENERATION";
        case MESSAGE_SOURCE_AST:                      return "AST";
        case MESSAGE_SOURCE_SYMBOL_TABLE:             return "SYMBOL_TABLE";
        case MESSAGE_SOURCE_DOT:                      return "DOT";
        case MESSAGE_SOURCE_OPT_CONSTANT_PROPAGATION: return "OPT_CONSTANT_PROPAGATION";
        case MESSAGE_SOURCE_OPT_DEAD_CODE:            return "OPT_DEAD_CODE";
        default:                                      return "";
    }
}

