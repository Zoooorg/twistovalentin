
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
 * @file list.h
 *
 * @brief 
 */

#ifndef LIST_H
#define LIST_H

#include "position2D.h"
#include "path.h"

#define NEXT_PATH_CELL_OF(list) (list->nextPathCell)
#define CURRENT_PATH_OF(list) (list->currentPath)
#define NEXT_POSITION_CELL_OF(list) (list->nextPositionCell)
#define CURRENT_POSITION_OF(list) (list->currentPosition)


typedef struct pathCell {

    Path currentPath;           
    struct pathCell* nextPathCell;      

}PathCell, *PathList;


typedef struct positionCell {

    Position currentPosition;           
    struct positionCell* nextPositionCell;      

} PositionCell, *PositionList;


/**
 * @brief Create a new list of paths.
 *
 * @return A pointer to the new list of paths.
 */
PathList newPathList();


/**
 * @brief Free the memory used by a list of paths.
 *
 * @param list Pointer to the list of paths to free.
 */
void freePathList(PathList list);


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
PathList addPathToList(PathList list, Path path);


/**
 * @brief Create a new list of positions.
 *
 * @return A pointer to the new list of positions.
 */
PositionList newPositionList();


/**
 * @brief Free the memory used by a list of positions.
 *
 * @param list Pointer to the list of positions to free.
 */
void freePositionList(PositionList list);


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
PositionList addPositonToList(PositionList list, Position position);


#endif  /* LIST_H */