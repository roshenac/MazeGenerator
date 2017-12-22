# MazeGenerator

## Description
The aim of this project was to create a solvable maze as well as a robot that can get from the start to the end of the maze. Currently the maze is not solvable and the robot moves in a random direction.

The 4 header files and the main files were given to us. We had to rename the SubrRobot.h and SubrMaze.h to our own names and rename it anywhere else it was used.


### ROBOT
In my MitchellRobot.cpp I implemented the methods in MitchellRobot.h that had not already been defined. This included:
* Up, Down, Left, Right
* StepTowardsEnd
* EnsureValidPosition
* Copy Contructor

In the direction methods, first I got the current row and column location using GetRowLocation and GetColumnLocation. I then incremented or decrements the row or column depending on what direction I was trying to go in. After checking to see if the direction was valid, I set the row or column with the updated value and return true. If the direction wasn’t valid, I kept the row and column location as is and return true.

The EnsureValidPosition checks to see if the robot can move in that direction. It takes the proposed row and column value as its parameters. First it gets a handle to the maze and checks the number of rows and columns the maze has. If the row and column value is greater or equal to 0 AND less than the row/column size it proceeds to the next stage of validation. It then checks the maze to see if it is empty as the position you are trying to get to . If it is, it will return true ie. Its valid. Otherwise it returns false.

The copy constructor just calls the the constructor with the row, column and maze from the copied robot.

Currently the robot moves randomly. The StepTowardsEnd method creates a random number between 0-4. Depending on the number it moves in a random direction.


### MAZE
In my MitchelMaze.cpp I implemented the methods in MitchellRobot.h that had not already been defined. This included:

* Regenerate          (Does the same as GenerateMaze with new row and column size)
* GenerateMaze    (sets the parameters for size and start/end values. Calls create and initialize on the maze)
* Copy Constructor    (Calls the constructor with row/column size and start/end)
* Display
* UpdateRobotLocs    (updates the robots locations)
* IsEmpty (checks if position is valid and if position is equal to 0 in mazeMatrix vector)
* nCols
* nRows

I also added my own methods and variable to MitchellMaze.h and MitchellMaze.cpp. This included:
* mazeMatrix        (2d vector matrix that holds the walls of maze)
* Destructor
* setRows            ( takes a int and sets the row number)
* setCols            ( takes a int and sets the column number
* createMaze            (creates a 2d vector matrix)
* initialiseMaze        (sets the values of mazeMatrix to 0 or 1)
* printMaze
* validRows
* validColumn


The Display method prints the maze with the robots in it. It iterates over the rows and columns. For each value it iterates through the robots. If there is a robot there it will print out a robot and not print out the row/column value. If there isn’t a robot it will call print maze which will print out the appropriate maze value ie.wall/start/end/empty.
