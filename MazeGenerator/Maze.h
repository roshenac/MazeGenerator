//
// This code was provided as part of my course works
//

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <iostream>
#include <vector>

class Robot ;

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

        Maze(int nr, int nc, const point& start, const point& end) : _st(start), _end(end)  // create a Maze with nr rows and nc columns
        {
            GenerateMaze(nr,nc,start,end) ;
        }


        ~Maze() {}

        //regenerate a maze with new size nr, nc
        // if no arguments are given, then use existing size
        virtual void Regenerate(int nr, int nc, const point& start, const point& end) = 0 ;

        // Get info about maze
        virtual int nRows() const = 0 ; // return # rows
        virtual int nCols() const = 0; // return # cols
        virtual bool IsEmpty(int i, int j) const = 0; // returns true if maze has no obstacle at (i,j) else return false


    virtual void UpdateRobotLocs(const std::vector<point>& vp) = 0; // copy points in vp to _robotLocs

        virtual std::ostream&  Display(std::ostream& os) const = 0 ;


    protected:
        // 2D array of booleans (true implies obstacle, false implies valid robot location)
    std::vector< std::vector<bool> > _mat;
        point _st, _end; // source and target destinations within maze
    std::vector<point> _robotLocs ; // vector of robot locations (for display purposes)

        // generate a maze which has no obstacles
        virtual void GenerateMaze(int nr, int nc, const point& start, const point& end)
        {
            std::vector<bool> dummy(nc,false) ;
            for (int i(0);i<nr; i++)
                _mat.push_back(dummy) ;
        }

};

// overload the stream insertion operator so we can cout << MazeObject
inline std::ostream& operator << (std::ostream& os, const Maze& M)
{
    return M.Display(os) ;
}


#endif // MAZE
