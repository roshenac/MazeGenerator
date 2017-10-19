//
//  MitchellMaze.h
//  MazeGenerator
//
//  Created by Roshenac Mitchell on 18/10/2017.
//  Copyright © 2017 Roshenac Mitchell. All rights reserved.
//

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <iostream>
#include <vector>

class Maze
{
public:
    struct point
    {
        point(int R=0, int C=0):r(R), c(C) {}
        bool operator==(const point& p2) {return (r==p2.r&&c==p2.c);}
        int r;
        int c;
    };
    
    Maze() {}
    
    // create a Maze with nr rows and nc columns
    Maze(int nr, int nc, const point& start, const point& end)
    {
        GenerateMaze(nr, nc, start, end);
    }
    
    ~Maze();
    
    //regenerate a maze with new size nr, nc
    // if no arguments are given, then use existing size
    void Regenerate(int nr, int nc, const point& start, const point& end);
    
    // Get info about maze
    int nRows() const; // # rows
    int nCols() const; // # cols
    
    // Maze cell does not contain a wall
    bool IsEmpty(int i, int j) const;
    
    void UpdateRobotLocs(const std::vector<point>& vp);

    std::ostream&  Display(std::ostream& os) const;
    
private:
    //start and end positions
    point m_start;
    point m_end;
    
    // number of rows and columns
    int m_numRows;
    int m_numColumns;
    
    bool m_retry;
    
    // Matrix to store empty and full cells of maze
    std::vector<std::vector<bool> > m_mazeMatrix;
    
    // Vector of points visited for maze backtracking
    std::vector<point> m_visitedPath;

    //overridden with my own version of GenerateMaze
    void GenerateMaze(int nr, int nc, const point& start, const point& end);

    void initialiseMatrix(const int rowNumber, const int columnNumber);
    void createBacktrackingMaze(point& point);
    
    point updateMazePoint(const int row, const int column, const point& diff);
    
    std::vector<point> checkValidNeighbours(const int row, const int column) const;
    
    bool validRow(const int row) const;
    bool validColumn(const int column) const;
    bool isValid(const int row, const int column) const;
    
    bool reachedStartEnd() const;
    
    // Do not want to allow mazes to be copied hence private copy constructor
    Maze(const Maze& m);
};

#endif // MAZE
