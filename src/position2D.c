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
 * @file position2D.c
 *
 * @brief 
 */

#include <stdio.h>
#include <stdlib.h>
#include "position2D.h"


Position createPosition(int x, int y, char ground) {

    Position position = (Position)allocateMemory(sizeof(Position2Dint));

    X_(position) = x;
    Y_(position) = y;
    GROUND_(position) = ground;

    return position;
}
