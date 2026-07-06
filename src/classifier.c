#include "token_spec.h"
#include "buff_manager.h"
#include "classifier.h"


extern unsigned int lexeme_start;
extern unsigned int lexeme_end;

extern char *buffer;
extern char buffer1[];
extern char buffer2[];
extern char flag_buff2;
extern size_t bytes_read;


Token classify_lexeme(void){

    Token curr_token;
    int temp;

    // Check if NULL or EOF reached
    if(buffer[lexeme_end % BUFF_SIZE] == '\0' || buffer[lexeme_end % BUFF_SIZE] == EOF){
        curr_token.token_type = END_OF_FILE;
        curr_token.lexme[0] = '\0';

        return curr_token;
    }
 
    // Edge case: When we find a whitespace, we do need to move the
    // lexme_start as well
    while(whitespace());

    if(identifier()){
        curr_token.token_type = IDENTIFIER;
    }

    else if(opr()){
        curr_token.token_type = OPERATOR;
    }

    else if(special_chars()){
        curr_token.token_type = SPECIAL_CHAR;
    }

    else if(temp = integer_or_float()){
        // Change integer_or_float() function's return type to int,
        // 0 - no match, 1 - Int, 2 - float
        if(temp == 1) curr_token.token_type = L_INTEGER;
        else curr_token.token_type = L_FLOAT;
    }

    else if(temp = char_or_string()){
        if(temp == 1) curr_token.token_type = L_CHAR;
        else curr_token.token_type = L_STRING;
    }
    else if(preprocessor()){
        curr_token.token_type = PREPROCESSOR;
    }
    else{
        curr_token.token_type = UNKNOWN;
    }


    /* 
    There are three possible cases:
        1. lexeme in buffer1
        2. lexeme in buffer2
        3. lexeme in buffer1 and buffer2
        4. lexeme in buffer2 and buffer1
    */

    unsigned int lexeme_index = 0; // to track the pos in strcut lexeme member

    if(lexeme_start < BUFF_SIZE && lexeme_end < BUFF_SIZE){
        // Case 1
        for(unsigned int i = lexeme_start; i < lexeme_end; i++){
            curr_token.lexme[lexeme_index++] = buffer1[i];
        }
        curr_token.lexme[lexeme_index] = '\0';
    }
    else if(lexeme_start < BUFF_SIZE && lexeme_end > BUFF_SIZE){
        // Case 3
        // Fill from buff1
        for(unsigned int i = lexeme_start; i < BUFF_SIZE; i++){
            curr_token.lexme[lexeme_index++] = buffer1[i];
        }

        // Fill from buff2
        for(unsigned int i = 0; i < lexeme_end % BUFF_SIZE; i++){
            curr_token.lexme[lexeme_index++] = buffer2[i];
        }

        curr_token.lexme[lexeme_index] = '\0';
    }
    else if(lexeme_start > BUFF_SIZE && lexeme_end > BUFF_SIZE){
        // Case 2
        for(unsigned int i = lexeme_start; i < lexeme_end; i++){
            curr_token.lexme[lexeme_index++] = buffer2[i % BUFF_SIZE];
        }
        curr_token.lexme[lexeme_index] = '\0';
    }
    else{
        // Case 4
        // Fill from buff2
        for(unsigned int i = lexeme_start; i < BUFF_SIZE; i++){
            curr_token.lexme[lexeme_index++] = buffer2[i % BUFF_SIZE];
        }

        // Fill from buff1
        for(unsigned int i = 0; i < lexeme_end % BUFF_SIZE; i++){
            curr_token.lexme[lexeme_index++] = buffer1[i];
        }

        curr_token.lexme[lexeme_index] = '\0';
    }
    
    // Resetting for next lexeme
    lexeme_start = lexeme_end;

    // Once you have the lexeme value and the token type is Identifier, check if it is a
    // keyword and change the type
    if(keyword(curr_token.lexme)){
        curr_token.token_type = KEYWORD;
    }
    
    if(lexeme_end % BUFF_SIZE >= bytes_read){
        curr_token.token_type = END_OF_FILE;
        curr_token.lexme[0] = '\0';
    }


    return curr_token;
}