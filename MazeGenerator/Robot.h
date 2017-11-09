//
//  Robot.hpp
//  MazeGenerator
//
//  Created by Roshenac Mitchell on 09/11/2017.
//  Copyright © 2017 Roshenac Mitchell. All rights reserved.
//

#ifndef Robot_h
#define Robot_h

#include "Maze.h"

#include <iostream>
#include <stdexcept>
#include <string>

class Robot
{
public:
    Robot() {} // takes no parameters, 'default constructor'
    
    
    // accesor methods
    // use these to obtain information about attributes of the robot
    int GetRowLocation() const;
    int GetColumnLocation() const;
    
    // modifier methods
    // Use these to change attributes of the robot
    void PlaceInMaze(const Maze* pMaze, int r=0, int c=0);
    
    void SetRowLocation(int r);
    void SetColumnLocation(int c);
    
    // methods to move robot
    bool Up() ;
    bool Down() ;
    bool Left() ;
    bool Right() ;
    
    // Each time this member function is called,
    // the logic inside it should make it move one step towards the
    // end position of the maze. Essentially, for each call of this
    // it should perform one of : Up, Down, Left or Right(). Which direction
    // depends on your logic to exit the maze.
    bool StepTowardsEnd(int& NewR, int& NewC) ;
    
private:
    int _r;
    int _c;
    Maze _pMaze;
    
    bool EnsureValidPosition(int r, int c) ; // see Robot.h
    
    bool moveTowardsRow(const int r);
    bool moveTowardsColumn(const int c);
    bool randomMove();
};

#endif /* Robot_h */
