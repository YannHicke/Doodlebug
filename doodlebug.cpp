/* check const in functions */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUM_DOODLEBUGS = 5;
const int NUM_ANTS = 100;
const int MAX_HEIGHT = 20;
const int MAX_WIDTH = 20;
char const ANT = 'A';
char const BUG = 'D';

class Organism;
class Doodlebug;
class Ant;

class World
{
public:
    World(int numDoodlebugs = NUM_DOODLEBUGS, int numAnts = NUM_ANTS);
    void next_step();
    void drawGrid();

    friend class Organism;
    friend class Doodlebug;
    friend class Ant;
private:
    Organism* grid[MAX_HEIGHT][MAX_WIDTH] = {nullptr};
};

class Organism
{
public:
    Organism(char a_type);
    char return_type();
    virtual void move(int i, int j, World a_world){};
    void breed(int i, int j, World a_world);

protected:
    char type;
    int breedingCounter;
};


class Doodlebug : public Organism
{
public:
    Doodlebug();
    virtual void move(int i, int j, World a_world);
    void starve(int i, int j, World a_world);

private:
    int starvingCounter;
};

class Ant : public Organism
{
public:
    Ant();
    virtual void move(int i, int j, World a_world);
};

int main()
{
    World newWorld;
    newWorld.drawGrid();

    cout<<"\nDo you want to watch the game?\nPress enter"<<endl;

    while(cin.get() == '\n')
    {
        newWorld.next_step();
    }

    return 0;
}

World::World(int numDoodlebugs, int numAnts)
{
    int doodlebugCounter(0), antCounter(0);
    srand(time(0));
    int isAlive;
    while(doodlebugCounter < numDoodlebugs)
    {
        for(int i = 0; i < MAX_HEIGHT; i++)
        {
            for(int j = 0; j < MAX_WIDTH; j++)
            {
                isAlive = (rand() % (MAX_WIDTH * MAX_HEIGHT));
                if((grid[i][j] == nullptr) && (isAlive < numDoodlebugs) && (doodlebugCounter < numDoodlebugs))
                {
                    grid[i][j] = new Doodlebug;
                    doodlebugCounter += 1;
                }
            }
            
        }
    }

    while(antCounter < numAnts)
    {
        for(int i = 0; i < MAX_HEIGHT; i++)
        {
            for(int j = 0; j < MAX_WIDTH; j++)
            {
                isAlive = (rand() % (MAX_WIDTH * MAX_HEIGHT));
                if((grid[i][j] == nullptr) && (isAlive < numAnts) && (antCounter < numAnts))
                {
                    grid[i][j] = new Ant;
                    antCounter += 1;
                }
            }
            
        }
    }


}

void World::drawGrid()
{
    cout<<endl;
    for(int i = 0; i < MAX_HEIGHT; i++)
    {
        for(int j = 0; j < MAX_WIDTH; j++)
        {
            if(grid[i][j] == nullptr)
            {
                cout<<YELLOW<<" -"<<RESET<<" |";
            }
            else if(grid[i][j] -> return_type() == 'D')
            {
                cout<<RED<<" X"<<RESET<<" |";
            }
            else
            {
                cout<<BOLDBLUE<<" o"<<RESET<<" |";
            }
        }
        cout<<endl<<endl;
    }
}

void World::next_step()
{
    for(int i = 0; i < MAX_HEIGHT; i++)
    {
        for(int j = 0; j < MAX_WIDTH; j++)
        {
            grid[i][j]->move(i,j, *this);
        }
    }
    drawGrid();
}


Organism::Organism(char a_type):breedingCounter(0),type(a_type)
{}

char Organism::return_type()
{
    return type;
}

void Organism::breed(int i, int j, World a_world)
{
    int directionVisited[4] = {0};
    int direction = (rand() % 4);
    // cout<<position<<" breed "<<direction<<endl;
    bool hasBred = false;
    bool moreToVisit = true;
    while((hasBred == false) && (moreToVisit == true))
    {
        direction = (rand() % 4);
        switch(direction)
        {
            
            case 0:
                if(directionVisited[0] == 1)
                {
                    break;
                }
                directionVisited[0] = 1;
                if((i <= 0) || (a_world.grid[i - 1][j] != nullptr))
                {
                    break;
                }
                else
                {
                    if(a_world.grid[i][j]->return_type() == BUG)
                    {
                        a_world.grid[i - 1][j] = new Doodlebug;
                    }
                    else
                    {
                        a_world.grid[i - 1][j] = new Ant;
                    }
                    
                }
            break;

            case 1:
                if(directionVisited[1] == 1)
                {
                    break;
                }
                directionVisited[1] = 1;
                if((j >= (MAX_WIDTH - 1)) || (a_world.grid[i][j + 1] != nullptr))
                {
                    break;
                }
                else
                {
                    if(a_world.grid[i][j]->return_type() == BUG)
                    {
                        a_world.grid[i][j + 1] = new Doodlebug;
                    }
                    else
                    {
                        a_world.grid[i][j + 1] = new Ant;
                    }
                }
            break;

            case 2:
                if(directionVisited[2] == 1)
                {
                    break;
                }
                directionVisited[2] = 1;
                if((i >= (MAX_HEIGHT - 1)) || (a_world.grid[i + 1][j] != nullptr))
                {
                    break;
                }
                else
                {
                    if(a_world.grid[i][j]->return_type() == BUG)
                    {
                        a_world.grid[i + 1][j] = new Doodlebug;
                    }
                    else
                    {
                        a_world.grid[i + 1][j] = new Ant;
                    }
                }
            break;

            case 3:
                if(directionVisited[3] == 1)
                {
                    break;
                }
                directionVisited[3] = 1;
                if((j <= 0) || (a_world.grid[i][j - 1] != nullptr))
                {
                    break;
                }
                else
                {
                    if(a_world.grid[i][j]->return_type() == BUG)
                    {
                        a_world.grid[i][j - 1] = new Doodlebug;
                    }
                    else
                    {
                        a_world.grid[i][j - 1] = new Ant;
                    }
                }
            break;

            default:
                cout<<"Error with rand function";
                exit(1);
        }

        moreToVisit = false;
        for(int i = 0; i < 4; i++)
        {
            if(directionVisited[i] == 0)
            {
                moreToVisit = true;
            }
        }
    }
}


Doodlebug::Doodlebug():Organism(BUG),starvingCounter(0)
{}

void Doodlebug::move(int i, int j, World a_world)
{
    bool isAntToEatUp = ((i > 0) && a_world.grid[i - 1][j]->return_type() == ANT);
    bool isAntToEatRight = ((j < (MAX_WIDTH - 1)) && a_world.grid[i][j + 1]->return_type() == ANT);
    bool isAntToEatDown = ((i < (MAX_HEIGHT -1)) && a_world.grid[i + 1][j]->return_type() == ANT);
    bool isAntToEatLeft = ((j > 0) && a_world.grid[i][j - 1]->return_type() == ANT);
    bool isAntToEat = (isAntToEatUp || isAntToEatRight || isAntToEatDown || isAntToEatLeft);
    

    int directionVisited[4] = {0};
    int direction;
    // cout<<position<<" breed "<<direction<<endl;
    bool hasEaten = false;
    bool moreToVisit = true;
    while(moreToVisit && !hasEaten)
    {
        direction = (rand() % 4);
        switch(direction)
        {
            case 0:
                if(directionVisited[0] == 1)
                {
                    break;
                }
                directionVisited[0] = 1;
                if(isAntToEat)
                {
                    if(isAntToEatUp)
                    {
                        delete a_world.grid[i - 1][j];
                        a_world.grid[i - 1][j] = a_world.grid[i][j];
                        a_world.grid[i][j] = nullptr;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if((i <= 0) || (a_world.grid[i - 1][j]->return_type() == BUG))
                    {
                        break;
                    }
                    else
                    {
                        a_world.grid[i - 1][j] = a_world.grid[i][j];
                        a_world.grid[i][j] = nullptr;
                    }
                }
            break;

            case 1:
                if(directionVisited[1] == 1)
                {
                    break;
                }
                directionVisited[1] = 1;
                if(isAntToEat)
                {
                    if(isAntToEatRight)
                    {
                        delete a_world.grid[i][j + 1];
                        a_world.grid[i][j + 1] = a_world.grid[i][j];
                        a_world.grid[i][j] = nullptr;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if((j >= (MAX_WIDTH - 1)) || (a_world.grid[i][j + 1]->return_type() == BUG))
                    {
                        break;
                    }
                    else
                    {
                        a_world.grid[i][j + 1] = a_world.grid[i][j];
                        a_world.grid[i][j] = nullptr;
                    }
                }
            break;

            case 2:
                if(directionVisited[2] == 1)
                {
                    break;
                }
                directionVisited[2] = 1;
                if(isAntToEat)
                {
                    if(isAntToEatDown)
                    {
                        delete a_world.grid[i + 1][j];
                        a_world.grid[i + 1][j] = a_world.grid[i][j];
                        a_world.grid[i][j] = nullptr;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if((i >= (MAX_HEIGHT - 1)) || (a_world.grid[i + 1][j]->return_type() == BUG))
                    {
                        break;
                    }
                    else
                    {
                        a_world.grid[i + 1][j] = a_world.grid[i][j];
                        a_world.grid[i][j] = nullptr;
                    }
                }
            break;

            case 3:
                if(directionVisited[3] == 1)
                {
                    break;
                }
                directionVisited[3] = 1;
                if(isAntToEat)
                {
                    if(isAntToEatLeft)
                    {
                        delete a_world.grid[i][j - 1];
                        a_world.grid[i][j - 1] = a_world.grid[i][j];
                        a_world.grid[i][j] = nullptr;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if((j <= 0) || (a_world.grid[i][j - 1]->return_type() == BUG))
                    {
                        break;
                    }
                    else
                    {
                        a_world.grid[i][j - 1] = a_world.grid[i][j];
                        a_world.grid[i][j] = nullptr;
                    }
                }
            break;

            default:
                cout<<"Error with function rand"<<endl;
                exit(1);
        }
        moreToVisit = false;
        for(int i = 0; i < 4; i++)
        {
            if(directionVisited[i] == 0)
            {
                moreToVisit = true;
            }
        }
    }

    breedingCounter++;
    starvingCounter++;
    if(breedingCounter == 8)
    {
        breed(i,j,a_world);
    }
    if(starvingCounter == 3)
    {
        starve(i,j,a_world);
    }
}

void Doodlebug::starve(int i, int j, World a_world)
{
    delete a_world.grid[i][j];
    a_world.grid[i][j] = nullptr;
}


Ant::Ant():Organism(ANT)
{}

void Ant::move(int i, int j, World a_world)
{
    int directionVisited[4] = {0};
    int direction;
    // cout<<position<<" breed "<<direction<<endl;
    bool moreToVisit = true;
    while(moreToVisit)
    {
        direction = (rand() % 4);
        switch(direction)
        {
            case 0:
                if(directionVisited[0] == 1)
                {
                    break;
                }
                directionVisited[0] = 1;
                if((i <= 0) || (a_world.grid[i - 1][j] != nullptr))
                {
                    break;
                }
                else
                {
                    a_world.grid[i - 1][j] = a_world.grid[i][j];
                    a_world.grid[i][j] = nullptr;
                }
            break;

            case 1:
                if(directionVisited[1] == 1)
                {
                    break;
                }
                directionVisited[1] = 1;
                if((j >= (MAX_WIDTH - 1)) || (a_world.grid[i][j + 1] != nullptr))
                {
                    break;
                }
                else
                {
                    a_world.grid[i][j + 1] = a_world.grid[i][j];
                    a_world.grid[i][j] = nullptr;
                }
            break;

            case 2:
                if(directionVisited[2] == 1)
                {
                    break;
                }
                directionVisited[2] = 1;
                if((i >= (MAX_HEIGHT - 1)) || (a_world.grid[i + 1][j] != nullptr))
                {
                    break;
                }
                else
                {
                    a_world.grid[i + 1][j] = a_world.grid[i][j];
                    a_world.grid[i][j] = nullptr;
                }
            break;

            case 3:
                if(directionVisited[3] == 1)
                {
                    break;
                }
                directionVisited[3] = 1;
                if((j <= 0) || (a_world.grid[i][j - 1] != nullptr))
                {
                    break;
                }
                else
                {
                    a_world.grid[i][j - 1] = a_world.grid[i][j];
                    a_world.grid[i][j] = nullptr;
                }
            break;

            default:
                cout<<"Error with rand function";
                exit(1);
        }

        moreToVisit = false;
        for(int i = 0; i < 4; i++)
        {
            if(directionVisited[i] == 0)
            {
                moreToVisit = true;
            }
        }
    }

    breedingCounter++;
    if(breedingCounter == 3)
    {
        breed(i,j,a_world);
    }
}