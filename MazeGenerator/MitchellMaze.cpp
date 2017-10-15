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

void MitchellMaze::printMaze(std::ostream& os , const int i, const int j) const
{
    if(i == m_rowStart && j== m_columnStart)
    {
        os <<  "..";
    }
    else if(i == m_rowEnd && j== m_columnEnd)
    {
        os <<  "XX";
    }else if(IsEmpty(i,j))
    {
        os <<  "  ";
    } else{
        os << "##";
    }
}

std::ostream& MitchellMaze::Display(std::ostream& os) const
{
    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            printMaze(os, i, j);
        }
        os<< std::endl;
    }
    os << "-------------------"  << std::endl;
    return os;
}


//overridden with my own version of GenerateMaze
void MitchellMaze::GenerateMaze(int nr, int nc, const point& start, const point& end)
{
    m_rowStart = start.r;
    m_rowEnd = end.r;
    m_columnStart=start.c;
    m_columnEnd = end.c;
    m_numRows = nr;
    m_numColumns = nc;
    
    m_visitedPath.clear();
    
    setUpMatrix(m_numRows, m_numColumns);
}

void MitchellMaze::setUpMatrix(const int rowNumber, const int columnNumber)
{
    std::vector<bool> columnMatrix(columnNumber);
    std::vector<std::vector<bool> > rowColumnMatrix(rowNumber, columnMatrix);
    m_mazeMatrix = rowColumnMatrix;
    
    for (int i = 0; i < rowNumber; i++) {
        for (int j = 0; j < columnNumber; j++) {
            m_mazeMatrix[i][j] = 1;
        }
    }
    
    solvable();
}

// Back tracking method
// Need to move by 2 steps in order to create path
// in block maze
void MitchellMaze::solvable()
{
    bool solved = false;
    
    Maze::point point(m_rowStart, m_columnStart);
    
    while(!solved)
    {
        int row = point.r;
        int column = point.c;
        
   
        std::vector<std::string> neighbours;
        
        // north
        if(isValid(row-2, column) && (m_mazeMatrix[row-2][column] == 1)){
            neighbours.push_back("north");
        }
        
        // south
        if(isValid(row+2, column)  && (m_mazeMatrix[row+2][column] == 1)){
            neighbours.push_back("south");
        }
        
        // east
        if(isValid(row, column+2)  && (m_mazeMatrix[row][column+2] == 1)){
            neighbours.push_back("east");
        }
        
        // west
        if(isValid(row, column-2)  && (m_mazeMatrix[row][column-2] == 1)){
            neighbours.push_back("west");
        }
        
        if(neighbours.size() > 0)
        {
            int dir = rand() % (neighbours.size());
            
            if(neighbours[dir] == "north")
            {
                m_mazeMatrix[row-1][column] = 0;
                m_mazeMatrix[row-2][column] = 0;
                Maze::point newPoint(row-2, column);
                m_visitedPath.push_back(newPoint);
                point = newPoint;
            }else if(neighbours[dir] == "south")
            {
                m_mazeMatrix[row+1][column] = 0;
                m_mazeMatrix[row+2][column] = 0;
                Maze::point newPoint(row+2, column);
                m_visitedPath.push_back(newPoint);
                point = newPoint;
            }else if(neighbours[dir] == "east")
            {
                m_mazeMatrix[row][column+1] = 0;
                m_mazeMatrix[row][column+2] = 0;
                Maze::point newPoint(row, column+2);
                m_visitedPath.push_back(newPoint);
                point = newPoint;
            }else if(neighbours[dir] == "west")
            {
                m_mazeMatrix[row][column-1] = 0;
                m_mazeMatrix[row][column-2] = 0;
                Maze::point newPoint(row, column-2);
                m_visitedPath.push_back(newPoint);
                point = newPoint;
            }
            
        }else{
            if(m_visitedPath.size() > 1)
            {
                m_visitedPath.pop_back();
                Maze:: point p = m_visitedPath.back();
                point = p ;
            }else{
                if(!reachedStartEnd())
                {
                    std::cout<< "Unable to generate maze" << std::endl;
                }
                solved = true;
            }
        }
    }
}

// Check to make sure you can reach both start and end point
bool MitchellMaze::reachedStartEnd()
{
    bool hasReachedStart = false;
    bool hasReachedEnd = false;
    
    if(m_mazeMatrix[m_rowStart][m_columnStart] == 0 )
    {
        hasReachedStart = true;
    }
    
    if(m_mazeMatrix[m_rowStart][m_columnStart] == 0 )
    {
        hasReachedEnd = true;
    }
    
    return hasReachedStart && hasReachedEnd  ;
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

