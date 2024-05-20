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
 * @file path.h
 *
 * @brief 
 */

#ifndef PATH_H
#define PATH_H

#include "position2D.h"

#define POSITION(path) (path->position)
#define STEP(path) (path->step)
#define FROM_WHERE(path) (path->FromWhere)


typedef struct path {

    Position position;
    int step;
    struct path* FromWhere;

} *Path;


Path newPath();


void createPath(Path path, Position position, int step, Path fromWhere);


void freePath(Path path);


#endif  /* PATH_H */