#include "token_spec.h"
#include "buff_manager.h"
#include "classifier.h"


extern unsigned int lexeme_start;
extern unsigned int lexeme_end;
extern char buffer[];


Token classify_lexeme(void){

    Token curr_token;

    while(whitespace()); // removes whitespaces if any

    if(identifier()){
        curr_token.token_type = IDENTIFIER;
    }

    else if(opr()){
        curr_token.token_type = OPERATOR;
    }

    else if(special_chars()){
        curr_token.token_type = SPECIAL_CHAR;
    }

    else if(integer_or_float()){
        // Change integer_or_float() function's return type to int,
        // 0 - no match, 1 - Int, 2 - float
        curr_token.token_type = L_INTEGER;
    }

    else if(char_or_string()){
        // Same as the above function
        curr_token.token_type = L_FLOAT;
    }
    else{
        curr_token.token_type = UNKNOWN;
    }


    // The current lexeme value is from lemexe_state - lexeme_end pos in buff
    for(unsigned int i = lexeme_start; i <= lexeme_end; i++){
        curr_token.lexme[i - lexeme_start] = buffer[i];
    }

    // Resetting for next lexeme
    lexeme_start = lexeme_end;

    // Once you have the lexeme value and the token type is Identifier, check if it is a
    // keyword and change the type
    if(keyword(curr_token.lexme)){
        curr_token.token_type = KEYWORD;
    }
    

    return curr_token;
}