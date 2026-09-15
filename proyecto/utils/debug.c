#include "debug.h"

char * getMessageSourceString(MessageSource msgSrc) {
    switch (msgSrc) {
        case MESSAGE_SOURCE_GLOBAL:              return "GLOBAL";              break;
        case MESSAGE_SOURCE_ARGUMENT:            return "ARGUMENT";            break;
        case MESSAGE_SOURCE_LEXICAL_ANALYSIS:    return "LEXICAL_ANALYSIS";    break;
        case MESSAGE_SOURCE_SINTAX_ANALYSIS:     return "SINTAX_ANALYSIS";     break;
        case MESSAGE_SOURCE_SEMANTIC_ANALYSIS:   return "SEMANTIC_ANALYSIS";   break;
        case MESSAGE_SOURCE_IR_GENERATION:       return "IR_GENERATION";       break;
        case MESSAGE_SOURCE_ASSEMBLY_GENERATION: return "ASSEMBLY_GENERATION"; break;
        case MESSAGE_SOURCE_AST:                 return "AST";                 break;
        case MESSAGE_SOURCE_SYMBOL_TABLE:        return "SYMBOL_TABLE";        break;
        default:                                 return "";                    break;
    }
}

