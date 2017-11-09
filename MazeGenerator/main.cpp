//
//  main.cpp
//  MazeGenerator
//
//  Created by Roshenac Mitchell on 18/10/2017.
//  Copyright © 2017 Roshenac Mitchell. All rights reserved.
//

#include <iostream>
#include "Maze.h"
#include "Robot.h"


int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    
    int MazeGridSize(40); // maze will be MazeGridSize x MazeGridSize
    bool WinningPosition = false;
    float Time = 0.0f;
    int RunsNtimes = 10;
    int MaxSteps = 40;
    
    Maze::point start(rand()%MazeGridSize, rand()%MazeGridSize); // random start location
    Maze::point end(rand()%MazeGridSize, rand()%MazeGridSize); // random end location
    
    // New instance of the maze with size, start and end position
    Maze* maze = new Maze(MazeGridSize, MazeGridSize, start, end);
    
    for(int i (0); i< RunsNtimes ; i++ )
    {
        
        std::ostream& os(std::cout) ;
        Robot* robot = new Robot();
        
        bool Solved(false) ;
        int StepNum(0);
        while(!Solved && StepNum<MaxSteps) // only end if it is solved, or we exceed MaxSteps
        {
            StepNum++ ; // keep track of iterations
            std::vector<Maze::point> vlocs; // To store locations of each of the robots
            
            Maze::point rpt(robot->GetRowLocation(), robot->GetColumnLocation());
            vlocs.push_back(rpt) ; //  vlocs stores locations of each of the robots
            if (rpt==end) // does any of the positions correspond to the 'end' location?
            {
                Solved=true;
                WinningPosition=true;
            }
            
            
            maze->UpdateRobotLocs(vlocs) ; //  send locations of each of the robots to maze (for display)
            
            
            std::clock_t begint = clock();
            robot->StepTowardsEnd(end.r, end.c) ; // ask each robot to move 1 step
            std::clock_t endt = clock();
            Time += endt-begint;
            
            
            os << " ------ Step " << StepNum << " ------" << std::endl ; // display current positions
            maze->Display(os) ;
        }
        
        os << " Started at " << start.r << " " << start.c << std::endl ;
        os << " Ended at " << end.r << " " << end.c << std::endl ;
        
        // Display robots that reached target position
        if (WinningPosition) os << " Congrats! Robot solved the maze " << std::endl ;
        
        // No robots solved the maze
        if (!Solved)
        {
            std::cout << ":(" << std::endl ;
            os << "Unfortunately none of the robots navigated the maze :(" << std::endl ;
        }
        else
            std::cout << ":)" << std::endl ;
        
        os << std::endl ;
        
        
        // Display total computation time consumed by each of the robots
        
        os << "Computational time consumed by Robot  = " << Time << " clock ticks "<< std::endl ;
        delete robot;
        
        
        // Display the maze
        maze->Display(os);
    }
    return 0;
}
