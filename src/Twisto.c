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
 * @file twisto.h
 *
 * @brief 
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver.h"

int main() {

    int width, height;
    int gasLevel;
    int boosts = BOOSTS_AT_START;
    int accelerationX = 0, accelerationY = 0;
    int speedX = 0, speedY = 0;
    char line_buffer[MAX_LINE_LENGTH];
    Direction direction = NO_DIRECTION;
    Stack* positionPath = createStack();

    boosts = boosts;                       
    fgets(line_buffer, MAX_LINE_LENGTH, stdin);      
    sscanf(line_buffer, "%d %d %d", &width, &height, &gasLevel);

    Track track = initializeTrack(width, height);

    createPositionsInMap(MAP_OF(track), END_POSITIONS_OF(track));
    

    while (!feof(stdin)) {
        
        int myX, myY, secondX, secondY, thirdX, thirdY;
        getPilotPosition(&myX, &myY, &secondX, &secondY, &thirdX, &thirdY);

        fprintf(stderr, "%d %d" , myX, myY);
        
        if (direction == NO_DIRECTION) {
            direction = getDirection(MAP(track), myX, myY); 
            int length = isAStraightLine(MAP(track), direction, myX, myY, speedX, speedY);
            Position start = getPosition(MAP(track), myX, myY);
            positionPath = generatePath(MAP(track), direction, start, speedX, speedY, accelerationX, accelerationY,length, gasLevel, 0);
        }

        Position current = getPosition(MAP(track), myX, myY);

        Position next = pop(positionPath);

        calculateAcceleration(current, next, &speedX, &speedY, &accelerationX, &accelerationY);
        accelerate(accelerationX, accelerationY);
    
    }
    return EXIT_SUCCESS;
}
