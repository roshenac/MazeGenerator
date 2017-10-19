//
//  MitchellMaze.cpp
//  MazeGenerator
//
//  Created by Roshenac Mitchell on 18/10/2017.
//  Copyright © 2017 Roshenac Mitchell. All rights reserved.
//

#include "Maze.h"

Maze::Maze(const Maze& m)
{
    Maze(m.nRows(), m.nCols(), m.m_start, m.m_end);
}

// Get info about maze
// # rows
int Maze::nRows() const
{
    return m_numRows;
}

// # cols
int Maze::nCols() const
{
    return m_numColumns;
}

// checks to see wether the given row, column is a maze wall or empty
bool Maze::IsEmpty(int row, int column) const
{
    return not m_mazeMatrix[row][column];
}


void Maze::UpdateRobotLocs(const std::vector<point>& vp)
{
    // TODO
}


std::ostream& Maze::Display(std::ostream& os) const
{
    for (int row = 0; row < m_numRows; row++)
    {
        for (int column = 0; column < m_numColumns; column++)
        {
            if (row == m_start.r && column== m_start.c)
            {
                os <<  "..";
            }
            else if (row == m_end.r && column== m_end.c)
            {
                os <<  "XX";
            }else if (IsEmpty(row, column))
            {
                os <<  "  ";
            } else
            {
                os << "##";
            }
        }
        os<< std::endl;
    }
    os << "-------------------"  << std::endl;
    return os;
}


//overridden with my own version of GenerateMaze
void Maze::GenerateMaze(int nr, int nc, const point& start, const point& end)
{
    m_start = start;
    m_end = end;
    m_numRows = nr;
    m_numColumns = nc;
    
    // clear the vector of already visited points
    m_visitedPath.clear();
    
    initialiseMatrix(m_numRows, m_numColumns);
}

void Maze::initialiseMatrix(const int rowNumber, const int columnNumber)
{
    std::vector<bool> columnMatrix(columnNumber);
    std::vector<std::vector<bool> > rowColumnMatrix(rowNumber, columnMatrix);
    m_mazeMatrix = rowColumnMatrix;
    
    for (int row = 0; row < rowNumber; row++)
    {
        for (int column = 0; column < columnNumber; column++)
        {
            // Initialise all the points in the maze to be walls
            m_mazeMatrix[row][column] = 1;
        }
    }
    
    createBacktrackingMaze(m_end);
}

void Maze::createBacktrackingMaze(point& point)
{
    bool mazeGenerated = false;
    while (not mazeGenerated)
    {
        std::vector<Maze::point> validNeighbours= checkValidNeighbours(point.r, point.c);
        
        if (validNeighbours.size() > 0)
        {
            // chose a random valid neighbour
            int dir = rand() % (validNeighbours.size());
            Maze::point diff = validNeighbours[dir];
            markPointAsVisited(point.r, point.c, diff);
            Maze::point newPoint(point.r + diff.r, point.c + diff.c);
            // step to next point
            point = newPoint;
        }else
        {
            // if there are no valid neighbours
            if (m_visitedPath.size() > 1)
            {
                // backtrack to the last visited point
                m_visitedPath.pop_back();
                Maze::point previousPoint = m_visitedPath.back();
                point = previousPoint;
            }else
            {
                if (not reachedStartEnd())
                {
                    // If the start is surrounded by wall, knock down one neighouring wall
                    // so that the start point is part of the maze
                    m_mazeMatrix[m_start.r][m_start.c-1] = 0;
                }
                
                mazeGenerated = true;
            }
        }
    }
}


std::vector<Maze::point> Maze::checkValidNeighbours(const int row, const int column) const
{
    std::vector<point> neighbours =
    {Maze::point(-2, 0), Maze::point(2, 0), Maze::point(0, 2), Maze::point(0, -2)};
    
    std::vector<point> validNeighbours;
    
    for (auto const& point: neighbours)
    {
        int newRow = row + point.r;
        int newColumn = column + point.c;
        if (isValid(newRow, newColumn) && (m_mazeMatrix[newRow][newColumn] == 1))
        {
            validNeighbours.push_back(point);
        }
    }
    return validNeighbours;
}

void Maze::markPointAsVisited(const int row, const int column, const point& diff)
{
    int columnDiff = diff.c;
    int rowDiff = diff.r;
    
    while (columnDiff != 0 || rowDiff != 0)
    {
        m_mazeMatrix[row + rowDiff][column + columnDiff] = 0;
        if (columnDiff != 0 ){columnDiff = (diff.c < 0) ? (columnDiff +1 ) : (columnDiff - 1);}
        if (rowDiff != 0){rowDiff = (diff.r < 0) ? (rowDiff +1 ) : (rowDiff - 1);}
    }
    
    m_visitedPath.push_back(point(row + diff.r, column + diff.c));
}

// Check to make sure you can reach both start and end point
// by checking the start and end and its surrounding neighbours
bool Maze::reachedStartEnd() const
{
    bool reachedStart = false;
    bool reachedEnd = false;
    
    std::vector<point> neighbours =
    {point(-1, 0), point(1, 0), point(0, 1), point(0, -1), Maze::point(0, 0)};
    
    for (auto const& point: neighbours)
    {
        int newStartRow = m_start.r+ point.r;
        int newStartColumn = m_start.c + point.c;
        
        int newEndRow = m_end.r+ point.r;
        int newEndColumn = m_end.c + point.c;
        
        if (isValid(newStartRow, newStartColumn) &&
            (m_mazeMatrix[newStartRow][newStartColumn] == 0))
        {
            reachedStart = true;
        }
        
        if (isValid(newEndRow, newEndColumn) && (m_mazeMatrix[newEndRow][newEndColumn] == 0))
        {
            reachedEnd = true;
        }
    }
    
    return reachedStart  && reachedEnd;
}


//validators
bool Maze::validRow(const int column) const
{
    return column >=0 && column< m_numRows;
}

bool Maze::validColumn(const int column) const
{
    return column >=0 && column< m_numColumns;
}

bool Maze::isValid(const int row, const int column) const
{
    return validRow(row) && validColumn(column);
}


//regenerate a maze with new size nr, nc
// if no arguments are given, then use existing size
void Maze::Regenerate(int nr, int nc, const point& start, const point& end)
{
    GenerateMaze(nr, nc, start, end);
};
