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
 * @file follow_line.h
 *
 * @brief 
 */

#ifndef FOLLOW_LINE_H
#define FOLLOW_LINE_H

#include "map.h"

#define EPSILON 0.5


/**
 * Dicrete line traversal information.
 */
typedef struct {

  Position start;
  Position end;
  Position2Dfloat currentPosition;
  Position2Dfloat delta;                  /*< Shift vector */
  int length;                             /*< Length along the main axis */
  int position;                           /*< Reference position on the line */
  
} InformationLine;

/**
 * @brief Initialize an InformationLine data structure
 */
void inititializeLine(Position startPosition,  Position stopPosition, InformationLine* informationLine);

/**
 * @brief Move a point along a line in one direction.
 *
 * @param informationLine Line traversal information.
 * @param point current/next position.
 * @param direction (+1 forward, -1 backward).
 * 
 * @return 1 if point is a new point in the line, otherwise -1 (info is already at the end point).
 */
int nextPoint(Map map, InformationLine* informationLine, Position point);

#endif /* FOLLOW_LINE_H */
