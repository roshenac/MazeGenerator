//
//  main.cpp
//  MazeGenerator
//
//  Created by Roshenac Mitchell on 18/10/2017.
//  Copyright © 2017 Roshenac Mitchell. All rights reserved.
//

#include <iostream>
#include "Maze.h"

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    
    int MazeGridSize(40); // maze will be MazeGridSize x MazeGridSize
    
    Maze::point start(rand()%MazeGridSize, rand()%MazeGridSize); // random start location
    Maze::point end(rand()%MazeGridSize, rand()%MazeGridSize); // random end location

    // New instance of the maze with size, start and end position
    Maze* maze = new Maze(MazeGridSize, MazeGridSize, start, end);

    // comment out one of the following
    std::ostream& os(std::cout); // option 1. prints to screen
    
    // ofstream os("roshenacMaze.txt"); // option 2. prints to file
    
    // Display the maze
    maze->Display(os);
    
   return 0;
}
