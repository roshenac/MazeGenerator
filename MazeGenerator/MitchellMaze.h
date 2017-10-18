#ifndef MITCHELLMAZE_H_INCLUDED
#define MITCHELLMAZE_H_INCLUDED

#include "Maze.h"
#include <iostream>
#include <vector>

class MitchellMaze: public Maze
{
public:
    MitchellMaze() {}
    MitchellMaze(int nr, int nc, const point& start, const point& end): Maze::Maze(nr,nc,start,end)  // create a Maze with nr rows and nc columns
    {
        GenerateMaze(nr,nc,start,end) ;
    }
    
    ~MitchellMaze();
    
    //regenerate a maze with new size nr, nc
    // if no arguments are given, then use existing size
    void Regenerate(int nr, int nc, const point& start, const point& end) ;
    
    // Get info about maze
    int nRows() const ; // # rows
    int nCols() const ; // # cols
 
    // Maze cell does not contain a wall
    bool IsEmpty(int i, int j) const ;
    
    void UpdateRobotLocs(const std::vector<point>& vp) ;

    std::ostream&  Display(std::ostream& os) const ;
    
private:
    
    //start and end positions
    Maze::point m_start;
    Maze::point m_end;
    
    // number of rows and columns
    int m_numRows;
    int m_numColumns;
    
    bool m_retry; 
    
    // Matrix to store empty and full cells of maze
    std::vector<std::vector<bool> > m_mazeMatrix;
    
    // Vector of points visited for maze backtracking
    std::vector<Maze::point> m_visitedPath;

    //overridden with my own version of GenerateMaze
    void GenerateMaze(int nr, int nc, const point& start, const point& end) ;

    void initialiseMatrix(const int rowNumber, const int columnNumber);
    void createBacktrackingMaze(Maze::point& point);
    
    Maze::point updateMazePoint(const int row, const int column, const Maze::point& diff);
    
    std::vector<Maze::point> checkValidNeighbours(const int row, const int column) const ;
    
    bool validRow(const int row) const;
    bool validColumn(const int column) const;
    bool isValid(const int row, const int column) const;
    
    bool reachedStartEnd() const;
    
    // Do not want to allow mazes to be copied hence private copy constructor
    MitchellMaze(const MitchellMaze& m);
};

#endif // MITCHELLMAZE
