#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils/debug.h"
#include "utils/argument.h"

bool debugFlag = false; // se setea en true sii se usa la opcion -debug

int main(int argc, char *argv[]) {
    Option option = getArgumentOption(argc, argv);
    
    switch (option) {
        case OPTION_O:      processOptionO(argc, argv);      break;
        case OPTION_TARGET: processOptionTarget(argc, argv); break;
        case OPTION_OPT:    processOptionOpt(argc, argv);    break;
        case OPTION_DEBUG:  processOptionDebug(argc, argv);  break;
    }

    return 0;
}
