# MazeGenerator

## Description
The aim of this project was to create a solvable maze as well as a robot that can get from the start to the end of the maze.

### ROBOT
Not currently implemented

### MAZE
The maze start and end position is set before generating the maze. The maze itself is generated using the back tracking method.

This method is broken down into the following steps:
* Initialise all the points in the maze to be walls
* Chose a random starting location and remove the wall

* Check if there is a random valid neighbour ( a neighbour is defined as current row or column +/- 2 )
* Remove the wall from that position
* If there are no valid neighbours
    * Backtrack to the last visited point
    * Continue till you have backtracked to all previously visited point
* Repeat until you have reached the start and end position
