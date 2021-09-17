#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUM_DOODLEBUGS = 5;
const int NUM_ANTS = 100;
const int NUM_ROW_CELLS = 20;

class Organism
{
public:
    Organism();
    ~Organism();
    void operator=(const Oraganism& organism);
    void move(int position, Doodlebug d[], Ant a[], int positionsTaken[]);
    bool just_moved();
    void set_moved(bool b);
    char get_status();
    void set_status(char new_status);
    virtual void move(int position, Doodlebug d[], Ant a[], int positionsTaken[]);
    int get_breedingCounter();
    void set_breedingCounter(int num);
    virtual void breed(Doodlebug d[], Ant a[], int positionsTaken[], int position);

private:
    char status;
    int breedingCounter;
    bool justMoved;
};

class Doodlebug;

class Ant : public Organism
{
public:
    Ant();
    ~Ant();
    void operator=(const Ant& ant);
    //increases counters
    virtual void move(int position, Doodlebug d[], Ant a[], int positionsTaken[]);
    virtual void breed(Doodlebug d[], Ant a[], int positionsTaken[], int position);
};

class Doodlebug : public Organism
{
public:
    Doodlebug();
    ~Doodlebug();
    void operator=(const Doodlebug& doodlebug);
    //increases counters
    virtual void move(int position, Doodlebug d[], Ant a[], int positionsTaken[]);
    virtual void breed(Doodlebug d[], Ant a[], int positionsTaken[], int position);
    int get_starvingCounter();
    void set_starvingCounter(int num);
private:
    int starvingCounter;
};

void initializeMap(int numDoodlebugs, int numAnts, int numRowCells, Doodlebug d[], Ant a[], int positionsTaken[]);
void drawMap(int numRowCells, Doodlebug d[], Ant a[], int positionsTaken[]);
void nextStep(Doodlebug d[], Ant a[], int positionsTaken[]);
void change_Setup(Doodlebug d[], Ant a[], int positionsTaken[], int position, int new_position);
void change_Setup_Ant(Doodlebug d[], Ant a[], int positionsTaken[], int position, int new_position);


int main()
{
    Doodlebug d[NUM_ROW_CELLS * NUM_ROW_CELLS];
    Ant a[NUM_ROW_CELLS * NUM_ROW_CELLS];
    int positionsTaken[NUM_ROW_CELLS * NUM_ROW_CELLS] = {0};

    initializeMap(NUM_DOODLEBUGS, NUM_ANTS, NUM_ROW_CELLS, d, a, positionsTaken);

    cout<<"\nDo you want to watch the game?\nPress enter"<<endl;
    for(int i = 0; i < 30000; i++)
    {
        nextStep(d, a, positionsTaken);
    }
    int countDoodlebugs(0), countAnts(0);
    for(int i = 0; i < NUM_ROW_CELLS * NUM_ROW_CELLS; i++)
    {
        if(d[i].get_status() == 'A')
            countDoodlebugs++;
        if(a[i].get_status() == 'A')
            countAnts++;
    }
    cout<<"Doodlebugs: "<<countDoodlebugs<<endl;
    cout<<"Ants: "<<countAnts<<endl;

    while(cin.get() == '\n')
    {
        nextStep(d, a, positionsTaken);
    }

    return 0;
}

void nextStep(Doodlebug d[], Ant a[], int positionsTaken[])
{
    for(int i = 0; i < NUM_ROW_CELLS*NUM_ROW_CELLS; i++)
    {
        if((d[i].get_status() == 'A') && (d[i].just_moved() == false))
        {
            d[i].move(i, d, a, positionsTaken);
        }
    }

    for(int i = 0; i < NUM_ROW_CELLS*NUM_ROW_CELLS; i++)
    {
        if((a[i].get_status() == 'A') && (a[i].just_moved() == false))
        {
            a[i].move(i, d, a, positionsTaken);
        }
    }

    drawMap(NUM_ROW_CELLS, d, a, positionsTaken);

    for(int i = 0; i < NUM_ROW_CELLS*NUM_ROW_CELLS; i++)
    {
        d[i].set_moved(false);
        a[i].set_moved(false);
    }


}

void initializeMap(int numDoodlebugs, int numAnts, int numRowCells, Doodlebug d[], Ant a[], int positionsTaken[])
{
    
    int doodlebugCounter(0), antCounter(0);

    srand(time(0));
    int isAlive;
    while(doodlebugCounter < numDoodlebugs)
    {
        for(int i = 0; i < NUM_ROW_CELLS*NUM_ROW_CELLS; i++)
        {
            isAlive = (rand() % NUM_ROW_CELLS*NUM_ROW_CELLS);
            if((isAlive < numDoodlebugs) && (doodlebugCounter < numDoodlebugs))
            {
                cout<<i<<endl;
                d[i].set_status('A');
                doodlebugCounter += 1;
                positionsTaken[i] = 1;
            }
        }
    }
    while(antCounter < numAnts)
    {
        for(int i = 0; i < NUM_ROW_CELLS*NUM_ROW_CELLS; i++)
        {
            isAlive = (rand() % NUM_ROW_CELLS*NUM_ROW_CELLS);
            if((isAlive < numAnts) && (positionsTaken[i] == 0) && (antCounter < numAnts))
            {
                a[i].set_status('A');
                antCounter += 1;
                positionsTaken[i] = 1;
            }
        }
    }

    drawMap(numRowCells, d, a, positionsTaken);

}

void drawMap(int numRowCells, Doodlebug d[], Ant a[], int positionsTaken[])
{
    cout<<endl;
    for(int i = 0; i < numRowCells; i++)
    {
        for(int j = 0; j < numRowCells; j++)
        {
            if(positionsTaken[j + i*numRowCells] == 1)
            {
                if(d[j + i*numRowCells].get_status() == 'A')
                {
                    cout<<" X |";
                }
                else
                {
                    cout<<" o |";
                }
            }
            else
            {
                cout<<" - |";
            }
        }
        cout<<endl<<endl;
    }
}

void change_Setup(Doodlebug d[], Ant a[], int positionsTaken[], int position, int new_position)
{
    if(positionsTaken[new_position] == 1)
    {
        if(d[new_position].get_status() == 'A')
        {
            d[position] = d[position];
            if(d[position].get_breedingCounter() == 8)
            {
                d[position].breed(d, a, positionsTaken, position);
                d[position].set_breedingCounter(0);
            }
            if(d[position].get_starvingCounter() == 3)
            {
                d[position].~Doodlebug();
                positionsTaken[position] = 0;
            }
        }
        else
        {
            positionsTaken[position] = 0;
            d[new_position] = d[position];
            d[position].~Doodlebug();
            a[new_position].~Ant();
            d[new_position].set_starvingCounter(0);
            if(d[new_position].get_breedingCounter() == 8)
            {
                d[new_position].breed(d, a, positionsTaken, new_position);
                d[new_position].set_breedingCounter(0);
            }
        }
    }
    else
    {
        positionsTaken[position] = 0;
        d[new_position] = d[position];
        d[position].~Doodlebug();
        positionsTaken[new_position] = 1;
        if(d[new_position].get_breedingCounter() == 8)
        {
            d[new_position].breed(d, a, positionsTaken, new_position);
            d[new_position].set_breedingCounter(0);
        }
        if(d[new_position].get_starvingCounter() == 3)
        {
            d[new_position].~Doodlebug();
            positionsTaken[new_position] = 0;
        }
    }
}

void change_Setup_Ant(Doodlebug d[], Ant a[], int positionsTaken[], int position, int new_position)
{
    if(positionsTaken[new_position] == 1)
    {
        a[position] = a[position];
        if(a[position].get_breedingCounter() == 3)
        {
            a[position].breed(d, a, positionsTaken, position);
            a[position].set_breedingCounter(0);
        }
    }
    else
    {
        positionsTaken[position] = 0;
        a[new_position] = a[position];
        a[position].~Ant();
        positionsTaken[new_position] = 1;
        if(a[new_position].get_breedingCounter() == 3)
        {
            a[new_position].breed(d, a, positionsTaken, new_position);
            a[new_position].set_breedingCounter(0);
        }
    }
}

Organism::Organism()
{
    status = 'D';
    breedingCounter = 0;
    justMoved = false;
}

Organism::~Organism()
{

}

void Organism::get_status()
{
    return status;
}

void Organism::set_status(char new_status)
{
    status = new_status;
}

bool Organism::just_moved()
{
    return justMoved;
}

void Organism::set_moved(bool b)
{
    justMoved = b;
}

void Organism::set_breedingCounter(int num)
{
    breedingCounter = num;
}

void Organism::get_breedingCounter()
{
    return breedingCounter;
}


void Doodlebug::move(int position, Doodlebug d[], Ant a[], int positionsTaken[])
{
    //choose direction
    int direction = (rand() % 4);
    // cout<<position<<" "<<direction<<endl;
    switch(direction)
    {
        case 0:
            if(position - NUM_ROW_CELLS >= 0)
            {
                change_Setup(d, a, positionsTaken, position, (position - NUM_ROW_CELLS));
            }
            else
            {
                d[position] = d[position];
                if(d[position].get_breedingCounter() == 8)
                {
                    d[position].breed(d, a, positionsTaken, position);
                    d[position].set_breedingCounter(0);
                }
            }
        break;

        case 1:
            if(((position + 1) / NUM_ROW_CELLS) == (position / NUM_ROW_CELLS))
            {
                change_Setup(d, a, positionsTaken, position, (position + 1));
            }
            else
            {
                d[position] = d[position];
                if(d[position].get_breedingCounter() == 8)
                {
                    d[position].breed(d, a, positionsTaken, position);
                    d[position].set_breedingCounter(0);
                }
            }
        break;

        case 2:
            if(position + NUM_ROW_CELLS < (NUM_ROW_CELLS * NUM_ROW_CELLS))
            {
                change_Setup(d, a, positionsTaken, position, (position + NUM_ROW_CELLS));
            }
            else
            {
                d[position] = d[position];
                if(d[position].get_breedingCounter() == 8)
                {
                    d[position].breed(d, a, positionsTaken, position);
                    d[position].set_breedingCounter(0);
                }
            }
        break;

        case 3:
            if((position > 0) && (((position - 1) / NUM_ROW_CELLS) == (position / NUM_ROW_CELLS)))
            {
                change_Setup(d, a, positionsTaken, position, (position - 1));
            }
            else
            {
                d[position] = d[position];
                if(d[position].get_breedingCounter() == 8)
                {
                    d[position].breed(d, a, positionsTaken, position);
                    d[position].set_breedingCounter(0);
                }
            }
        break;

        default:
            cout<<"Error with function rand"<<endl;
            exit(1);
    }
}

void Ant::move(int position, Doodlebug d[], Ant a[], int positionsTaken[])
{
    //choose direction
    int direction = (rand() % 4);
    // cout<<position<<" "<<direction<<endl;
    switch(direction)
    {
        case 0:
            if(position - NUM_ROW_CELLS >= 0)
            {
                change_Setup_Ant(d, a, positionsTaken, position, (position - NUM_ROW_CELLS));
            }
            else
            {
                a[position] = a[position];
                if(a[position].get_breedingCounter() == 3)
                {
                    a[position].breed(d, a, positionsTaken, position);
                    a[position].set_breedingCounter(0);
                }
            }
        break;

        case 1:
            if(((position + 1) / NUM_ROW_CELLS) == (position / NUM_ROW_CELLS))
            {
                change_Setup_Ant(d, a, positionsTaken, position, (position + 1));
            }
            else
            {
                a[position] = a[position];
                if(a[position].get_breedingCounter() == 3)
                {
                    a[position].breed(d, a, positionsTaken, position);
                    a[position].set_breedingCounter(0);
                }
            }
        break;

        case 2:
            if(position + NUM_ROW_CELLS < (NUM_ROW_CELLS * NUM_ROW_CELLS))
            {
                change_Setup_Ant(d, a, positionsTaken, position, (position + NUM_ROW_CELLS));
            }
            else
            {
                a[position] = a[position];
                if(a[position].get_breedingCounter() == 3)
                {
                    a[position].breed(d, a, positionsTaken, position);
                    a[position].set_breedingCounter(0);
                }
            }
        break;

        case 3:
            if((position > 0) && (((position - 1) / NUM_ROW_CELLS) == (position / NUM_ROW_CELLS)))
            {
                change_Setup_Ant(d, a, positionsTaken, position, (position - 1));
            }
            else
            {
                a[position] = a[position];
                if(a[position].get_breedingCounter() == 3)
                {
                    a[position].breed(d, a, positionsTaken, position);
                    a[position].set_breedingCounter(0);
                }
            }
        break;

        default:
            cout<<"Error with function rand"<<endl;
            exit(1);
    }
}


Doodlebug::Doodlebug():Organism()
{
    starvingCounter = 0;
}

Ant::Ant():Organism()
{}


void Doodlebug::set_starvingCounter(int num)
{
    starvingCounter = num;
}

int Doodlebug::get_starvingCounter()
{
    return starvingCounter;
}



Doodlebug::~Doodlebug()
{
    Organism::~O
    status = 'D';
    breedingCounter = 0;
    starvingCounter = 0;
    justMoved = false;
}

void Doodlebug::operator=(const Doodlebug& doodlebug)
{
    status = doodlebug.status;
    breedingCounter = doodlebug.breedingCounter + 1;
    starvingCounter = doodlebug.starvingCounter + 1;
    justMoved = true;
}

void Ant::operator=(const Ant& ant)
{
    status = ant.status;
    breedingCounter = ant.breedingCounter + 1;
    justMoved = true;
}
Ant::~Ant()
{
    status = 'D';
    breedingCounter = 0;
    justMoved = false;
}

void Doodlebug::breed(Doodlebug d[], Ant a[], int positionsTaken[], int position)
{
    int directionVisited[4] = {0};
    int direction = (rand() % 4);
    // cout<<position<<" breed "<<direction<<endl;
    bool hasBred = false;
    bool moreToVisit = true;
    while((hasBred == false) && (moreToVisit == true))
    {
        moreToVisit = false;
        for(int i = 0; i < 4; i++)
        {
            if(directionVisited[i] == 0)
            {
                moreToVisit = true;
            }
        }

        direction = (rand() % 4);
        switch(direction)
        {
            
            case 0:
                directionVisited[0] = 1;
                if(position - NUM_ROW_CELLS > 0)
                {
                    if(positionsTaken[position - NUM_ROW_CELLS] == 1)
                    {
                        break;
                    }
                    else
                    {
                        d[position - NUM_ROW_CELLS].set_status('A');
                        d[position - NUM_ROW_CELLS].set_moved(true);
                        positionsTaken[position - NUM_ROW_CELLS] = 1;
                        hasBred = true;
                    }
                }
            break;

            case 1:
                directionVisited[1] = 1;
                if(((position + 1) / NUM_ROW_CELLS) == (position / NUM_ROW_CELLS))
                {
                    if(positionsTaken[position + 1] == 1)
                    {
                        break;
                    }
                    else
                    {
                        d[position + 1].set_status('A');
                        d[position + 1].set_moved(true);
                        positionsTaken[position + 1] = 1;
                        hasBred = true;
                    }
                }
            break;

            case 2:
                directionVisited[2] = 1;
                if(position + NUM_ROW_CELLS < (NUM_ROW_CELLS * NUM_ROW_CELLS))
                {
                    if(positionsTaken[position + NUM_ROW_CELLS] == 1)
                    {
                        break;
                    }
                    else
                    {
                        d[position + NUM_ROW_CELLS].set_status('A');
                        d[position + NUM_ROW_CELLS].set_moved(true);
                        positionsTaken[position + NUM_ROW_CELLS] = 1;
                        hasBred = true;
                    }
                }
            break;

            case 3:
                directionVisited[3] = 1;
                if((position > 0) && (((position - 1) / NUM_ROW_CELLS) == (position / NUM_ROW_CELLS)))
                {
                    if(positionsTaken[position - 1] == 1)
                    {
                        break;
                    }
                    else
                    {
                        d[position - 1].set_status('A');
                        d[position - 1].set_moved(true);
                        positionsTaken[position - 1] = 1;
                        hasBred = true;
                    }
                }
            break;

            default:
                cout<<"Error with function rand"<<endl;
                exit(1);
        }
    }
}

void Ant::breed(Doodlebug d[], Ant a[], int positionsTaken[], int position)
{
    int directionVisited[4] = {0};
    int direction;
    bool hasBred = false;
    bool moreToVisit = true;
    while((hasBred == false) && (moreToVisit == true))
    {
        moreToVisit = false;
        for(int i = 0; i < 4; i++)
        {
            if(directionVisited[i] == 0)
            {
                moreToVisit = true;
            }
        }

        direction = (rand() % 4);
        // cout<<position<<" breed "<<direction<<endl;
        switch(direction)
        {
            case 0:
                directionVisited[0] = 1;
                if(position - NUM_ROW_CELLS > 0)
                {
                    if(positionsTaken[position - NUM_ROW_CELLS] == 1)
                    {
                        break;
                    }
                    else
                    {
                        a[position - NUM_ROW_CELLS].set_status('A');
                        a[position - NUM_ROW_CELLS].set_moved(true);
                        positionsTaken[position - NUM_ROW_CELLS] = 1;
                        hasBred = true;
                    }
                }
            break;

            case 1:
                directionVisited[1] = 1;
                if(((position + 1) / NUM_ROW_CELLS) == (position / NUM_ROW_CELLS))
                {
                    if(positionsTaken[position + 1] == 1)
                    {
                        break;
                    }
                    else
                    {
                        a[position + 1].set_status('A');
                        a[position + 1].set_moved(true);
                        positionsTaken[position + 1] = 1;
                        hasBred = true;
                    }
                }
            break;

            case 2:
                directionVisited[2] = 1;
                if(position + NUM_ROW_CELLS < (NUM_ROW_CELLS * NUM_ROW_CELLS))
                {
                    if(positionsTaken[position + NUM_ROW_CELLS] == 1)
                    {
                        break;
                    }
                    else
                    {
                        a[position + NUM_ROW_CELLS].set_status('A');
                        a[position + NUM_ROW_CELLS].set_moved(true);
                        positionsTaken[position + NUM_ROW_CELLS] = 1;
                        hasBred = true;
                    }
                }
            break;

            case 3:
                directionVisited[3] = 1;
                if((position > 0) && (((position - 1) / NUM_ROW_CELLS) == (position / NUM_ROW_CELLS)))
                {
                    if(positionsTaken[position - 1] == 1)
                    {
                        break;
                    }
                    else
                    {
                        a[position - 1].set_status('A');
                        a[position - 1].set_moved(true);
                        positionsTaken[position - 1] = 1;
                        hasBred = true;
                    }
                }
            break;

            default:
                cout<<"Error with function rand"<<endl;
                exit(1);
        }
    }
}