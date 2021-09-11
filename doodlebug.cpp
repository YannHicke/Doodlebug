#include <iostream>
using namespace std;

const int NUM_DOODLEBUGS = 5;
const int NUM_ANTS = 100;
const int NUM_ROW_CELLS = 20;

class Organism
{

};

class Ant : public Organism
{

};

class Doodlebug : public Organism
{

};

void initializeMap(int numDoodlebugs, int numAnts, int numRowCells);
void nextStep();

int main()
{
    initializeMap(NUM_DOODLEBUGS, NUM_ANTS, NUM_ROW_CELLS);

    cout<<"Do you want to watch the game?\nPress enter"<<endl;
    while(cin.get() == '\n')
    {
        nextStep();
    }

    return 0;
}

void nextStep()
{
    cout<<"1";
}

void initializeMap(int numDoodlebugs, int numAnts, int numRowCells)
{}