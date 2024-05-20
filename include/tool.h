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
 * @file tool.h
 *
 * @brief 
 */

#ifndef TOOL_H
#define TOOL_H

#include <stdlib.h>

#define TRUE 1
#define FALSE 0


void* allocateMemory(size_t size);


void* callocMemory(size_t numberElements, size_t elementSize); 


#endif  /* TOOL_H */ 

