#include "buff_manager.h"
#include <stdlib.h>

unsigned int lexeme_start;
unsigned int lexeme_end;

FILE *fptr;

char buffer1[BUFF_SIZE];
char buffer2[BUFF_SIZE];
char flag_buff2 = OFF;
char *buffer = buffer1;
size_t bytes_read;



// Move the lexeme_end to next position
void advance(void){
    lexeme_end++;

    if(lexeme_end == BUFF_SIZE){
        // end of the first buffer
        buffer = buffer2;
        refill_buffer();
    }
    else if(lexeme_end == (BUFF_SIZE * 2)){
        // end of the second buffer
        lexeme_end = 0;
        lexeme_start = 0;
        buffer = buffer1;
        refill_buffer();
    }
}


// Return the current char pointed by the lexeme_end
char peek(void){
    return buffer[lexeme_end % BUFF_SIZE];
}


// Function to open the file
void open_file(char *file_name){

    fptr = fopen(file_name, "r");

    if(fptr == NULL){
        printf("E: Unable to open file.\n");
        return;
    }

    // Initial Buffer fill
    refill_buffer();
}


// Function to refill the buffer
void refill_buffer(){
    bytes_read = fread(buffer, 1, BUFF_SIZE, fptr);
}