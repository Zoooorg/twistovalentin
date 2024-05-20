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
 * @file path.c
 *
 * @brief 
 */

#include <stdio.h>
#include <stdlib.h>
#include "path.h"

Path newPath() {

    return NULL;
}

void createPath(Path path, Position position, int step, Path fromWhere) {

    POSITION(path) = position;
    fprintf(stderr, "la");
    STEP(path) = step;
    FROM_WHERE(path) = fromWhere;
}

void freePath(Path path) {

    if (path != NULL) {
        free(POSITION(path));
        free(FROM_WHERE(path));
        free(path);
    }
}
