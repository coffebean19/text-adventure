#include <stdio.h>
#include <stdbool.h>
#include "parsexec.h"

static char input[100] = "look around";

static bool getInput(void)
{
    printf("\n--> ");
    return fgets(input, sizeof input, stdin) != NULL;
}

int main() 
{
    printf("Welcome to Little Cave Adventure.\n");
    while (parseAndExecute(input) && getInput());
    printf("\nBye!\n");

    return 0;
}
