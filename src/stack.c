/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/**
 * @author SALIC valentin <valentin.salic@ecole.ensicaen.fr>
 * @author Auteur2 <mail@ecole.ensicaen.fr>
 * @author Auteur3 <mail@ecole.ensicaen.fr>
 *
 * @version 0.0.1 
 */

/**
 * @file stack.c
 *
 * @brief 
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


/**
 * @brief Creates a new stack with no elements.
 *
 * @return A pointer to the new stack.
 */
Stack* createStack() {

    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (!s) {
		exit(EXIT_FAILURE);
	}

    *s = newPositionList();

    return s;
}


/**
 * @brief Pushes an element onto the top of the stack.
 *
 * @param stack The stack to push onto.
 * @param data The data to push onto the stack.
 */
void push(Stack* stack, Position position) {

    PositionCell* cell = (PositionCell*)allocateMemory(sizeof(PositionCell));

	CURRENT_POSITION_OF(cell) = position;
    NEXT_POSITION_CELL_OF(cell) = *stack;

    *stack = cell;
}
  

/**
 * @brief Pops an element from the top of the stack.
 *
 * @param stack The stack to pop from.
 *
 * @return The data from the top element of the stack.
 */
Position pop(Stack* stack) {

    if (isStackEmpty(*stack)) {
        exit(EXIT_FAILURE);
    }

    Position position = CURRENT_POSITION_OF((*stack));
    PositionCell* temporaryCell = NEXT_POSITION_CELL_OF((*stack));

    free(*stack);
    *stack = temporaryCell;

    return position;
}



/**
 * @brief Peeks at the top element of the stack without removing it.
 *
 * @param stack The stack to peek at.
 *
 * @return The data from the top element of the stack.
 */
Position peek(Stack stack) {

    if (isStackEmpty(stack)) {
        exit(EXIT_FAILURE);
    }
    
    return CURRENT_POSITION_OF(stack);
}


/**
 * @brief Checks whether the stack is empty.
 *
 * @param stack The stack to check.
 *
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isStackEmpty(Stack stack) {

    return (stack == NULL);
}

