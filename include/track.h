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
 * @file track.h
 *
 * @brief 
 */

#ifndef TRACK_H
#define TRACK_H

#include "path.h"
#include "map.h"


#define MAP_OF(track) (track->map)
#define END_POSITIONS_OF(track) (track->endPositions)


typedef struct track {
  
    Map map;
    PositionList endPositions;       

} *Track;


Track initializeTrack(int width, int height);


#endif  /* TRACK_H */
