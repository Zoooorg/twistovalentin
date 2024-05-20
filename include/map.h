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
 * @file map.h
 *
 * @brief 
 */

#ifndef MAP_H
#define MAP_H

#include "list.h"

#define OFF_TRACK '.'
#define SAND '~'
#define END '='
#define MAP(_map) (_map->map)
#define WIDTH(map)(map->width)
#define HEIGHT(map) (map->height)


typedef struct map {   
    
    Position** map;
    int width;
    int height;         

} *Map;


Map initializeMap(int width, int height);


void createPositionsInMap(Map map, PositionList list);


Position getPosition(Map map, int xCoordinate, int yCoordinate);


Position nextPosition(Map map, int xCoordinate, int yCoordinate, int xSpeed, int ySpeed, int xAcceleration, int yAcceleration);


int isAValidPosition(Position position);


int isSand(Position position);


int areValidPositionsInTheRange(Map map, int range, int xCoordinate, int yCoordinate, int xOffset, int yOffset);


#endif  /* MAP_H */ 