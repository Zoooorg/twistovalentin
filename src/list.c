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
 * @file list.c
 *
 * @brief 
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


/**
 * @brief Create a new list of paths.
 *
 * @return A pointer to the new list of paths.
 */
PathList newPathList() {

    return NULL;
}


/**
 * @brief Free the memory used by a list of paths.
 *
 * @param list Pointer to the list of paths to free.
 */
void freePathList(PathList list) {

    while (list != NULL) {

        PathCell* temporaryPathCell = NEXT_PATH_CELL_OF(list);
        freePath(CURRENT_PATH_OF(list)); 
        free(list);
        list = temporaryPathCell;
    }
}


/**
 * @brief Add a new path to a list of paths.
 *
 * @param list Pointer to the list of paths to which to add.
 * @param path The path to add.
 *
 * @return A pointer to the modified list of paths.
 * 
 * The path is added to the beginning of the list.
 */
PathList addPathToList(PathList list, Path path) {

    PathCell* pathCell = (PathCell*)allocateMemory(sizeof(PathCell));

    CURRENT_PATH_OF(pathCell) = path;
    NEXT_PATH_CELL_OF(pathCell) = list;

    return pathCell;
}


/**
 * @brief Create a new list of positions.
 *
 * @return A pointer to the new list of positions.
 */
PositionList newPositionList() {

    return NULL;
}


/**
 * @brief Free the memory used by a list of positions.
 *
 * @param list Pointer to the list of positions to free.
 */
void freePositionList(PositionList list) {

    while (list != NULL) {

        PositionCell* temporaryPositionCell = NEXT_POSITION_CELL_OF(list);
        free(CURRENT_POSITION_OF(list)); 
        free(list);
        list = temporaryPositionCell;
    }
}


/**
 * @brief Add a new position to a list of positions.
 *
 * @param list Pointer to the list of positions to which to add.
 * @param position The position to add.
 *
 * @return A pointer to the modified list of positions.
 * 
 * The position is added to the beginning of the list.
 */
PositionList addPositonToList(PositionList list, Position position) {

    PositionCell* positionList = (PositionCell*)allocateMemory(sizeof(PositionCell));

    CURRENT_POSITION_OF(positionList) = position;
    NEXT_POSITION_CELL_OF(positionList) = list;

    return positionList;
}