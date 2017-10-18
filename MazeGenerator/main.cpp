#include "MitchellMaze.h"

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    int MazeGridSize(30) ; // maze will be MazeGridSize x MazeGridSize
    int numMazes(1);

    Maze::point start(rand()%MazeGridSize, rand()%MazeGridSize), end(rand()%MazeGridSize, rand()%MazeGridSize) ; // random start and end locations

    for(int i = 0; i< 2000; i++){
    std::vector<Maze*> Ms(numMazes);
       Ms[0] = new MitchellMaze(MazeGridSize, MazeGridSize, start, end);

    // comment out one of the following
    std::ostream& os(std::cout) ; // option 1. prints to screen
    
    // ofstream os("roshenacMaze.txt") ; // option 2. prints to file
    
    Ms[0]->Display(os) ;
    }
   return 0;
}
