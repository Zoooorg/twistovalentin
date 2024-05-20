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
 * @file driver.h
 *
 * @brief 
 */

#ifndef DRIVER_H
#define DRIVER_H

#include "track.h"
#include "follow_line.h"
#include "stack.h"

#define MINIMAL_RANGE 5
#define SPEED_RANGE_FACTOR 2
#define MAXIMAL_SPEED 5
#define MAX_LINE_LENGTH 1024
#define BOOSTS_AT_START 5
#define ACTION_LENGTH 10
#define NO_ACCELERATION 0
#define NO_STEP 0
#define TEST_STRAIGHT_LINE 3
#define MINIMAL_STRAIGHT_LINE_SIZE(speed) (MINIMAL_RANGE + SPEED_RANGE_FACTOR * speed)
#define DIRECTION(pilotData) (pilotData->direction)
#define PATH(pilotData) (pilotData->path)
#define PATH_TO_FREE(pilotData) (pilotData->pathToFree)
#define START_POSITION(pilotData) (pilotData->startPosition)
#define END_POSITION(pilotData) (pilotData->endPosition)
#define GAS(pilotData) (pilotData->gas)
#define IN_SAND(pilotData) (pilotData->isInSand)
#define X_SPEED(pilotData) (pilotData->xSpeed)
#define Y_SPEED(pilotData) (pilotData->ySpeed)
#define X_ACCELERATION(pilotData) (pilotData->xAcceleration)
#define Y_ACCELERATION(pilotData) (pilotData->yAcceleration)


typedef enum {

    NORTH,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST,

    MAX_DIRECTION = 8,
    NO_DIRECTION = -1,

} Direction;


typedef struct driverData {

    Map map;
    Direction direction;
    Path path;
    PathList pathToFree;
    Position startPosition;
    Position endPosition;
    int gas;
    int step;
    int isInSand;
    int xSpeed;
    int ySpeed;
    int xAcceleration;
    int yAcceleration;

} *DriverData;


typedef void (*addInPath)(DriverData, Path, int);



int speedVector(int speedX, int speedY);


/**
 * @brief Compute the gas consumption of a requested acceleration.
 *
 * CAUTION: Even an illegal move will result in gas consumption. Producing
 * illegal moves should be prevented as much as possible!
 *
 * @param xAcceleration Acceleration x component.
 * @param yAcceleration Acceleration y component.
 * @param speedX Speed x component.
 * @param speedY Speed y component.
 * @param inSand (boolean).
 * 
 * @return Number of gas units consumed.
 */
int gasConsumption(int xAcceleration, int yAcceleration, int speedX, int speedY, int inSand);


void getOffset(Direction direction, int* xOffset, int* yOffset);


int canMoveInTheDirectionInTheRange(Map map, Direction direction, int range, int xPilot, int yPilot);


Direction getDirection(Map map, int xPilot, int yPilot);


void goBorder(Map map, Direction direction, int* xCoordinate, int* yCoordinate);


int canTurn(Map map, Direction direction, int xCoordinate, int yCoordinate);


int whenTurning(Map map, Direction direction, Direction turningDirection, int xCoordinate, int yCoordinate);


Direction addDirection(Direction direction, Direction directionToAdd );


int getSizeBeforeTurning(Map map, Direction direction, int xPilot, int yPilot);

int isAStraightLine(Map map, Direction direction, int xPilot, int yPilot, int speedX, int speedY);


void accelerateInDirection(Direction direction, int* speedX, int* speedY);


void accelerate(int accelerationX, int accelerationY);


void calculateAcceleration(Position startPosition, Position endPosition, int* speedX, int* speedY, int* accelerationX, int* accelerationY);


void getPilotPosition(int* myX, int* myY, int* secondX, int* secondY, int* thirdX, int* thirdY);


void wait(double time);


int canMoveBetweenPositions(Map map, Position startPosition, Position stopPosition);


int lenghtBeforeOffTrack(Map map, Direction direction, int xCoordinate, int yCoordinate);


Direction whichDirectionTurn(Map map, Direction direction, int xCoordinate, int yCoordinate);


int canAddInPath(DriverData data);

DriverData newDriverData();

void setData(DriverData data, Map map, Direction direction, Path path, Position startPosition, Position endPosition, int step, int gas, int inSand, int xSpeed, int ySpeed, int xAcceleration, int yAcceleration);

void resetData(DriverData data, Direction direction, Path path, Position startPosition, Position endPosition, int step, int gas, int inSand, int xSpeed, int ySpeed, int xAcceleration, int yAcceleration);

void addInPathUnidirection(DriverData data, Path finalPath, int lengthStraightLine);

void addInPathMultidirection(DriverData data, Path finalPath, int loop);

int extendPath(DriverData data, DriverData currentData, addInPath addInPath, Path finalPath, int argument, int xAcceleration, int yAcceleration);


void unidirectionnalPath(DriverData data, Path finalPath, int lengthStraightLine);


int isCardinalDirection(Direction direction);


int addPathInSand(DriverData data, DriverData currentData, addInPath addInPath, Path finalPath, int argument);


void multidirectionnalPath(DriverData data, Path finalPath, int loop);

Stack* getPositionInPath(Path path);


Stack* generatePath(Map map, Direction direction, Position position, int xSpeed, int ySpeed, int xAcceleration, int yAcceleration, int lengthStraightLine, int gas, int step);


Direction SpeedInDirection(int xSpeed, int ySpeed);


#endif /* DRIVER_H */ 