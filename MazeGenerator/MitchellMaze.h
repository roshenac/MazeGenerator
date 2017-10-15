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
 
    bool IsEmpty(int i, int j) const ;
    
    void UpdateRobotLocs(const std::vector<point>& vp) ;

    std::ostream&  Display(std::ostream& os) const ;
    
private:
    
    //start and end positions
    int m_rowStart;
    int m_rowEnd;
    int m_columnStart;
    int m_columnEnd;
    int m_numRows;
    int m_numColumns;
    
    std::vector<std::vector<bool> > m_mazeMatrix;
    std::vector<Maze::point> m_visitedPath;

    //overridden with my own version of GenerateMaze
    void GenerateMaze(int nr, int nc, const point& start, const point& end) ;
    
    void printMaze(std::ostream& os , const int i, const int j) const;
    
    void setUpMatrix(const int rowNumber, const int columnNumber);
    
    void solvable();
    
    bool validRow(const int row) const;
    bool validColumn(const int column) const;
    bool isValid(const int row, const int column) const;
    
    bool reachedStartEnd();
    
    // Do not want to allow mazes to be copied hence private copy constructor
    MitchellMaze(const MitchellMaze& m);
};

#endif // MITCHELLMAZE
