//
//  MitchellMaze.cpp
//  RobotProject
//
//  Created by Roshenac Mitchell on 10/10/2015.
//  Copyright © 2015 Roshenac Mitchell. All rights reserved.
//

#include "MitchellMaze.h"

//Do not want to allow mazes to be copied hence private copy constructor
MitchellMaze::MitchellMaze(const MitchellMaze& m)
{
    MitchellMaze(m.nRows(), m.nCols(), m._st, m._end);
}

//Destructor
MitchellMaze::~MitchellMaze()
{
}

// Get info about maze
// # rows
int MitchellMaze::nRows() const
{
    return m_numRows;
}

// # cols
int MitchellMaze::nCols() const
{
    return m_numColumns;
}

bool MitchellMaze::IsEmpty(int i, int j) const
{
    return !m_mazeMatrix[i][j];
}


void MitchellMaze::UpdateRobotLocs(const std::vector<point>& vp)
{
    // TODO
}


std::ostream& MitchellMaze::Display(std::ostream& os) const
{
    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            if(i == m_start.r && j== m_start.c)
            {
                os <<  "..";
            }
            else if(i == m_end.r && j== m_end.c)
            {
                os <<  "XX";
            }else if(IsEmpty(i,j))
            {
                os <<  "  ";
            } else{
                os << "##";
            }
        }
        os<< std::endl;
    }
    os << "-------------------"  << std::endl;
    return os;
}


//overridden with my own version of GenerateMaze
void MitchellMaze::GenerateMaze(int nr, int nc, const point& start, const point& end)
{
    m_start = start;
    m_end = end;
    m_numRows = nr;
    m_numColumns = nc;
    
    m_visitedPath.clear();
    
    initialiseMatrix(m_numRows, m_numColumns);
}

void MitchellMaze::initialiseMatrix(const int rowNumber, const int columnNumber)
{
    std::vector<bool> columnMatrix(columnNumber);
    std::vector<std::vector<bool> > rowColumnMatrix(rowNumber, columnMatrix);
    m_mazeMatrix = rowColumnMatrix;
    
    for (int i = 0; i < rowNumber; i++) {
        for (int j = 0; j < columnNumber; j++) {
            m_mazeMatrix[i][j] = 1;
        }
    }
    
    createBacktrackingMaze(m_end);
}

void MitchellMaze::createBacktrackingMaze(Maze::point& point)
{
    m_retry = false;
    bool mazeGenerated = false;
    while(!mazeGenerated)
    {
        std::vector<Maze::point> validNeighbours= checkValidNeighbours(point.r, point.c);
        
        if(validNeighbours.size() > 0)
        {
            int dir = rand() % (validNeighbours.size());
            point = updateMazePoint(point.r, point.c, validNeighbours[dir]);
        }else{
            if(m_visitedPath.size() > 1)
            {
                m_visitedPath.pop_back();
                Maze:: point previousPoint = m_visitedPath.back();
                point = previousPoint;
            }else{
                if(!reachedStartEnd())
                {
                    m_mazeMatrix[m_start.r][m_start.c-1] = 0;
                }
                
                mazeGenerated = true;
            }
        }
    }
}


std::vector<Maze::point> MitchellMaze::checkValidNeighbours(const int row, const int column) const
{
    std::vector<Maze::point> neighbours = {Maze::point(-2,0), Maze::point(2,0), Maze::point(0,2), Maze::point(0,-2)};
    
    std::vector<Maze::point> validNeighbours;
    
    for(auto const& point: neighbours)
    {
        int newRow = row+ point.r;
        int newColumn = column + point.c;
        if(isValid(newRow, newColumn) && (m_mazeMatrix[newRow][newColumn] == 1)){
            validNeighbours.push_back(point);
        }
    }
    return validNeighbours;
}

Maze::point MitchellMaze::updateMazePoint(const int row, const int column, const Maze::point& diff)
{
    int columnDiff = diff.c;
    int rowDiff = diff.r;
    
    
    while(columnDiff != 0 || rowDiff != 0)
    {
        if(m_retry)
        {
            std::cout<< "retyr" <<std::endl;
        }
        
        m_mazeMatrix[row + rowDiff][column + columnDiff] = 0;
        if(columnDiff != 0 ){columnDiff = (diff.c < 0) ? (columnDiff +1 ) : (columnDiff - 1) ;}
        if(rowDiff != 0){rowDiff = (diff.r < 0) ? (rowDiff +1 ) : (rowDiff - 1)  ;}
    }
    
    Maze::point newPoint(row + diff.r, column + diff.c);
    
    
    m_visitedPath.push_back(newPoint);
    
    
    return newPoint;
}

// Check to make sure you can reach both start and end point
bool MitchellMaze::reachedStartEnd() const
{
    bool reachedStart = false;
    bool reachedEnd = false;
    
    std::vector<Maze::point> neighbours = {Maze::point(-1,0), Maze::point(1,0), Maze::point(0,1), Maze::point(0,-1), Maze::point(0,0)};
    
    for(auto const& point: neighbours)
    {
        int newStartRow = m_start.r+ point.r;
        int newStartColumn = m_start.c + point.c;
        
        int newEndRow = m_end.r+ point.r;
        int newEndColumn = m_end.c + point.c;
        
        if(isValid(newStartRow, newStartColumn) && (m_mazeMatrix[newStartRow][newStartColumn] == 0)){
            reachedStart = true;
        }
        
        if(isValid(newEndRow, newEndColumn) && (m_mazeMatrix[newEndRow][newEndColumn] == 0)){
            reachedEnd = true;
        }
    }
    
    return reachedStart  && reachedEnd;
}


//validators
bool MitchellMaze::validRow(const int column) const
{
    return column >=0 && column< m_numRows;
}

bool MitchellMaze::validColumn(const int column) const
{
    return column >=0 && column< m_numColumns;
}

bool MitchellMaze::isValid(const int row, const int column) const
{
    return validRow(row) && validColumn(column);
}


//regenerate a maze with new size nr, nc
// if no arguments are given, then use existing size
void MitchellMaze::Regenerate(int nr, int nc, const point& start, const point& end)
{
    GenerateMaze(nr, nc, start, end);
};

