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
 * @file driver.c
 *
 * @brief 
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include "driver.h"


int speedVector(int speedX, int speedY) {

    return (int)sqrt(speedX * speedX + speedY * speedY);
}


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
int gasConsumption(int xAcceleration, int yAcceleration, int speedX, int speedY, int inSand) {

    int gas = xAcceleration * xAcceleration + yAcceleration * yAcceleration;

    gas += (speedVector(speedX, speedY) * 3.0 / 2.0);

    if (inSand) {
      gas += 1;
    }

    return -gas;
}


void getOffset(Direction direction, int* xOffset, int* yOffset) {

    switch (direction) {

        case NORTH: 
            *yOffset = -1; 
            break;

        case EAST:          
            *xOffset = 1; 
            break;

        case SOUTH:       
            *yOffset = 1; 
            break;

        case WEST:          
            *xOffset = -1; 
            break;

        case NORTH_EAST:    
            *xOffset = 1; 
            *yOffset = -1; 
            break;

        case SOUTH_EAST:    
            *xOffset = 1; 
            *yOffset = 1; 
            break;
        
        case SOUTH_WEST:    
            *xOffset = -1; 
            *yOffset = 1; 
            break;  

        case NORTH_WEST:    
            *xOffset = -1; 
            *yOffset = -1; 
            break;

        default:       
            break; 
    }
}


int canMoveInTheDirectionInTheRange(Map map, Direction direction, int range, int xPilot, int yPilot) {

    int xOffset = 0, yOffset = 0;

    getOffset(direction, &xOffset, &yOffset);

    return areValidPositionsInTheRange(map, range, xPilot, yPilot, xOffset, yOffset);
}   


Direction getDirection(Map map, int xPilot, int yPilot) {

    Direction direction;

    for (direction = NORTH; direction < MAX_DIRECTION; direction++) {
        if (canMoveInTheDirectionInTheRange(map, direction, MINIMAL_RANGE, xPilot, yPilot)) {
            return direction;
        }
    }

    return NO_DIRECTION;
}


void goBorder(Map map, Direction direction, int* xCoordinate, int* yCoordinate) {

    int xOffset = 0, yOffset = 0;

    getOffset(direction, &xOffset, &yOffset);

    do {
        *xCoordinate += xOffset;
        *yCoordinate += yOffset;

    } while (isAValidPosition(getPosition(map, *xCoordinate, *yCoordinate)));
}


int canTurn(Map map, Direction direction, int xCoordinate, int yCoordinate) {

    int xOffset = 0, yOffset = 0;

    getOffset(direction, &xOffset, &yOffset);

    xCoordinate += xOffset;
    yCoordinate += yOffset;

    return isAValidPosition(getPosition(map, xCoordinate, yCoordinate));
}


int whenTurning(Map map, Direction direction, Direction turningDirection, int xCoordinate, int yCoordinate) {

    goBorder(map, turningDirection, &xCoordinate, &yCoordinate);

    int xOffset = 0, yOffset = 0;
    int sizeStraightLine = -1;

    getOffset(direction, &xOffset, &yOffset);

    do {
        xCoordinate += xOffset;
        yCoordinate += yOffset;
        sizeStraightLine++;

    } while (!canTurn(map, turningDirection, xCoordinate, yCoordinate));

    return (sizeStraightLine - MINIMAL_RANGE);
}


Direction addDirection(Direction direction, Direction directionToAdd ) {

    return ((direction + directionToAdd) % MAX_DIRECTION);
}


int getSizeBeforeTurning(Map map, Direction direction, int xPilot, int yPilot) {

    Direction leftDirection = addDirection(direction, WEST);
    Direction rightDirection = addDirection(direction, EAST);

    int sizeLeftStraightLine = whenTurning(map, direction, leftDirection, xPilot, yPilot);
    int sizeRightStraightLine = whenTurning(map, direction, rightDirection, xPilot, yPilot);

    if (sizeLeftStraightLine < sizeRightStraightLine) {
        return sizeLeftStraightLine;
    } else {
        return sizeRightStraightLine;
    }
}


int isAStraightLine(Map map, Direction direction, int xPilot, int yPilot, int speedX, int speedY) {

    if (!canMoveInTheDirectionInTheRange(map, direction, MINIMAL_STRAIGHT_LINE_SIZE(speedVector(speedX, speedY)), xPilot, yPilot)) {
        return FALSE;
    }

    int sizeStraightLine = getSizeBeforeTurning(map, direction, xPilot, yPilot);

    if (sizeStraightLine < MINIMAL_STRAIGHT_LINE_SIZE(speedVector(speedX, speedY))) {
        return FALSE;
    }

    return sizeStraightLine;
}


void accelerateInDirection(Direction direction, int* speedX, int* speedY) {

    char action[ACTION_LENGTH];
    int accelerationX = 0, accelerationY = 0;

    getOffset(direction, &accelerationX, &accelerationY);
    *speedX += accelerationX;
    *speedY += accelerationY;

    sprintf(action, "%d %d", accelerationX, accelerationY);
    fprintf(stdout, "%s", action);
    fflush(stdout); 
}


void accelerate(int accelerationX, int accelerationY) {

    char action[ACTION_LENGTH];

    sprintf(action, "%d %d", accelerationX, accelerationY);
    fprintf(stdout, "%s", action);
    fflush(stdout); 
}


void calculateAcceleration(Position startPosition, Position endPosition, int* speedX, int* speedY, int* accelerationX, int* accelerationY) {

    *accelerationX = X_(endPosition) - (X_(startPosition) + *speedX);
    *accelerationY = Y_(endPosition) - (Y_(startPosition) + *speedY);

    *speedX += *accelerationX;
    *speedY += *accelerationY;
}


void getPilotPosition(int* myX, int* myY, int* secondX, int* secondY, int* thirdX, int* thirdY) {

    char line_buffer[MAX_LINE_LENGTH];

    fgets(line_buffer, MAX_LINE_LENGTH, stdin);   
    sscanf(line_buffer, "%d %d %d %d %d %d", myX, myY, secondX, secondY, thirdX, thirdY);
}


void wait(double time) {

    sleep(time);
}


int canMoveBetweenPositions(Map map, Position startPosition, Position stopPosition) {

    InformationLine line;
    Position position = NULL;

    inititializeLine(startPosition, stopPosition, &line);

    while (nextPoint(map, &line, position)) {
        if (!isAValidPosition(position)) {
            return FALSE;
        }
    }

    return TRUE;
}


int lenghtBeforeOffTrack(Map map, Direction direction, int xCoordinate, int yCoordinate) {

    int xOffset = 0, yOffset = 0;
    int length = -1;

    getOffset(direction, &xOffset, &yOffset);

    do {
        xCoordinate += xOffset;
        yCoordinate += yOffset;
        length++;

    } while (isAValidPosition(getPosition(map, xCoordinate, yCoordinate)));

    return length;
}


Direction whichDirectionTurn(Map map, Direction direction, int xCoordinate, int yCoordinate) {
    
    Direction leftDirection = addDirection(direction, NORTH_WEST);
    Direction rightDirection = addDirection(direction, NORTH_EAST);

    int leftLength = lenghtBeforeOffTrack(map, leftDirection, xCoordinate, yCoordinate);
    int rightLength = lenghtBeforeOffTrack(map, rightDirection, xCoordinate, yCoordinate);

    if (leftLength < rightLength) {
        return NORTH_EAST;
    } else if (rightLength < leftLength) {
        return NORTH_WEST;
    }

    return NORTH;
}


int canAddInPath(DriverData data) {

    if (!canMoveBetweenPositions(MAP(data), START_POSITION(data), END_POSITION(data))) {
        return FALSE;
    }

    if (!isAValidPosition(END_POSITION(data))) {
        return FALSE;
    }

    int consumedGas = gasConsumption(X_ACCELERATION(data), Y_ACCELERATION(data), X_SPEED(data), Y_SPEED(data), IN_SAND(data));
    if ((GAS(data) - consumedGas) < 0) {
        return FALSE;
    }

    return TRUE;
}

DriverData newDriverData() {

    return NULL;
}

void setData(DriverData data, Map map, Direction direction, Path path, Position startPosition, Position endPosition, int step, int gas, int inSand, int xSpeed, int ySpeed, int xAcceleration, int yAcceleration) {

    MAP(data) = map;
    PATH_TO_FREE(data) = newPathList();
    resetData(data, direction, path, startPosition, endPosition, step, gas, inSand, xSpeed, ySpeed, xAcceleration, yAcceleration); 
}

void resetData(DriverData data, Direction direction, Path path, Position startPosition, Position endPosition, int step, int gas, int inSand, int xSpeed, int ySpeed, int xAcceleration, int yAcceleration) {

    DIRECTION(data) = direction;
    PATH(data) = path;
    START_POSITION(data) = startPosition;
    END_POSITION(data) = endPosition;
    STEP(data) = step;
    GAS(data) = gas;
    IN_SAND(data) = inSand;
    X_SPEED(data) = xSpeed;
    Y_SPEED(data) = ySpeed;
    X_ACCELERATION(data) = xAcceleration;
    Y_ACCELERATION(data) = yAcceleration;
    
}

void addInPathUnidirection(DriverData data, Path finalPath, int lengthStraightLine) {

    Path path = newPath();

    createPath(path, END_POSITION(data), ++STEP(data), (PATH(data)));
    
    int gas = GAS(data) - gasConsumption(X_ACCELERATION(data), Y_ACCELERATION(data), X_SPEED(data), Y_SPEED(data), IN_SAND(data));
    int xSpeed = X_ACCELERATION(data) + X_SPEED(data);
    int ySpeed = Y_ACCELERATION(data) + Y_SPEED(data);

    resetData(data, DIRECTION(data), path, POSITION(path), NULL, STEP(data), gas, IN_SAND(data), xSpeed, ySpeed, NO_ACCELERATION, NO_ACCELERATION);
   
    unidirectionnalPath(data, finalPath, (lengthStraightLine - speedVector(X_SPEED(data), Y_SPEED(data))));
}

void addInPathMultidirection(DriverData data, Path finalPath, int loop) {

    Path path = newPath();

    createPath(path, END_POSITION(data), ++STEP(data), (PATH(data)));
    
    int gas = GAS(data) - gasConsumption(X_ACCELERATION(data), Y_ACCELERATION(data), X_SPEED(data), Y_SPEED(data), IN_SAND(data));
    int xSpeed = X_ACCELERATION(data) + X_SPEED(data);
    int ySpeed = Y_ACCELERATION(data) + Y_SPEED(data);

    resetData(data, SpeedInDirection(X_SPEED(data), Y_SPEED(data)), path, POSITION(path), NULL, STEP(data), gas, IN_SAND(data), xSpeed, ySpeed, NO_ACCELERATION, NO_ACCELERATION);
    multidirectionnalPath(data, finalPath, --loop);
}


int extendPath(DriverData data, DriverData currentData, addInPath addInPath, Path finalPath, int argument, int xAcceleration, int yAcceleration) {

    Position position = nextPosition(MAP(currentData), X_(START_POSITION(currentData)), Y_(START_POSITION(currentData)), X_SPEED(currentData), Y_SPEED(currentData), xAcceleration, yAcceleration);

    resetData(data, DIRECTION(currentData), PATH(currentData), START_POSITION(currentData), position, STEP(currentData), GAS(currentData), IN_SAND(currentData), X_SPEED(currentData), Y_SPEED(currentData), xAcceleration, yAcceleration);
    
    if (canAddInPath(data)) {
        addInPath(data, finalPath, argument);
        return TRUE;
    } else {
        free(position);
        return FALSE;
    }
}


void unidirectionnalPath(DriverData data, Path finalPath, int lengthStraightLine) {

    if (lengthStraightLine <= 0) {
         multidirectionnalPath(data, finalPath, TEST_STRAIGHT_LINE);
         return;
    }

    if (GROUND_(START_POSITION(data)) == END) {
        if (STEP(data) < STEP(finalPath)) {
            finalPath = PATH(data);
        } else {
            addPathToList(PATH_TO_FREE(data), PATH(data));
        }
        return;
    }

    if (GROUND_(START_POSITION(data)) == SAND) {
        if (!addPathInSand(data, data, addInPathUnidirection, finalPath, lengthStraightLine)) {
            addPathToList(PATH_TO_FREE(data), PATH(data));
        }
        return;
    }

    DriverData currentData = newDriverData();
    setData(currentData, MAP(data), DIRECTION(data), PATH(data), START_POSITION(data), END_POSITION(data), STEP(data), GAS(data), IN_SAND(data), X_SPEED(data), Y_SPEED(data), X_ACCELERATION(data), Y_ACCELERATION(data));
    int addedPath = 0;

    int xMinimalSpeed = 0, yMinimalSpeed = 0;
    getOffset(DIRECTION(currentData), &xMinimalSpeed, &yMinimalSpeed);

    if ((X_SPEED(currentData) > xMinimalSpeed) && (Y_ACCELERATION(currentData) > yMinimalSpeed)) {
        if (extendPath(data, currentData, addInPathUnidirection, finalPath, lengthStraightLine, -xMinimalSpeed, -xMinimalSpeed)) {
            addedPath++;
        }
    }
    
    if (extendPath(data, currentData, addInPathUnidirection, finalPath, lengthStraightLine, NO_ACCELERATION, NO_ACCELERATION)) {
        addedPath++;
    }

    int newXSpeed = X_SPEED(currentData) + xMinimalSpeed;
    int newYSpeed = Y_SPEED(currentData) + yMinimalSpeed;
    if (speedVector(newXSpeed, newYSpeed) < MAXIMAL_SPEED) {
        if (extendPath(data, currentData, addInPathUnidirection, finalPath, lengthStraightLine, xMinimalSpeed, xMinimalSpeed)) {
            addedPath++;
        }
    }

    if (addedPath == 0) {
        addPathToList(PATH_TO_FREE(data), PATH(data));
    }
}


int isCardinalDirection(Direction direction) {

    return ((direction % EAST) == 0);
}


int addPathInSand(DriverData data, DriverData currentData, addInPath addInPath, Path finalPath, int argument) {
    
    int xAcceleration = 0, yAcceleration = 0;
    IN_SAND(data) = TRUE;
    X_SPEED(data) = 0;
    Y_SPEED(data) = 0;

    if (isCardinalDirection(DIRECTION(currentData))) {
        getOffset(DIRECTION(data), &xAcceleration, &yAcceleration);
    } else {
        Direction turningDirection = whichDirectionTurn(MAP(data), DIRECTION(data), X_(START_POSITION(data)), Y_(START_POSITION(data)));
        DIRECTION(data) = addDirection(DIRECTION(data), turningDirection);
        getOffset(DIRECTION(data), &xAcceleration, &yAcceleration);
    }

    return extendPath(data, currentData, addInPath, finalPath, argument, xAcceleration, yAcceleration);
}


void multidirectionnalPath(DriverData data, Path finalPath, int loop) {

    if (loop <= 0) {
        int lengthStraightLine = isAStraightLine(MAP(data), DIRECTION(data), X_(START_POSITION(data)), Y_(START_POSITION(data)), X_SPEED(data), Y_SPEED(data));
        unidirectionnalPath(data, finalPath, lengthStraightLine);
        return;
    }

    if (GROUND_(START_POSITION(data)) == END) {
        if (STEP(data) < STEP(finalPath)) {
            finalPath = PATH(data);
        } else {
            addPathToList(PATH_TO_FREE(data), PATH(data));
        }
        return;
    }

    if (GROUND_(START_POSITION(data)) == SAND) {
        if (!addPathInSand(data, data, addInPathMultidirection, finalPath, loop)) {
            addPathToList(PATH_TO_FREE(data), PATH(data));
        }
        return;
    }

    DriverData currentData = newDriverData();
    setData(currentData, MAP(data), DIRECTION(data), PATH(data), START_POSITION(data), END_POSITION(data), STEP(data), GAS(data), IN_SAND(data), X_SPEED(data), Y_SPEED(data), X_ACCELERATION(data), Y_ACCELERATION(data));
 
    int xMinimalSpeed = 0, yMinimalSpeed = 0;
    getOffset(DIRECTION(currentData), &xMinimalSpeed, &yMinimalSpeed);

    Direction turningDirection = whichDirectionTurn(MAP(data), DIRECTION(data), X_(START_POSITION(data)), Y_(START_POSITION(data)));
    Direction endDirection;
    if ((X_SPEED(data) > xMinimalSpeed) && (Y_ACCELERATION(data) > yMinimalSpeed)) {
        endDirection = addDirection(DIRECTION(data), SOUTH);
    } else {
        endDirection = addDirection(addDirection(DIRECTION(data), turningDirection), turningDirection);
    }

    int addedPath = 0;
    Direction currentDirection = DIRECTION(data);
    while (currentDirection != endDirection) {
        int xAcceleration = 0, yAcceleration = 0;
        getOffset(currentDirection, &xAcceleration, &yAcceleration);
        if (extendPath(data, currentData, addInPathMultidirection, finalPath, loop, xAcceleration, yAcceleration)) {
            addedPath++;
        }
        currentDirection = addDirection(currentDirection, turningDirection);
    }
    if (extendPath(data, currentData, addInPathMultidirection, finalPath, loop, NO_ACCELERATION, NO_ACCELERATION)) {
        addedPath++;
    }

    if (addedPath == 0) {
        addPathToList(PATH_TO_FREE(data), PATH(data));
    }
}

Stack* getPositionInPath(Path path) {

    Stack* positionPath = createStack();

    do {
        push(positionPath, POSITION(path));
        Path temporaryPath = FROM_WHERE(path);
        freePath(path);
        path = temporaryPath;

    } while (FROM_WHERE(path) != NULL);

    return positionPath;
}


Stack* generatePath(Map map, Direction direction, Position position, int xSpeed, int ySpeed, int xAcceleration, int yAcceleration, int lengthStraightLine, int gas, int step) {

    Path currentPath = newPath();
    createPath(currentPath, position, step, NULL);
    Path finalPath = newPath();

    DriverData data = newDriverData();
    setData(data, map, direction, currentPath, position, NULL, STEP(currentPath), gas, isSand(position), xSpeed, ySpeed, xAcceleration, yAcceleration);

    if (lengthStraightLine > 0) {
        unidirectionnalPath(data, finalPath, lengthStraightLine);
    } else {
        multidirectionnalPath(data, finalPath, TEST_STRAIGHT_LINE);
    }

    Stack* positionPath = getPositionInPath(finalPath);
    freePathList(PATH_TO_FREE(data));

    return positionPath;
}


Direction SpeedInDirection(int xSpeed, int ySpeed) {

    if ((xSpeed == 0) && (ySpeed < -1)) {
        return NORTH;

    } else if ((xSpeed >= 1) && (ySpeed <= -1)) {
        return NORTH_EAST;

    } else if ((xSpeed >= 1) && (ySpeed == 0)) {
        return EAST;

    } else if ((xSpeed >= 1) && (ySpeed >= 1)) {
        return SOUTH_EAST;

    } else if ((xSpeed == 0) && (ySpeed >= 1)) {
        return SOUTH;

    } else if ((xSpeed <= -1) && (ySpeed >= 1)) {
        return SOUTH_WEST;

    } else if ((xSpeed <= -1) && (ySpeed == 0)) {
        return WEST;

    } else if ((xSpeed <= -1) && (ySpeed <= -1)) {
        return NORTH_WEST;
    } 

    return NO_DIRECTION;
}