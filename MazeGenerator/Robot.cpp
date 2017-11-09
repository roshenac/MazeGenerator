//
//  Robot.cpp
//  MazeGenerator
//
//  Created by Roshenac Mitchell on 09/11/2017.
//  Copyright © 2017 Roshenac Mitchell. All rights reserved.
//

#include "Robot.h"

// accesor methods
// use these to obtain information about attributes of the robot
int Robot::GetRowLocation() const{return 0;}
int Robot::GetColumnLocation() const {return 0;}

// modifier methods
// Use these to change attributes of the robot
void Robot::PlaceInMaze(const Maze* pMaze, int r, int c){} ;

void Robot::SetRowLocation(int r) {};
void Robot::SetColumnLocation(int c) {};

// methods to move robot
bool Robot::Up() {return false;}
bool Robot::Down() {return false;}
bool Robot::Left() {return false;}
bool Robot::Right() {return false;}

// Each time this member function is called,
// the logic inside it should make it move one step towards the
// end position of the maze. Essentially, for each call of this
// it should perform one of : Up, Down, Left or Right(). Which direction
// depends on your logic to exit the maze.
bool Robot::StepTowardsEnd(int& NewR, int& NewC) {return false;}


// EnsureValidPosition returns true if (r,c) is a valid Maze location and it is empty
// returns false otherwise
bool Robot::EnsureValidPosition(int r, int c) {return false;}

