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
 * @file map.c
 *
 * @brief 
 */

#include <stdio.h>
#include <stdlib.h>
#include "map.h"


Map initializeMap(int width, int height) {

    Map map = (Map)allocateMemory(sizeof(struct map));

    MAP(map) = (Position**)allocateMemory(width * sizeof(Position*));

    for (int x = 0; x < width; x++) {
        MAP(map)[x] = (Position*)callocMemory(height, sizeof(Position));
    }

    WIDTH(map) = width;
    HEIGHT(map) = height;

    return map;
}


void createPositionsInMap(Map map, PositionList list) {

    for (int y = 0; y < HEIGHT(map); y++) {
        for (int x = 0; x < WIDTH(map); x++) {

            char ground = fgetc(stdin);

            if (ground != OFF_TRACK) {
                Position position = createPosition(x, y, ground);
                MAP(map)[x][y] = position;
                if (ground == END) {
                    addPositonToList(list, position);
                }
            }
        }
    }
}


Position getPosition(Map map, int xCoordinate, int yCoordinate) {

    return MAP(map)[xCoordinate][yCoordinate];
}

Position nextPosition(Map map, int xCoordinate, int yCoordinate, int xSpeed, int ySpeed, int xAcceleration, int yAcceleration) {

    int newX = xCoordinate + xSpeed + xAcceleration;
    int newY = yCoordinate + ySpeed + yAcceleration;
    
    return getPosition(map, newX, newY);
}


int isAValidPosition(Position position) {

    return (position != NULL); 
}


int isSand(Position position) {

    return (GROUND_(position) == SAND); 
}


int areValidPositionsInTheRange(Map map, int range, int xCoordinate, int yCoordinate, int xOffset, int yOffset) {

    for (int i = 0; i < range; i++) {

        fprintf(stderr, "%d %d", xCoordinate, yCoordinate);

        Position position = getPosition(map, xCoordinate, yCoordinate);

        if (!isAValidPosition(position)) {
            return FALSE;
        }
        
        xCoordinate += xOffset;
        yCoordinate += yOffset;
    } 

    return TRUE;
}
