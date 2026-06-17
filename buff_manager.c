#include "buff_manager.h"
#include <stdio.h>

unsigned int lexeme_start;
unsigned int lexeme_end;


// Test all the token specification
char buffer[] = "\"santhosh\"";


// Move the lexeme_end to next position
void advance(void){
    lexeme_end++;
}


// Return the current char pointed by the lexeme_end
char peek(void){
    return buffer[lexeme_end];
}