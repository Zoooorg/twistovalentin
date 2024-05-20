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
 * @file follow_line.c
 *
 * @brief 
 */

#include "follow_line.h"

void inititializeLine(Position startPosition, Position stopPosition, InformationLine* informationLine) {

    int ABSDeltaX, ABSDeltaY, deltaX, deltaY;

    informationLine->start = startPosition;
    informationLine->currentPosition.x = X_(startPosition) + EPSILON;
    informationLine->currentPosition.y = Y_(startPosition) + EPSILON;
    informationLine->end = stopPosition;

    ABSDeltaX = deltaX = X_(stopPosition) - X_(startPosition);
    ABSDeltaY = deltaY = Y_(stopPosition) - Y_(startPosition);

    if (ABSDeltaX < 0)  {
        ABSDeltaX = -deltaX;
    }

    if (ABSDeltaY < 0) {
        ABSDeltaY = -deltaY;
    }

    informationLine->position = 0;
    informationLine->length = ABSDeltaX;

    if (ABSDeltaY > ABSDeltaX) {
        informationLine->length = ABSDeltaY;
    }

    informationLine->delta.x = ((float)deltaX) / informationLine->length;
    informationLine->delta.y = ((float)deltaY) / informationLine->length;
}


int nextPoint(Map map, InformationLine* informationLine, Position point) {

    if (informationLine->position == informationLine->length) {

        point = getPosition(map, X_(informationLine->end), Y_(informationLine->end));

        return FALSE; /* End of the line */
    }

    informationLine->currentPosition.x += informationLine->delta.x;
    informationLine->currentPosition.y += informationLine->delta.y;
    point = getPosition(map, X_(informationLine->end), Y_(informationLine->end));
    informationLine->position++;

    return TRUE;   /* a new point is found */    
}

