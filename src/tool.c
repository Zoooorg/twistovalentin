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
 * @file tool.c
 *
 * @brief 
 */

#include "tool.h"

void* allocateMemory(size_t size) {
    
    void* pointer = malloc(size);
    if (!pointer) {
        exit(EXIT_FAILURE);
    }

    return pointer;
}


void* callocMemory(size_t numberElements, size_t elementSize) {

    void* pointer = calloc(numberElements, elementSize);
    if (!pointer) {
        exit(EXIT_FAILURE);
    }
    
    return pointer;
}



