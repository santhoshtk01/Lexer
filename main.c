#include <stdio.h>
#include "stack.h"


int main(void){

    // New stack creation
    Stack stack;
    stack.top = -1;

    // To Push
    push(&stack, 'A');

    // To check overflow
    for(unsigned int i = 100; i--;) push(&stack, 'A');

    // To Pop
    // printf("%c", pop(&stack));
    // pop(&stack); // Error

    return 0;
}