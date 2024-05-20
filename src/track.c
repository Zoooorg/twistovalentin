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
 * @file track.c
 *
 * @brief 
 */

#include <stdio.h>
#include <stdlib.h>
#include "track.h"


Track initializeTrack(int width, int height) {

    Track track = (Track)allocateMemory(sizeof(struct track*));

    MAP_OF(track) = initializeMap(width, height);
    END_POSITIONS_OF(track) = newPositionList();

    return track;
}

