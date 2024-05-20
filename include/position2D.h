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
 * @file position2D.h
 *
 * @brief 
 */

#ifndef POSITION2D_H
#define POSITION2D_H

#include "tool.h"

#define X_(position) (position->x)
#define Y_(position) (position->y)
#define GROUND_(position) (position->ground)


/**
 * Position on a map (integer coordinates) and type of the ground.
 */
typedef struct position2Dint{

    int x;
    int y;
    char ground;

} Position2Dint, *Position;


/**
 * Position with floating point coordinates.
 */
typedef struct position2Dfloat {

  float x;
  float y;

} Position2Dfloat;


Position createPosition(int x, int y, char ground);


#endif /* POSITION2D_H */ 
