#include <ctype.h> // for isspace(c) function. The function provides a more comprehensive whitespace test than the previous implemention.
#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "location.h"
#include "inventory.h"
#include "openclose.h"

// struct combines a pattern with a function
typedef struct {
    const char *pattern;
    bool (*function)(void);
} COMMAND;

static bool executeQuit(void) {
    return false;
}

static bool executeNoMatch(void) {
    const char * src = * params;
    int len;
    // this for calculates the length of the first word entered by the player, which we assume is supposed to be the unrecognized verb
    for (len = 0; src[len] != '\0' && !isspace(src[len]); len++);
    //we use a special format specifier %.*s to print only the first len characters of src. 
    if (len > 0) printf("I don't know how to '%.*s'\n", len, src);
    return true;
}

bool parseAndExecute(const char *input) {

    // This is the array of patterns
    static const COMMAND commands[] = {
        { "quit"        ,   executeQuit         },
        { "look"        ,   executeLookAround   },
        { "look around" ,   executeLookAround   },
        { "look at A"   ,   executeLook         },
        { "look A"      ,   executeLook         },
        { "examine A"   ,   executeLook         },
        { "go to A"     ,   executeGo           },
        { "go A"        ,   executeGo           },
        { "get A"       ,   executeGet          },
        { "drop A"      ,   executeDrop         },
        { "ask A"       ,   executeAsk          },
        { "give A"      ,   executeGive         },
        { "inventory"   ,   executeInventory    },
        { "open A"      ,   executeOpen         },
        { "close A"     ,   executeClose        },
        { "lock A"      ,   executeLock         },
        { "unlock A"    ,   executeUnlock       },
        { "A"           ,   executeNoMatch      },
    };
    const COMMAND *cmd;
    // This loop scans through all the patterns until a match is found, with the "A" assuring the loop will never go out of the array
    for (cmd = commands; !matchCommand(input, cmd->pattern); cmd++);
    // the function that is mapped to the pattern is called
    return (*cmd->function)();
}