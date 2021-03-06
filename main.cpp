//
//  main.cpp
//  Explore Mars CLI Game
//
//  Created by Mohammad Shahdad on 2/9/19.
//  Copyright © 2019 Mohammad Shahdad. All rights reserved.
//


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

const char HILL = '$', TRAP = '#', GOLD = '*', HIDDEN = '?', TRAPPED = '@';

enum Direction
{
    north = 0,
    east = 1,
    west = 2,
    south = 3
};

class Map
{
private:
    vector < vector<char> > map;
    int dimX, dimY, roverX, roverY;
    char objectUnderRover;
    Direction heading;
public:
    Map()
    {
        dimX = 0;
        dimY = 0;
        roverX = 0;
        roverY = 0;
    }
    Map(int dimx, int dimy)
    {
        dimX = dimx;
        dimY = dimy;
        roverX = dimx/2;
        roverY = dimy/2;
        init();
    }
    void init()
    {
        const int noOfObjects = 10;  //number of objects in the objects array
        char objects[noOfObjects] = {' ', ' ', ' ', ' ', ' ', ' ',
            HILL, HILL, TRAP, TRAP };

        //create dynamic 2D array using vector
        map.resize(dimY);        //create rows
        for (int i=0; i<dimY; ++i)
        {
            map[i].resize(dimX);  //resize each rows
        }

        //put random chars into the vector array

        unsigned int seed = static_cast<unsigned int>(time(NULL));
        srand(seed);        // seed needs to be set only once in the entire program

        for (int i=0; i<dimY; ++i)
        {
            for (int j=0; j<dimX; ++j)
            {
                int objNo = rand() % noOfObjects;
                map[i][j] =  objects[objNo];
            }
        }
    }

    void populateGold(int quantity)
    {
        roverX = dimY/2;
        roverY = dimX/2;
        int goldDeployed = 0;
        map[roverX][roverY] = ' ';  // sets center of map to be empty
        do {
            const int SIZE = 4;
            Direction directions[SIZE] = {north, east, west, south};

            int dir = rand() % SIZE;
            heading = directions[dir];
            int randNum = rand() % 10;
            if (randNum == 0 || randNum == 1)
            {
                turnRight();
            }
            else if (randNum == 8 || randNum == 9)
            {
                turnLeft();
            }
            else
            {
                move();
                int randNumGold = rand() % 10;
                if (randNumGold == 0)
                {
                    if (objectUnderRover != GOLD)
                    {
                        map[roverX][roverY] = GOLD;
                        goldDeployed++;
                    }
                }
            }
        } while(goldDeployed<quantity);
    }

    void turnLeft()
    {
        switch (heading) {
            case north:
                heading = west;
                break;
            case east:
                heading = north;
                break;
            case west:
                heading = south;
                break;
            case south:
                heading = east;
                break;
        }
    }
    void turnRight()
    {
        switch (heading) {
            case north:
                heading = east;
                break;
            case east:
                heading = south;
                break;
            case west:
                heading = north;
                break;
            case south:
                heading = west;
                break;
        }
    }

    void move()
    {
        switch (heading) {
            case north:
                if (isInsideMap(roverX-1, roverY))
                {
                    roverX-=1;
                    objectUnderRover = map[roverX][roverY];
                    if (objectUnderRover != GOLD)
                    {
                        map[roverX][roverY] = ' ';
                    }
                }
                else
                {
                    heading = south;
                }
                break;
            case east:
                if (isInsideMap(roverX, roverY+1))
                {
                    roverY+=1;
                    objectUnderRover = map[roverX][roverY];
                    if (objectUnderRover != GOLD)
                    {
                        map[roverX][roverY] = ' ';
                    }
                }
                else
                {
                    heading = west;
                }
                break;
            case west:
                if (isInsideMap(roverX, roverY-1))
                {
                    roverY-=1;
                    objectUnderRover = map[roverX][roverY];
                    if (objectUnderRover != GOLD)
                    {
                        map[roverX][roverY] = ' ';
                    }
                }
                else
                {
                    heading = east;
                }
                break;
            case south:
                if (isInsideMap(roverX+1, roverY))
                {
                    roverX+=1;
                    objectUnderRover = map[roverX][roverY];
                    if (objectUnderRover != GOLD)
                    {
                        map[roverX][roverY] = ' ';
                    }
                }
                else
                {
                    heading = north;
                }
                break;
        }
    }

    void resize(int dimx, int dimy, char ch)
    {
        dimX = dimx;
        dimY = dimy;
        map.resize(dimy);        //create rows
        for (int i=0; i<dimy; ++i)
        {
            map[i].resize(dimx);  //resize each rows
        }
        for (int i=0; i<dimy; ++i)
        {
            for (int j=0; j<dimx; ++j)
            {
                map[i][j] = ch;
            }
        }
    }


    void display()
    {
        cout << "\n  --__--__--Welcome to Mars!--__--__--" << endl;

        for (int i=0; i<dimY; ++i)
        {
            cout << "  ";
            for (int j=0; j<dimX; ++j)
            {
                cout << "+-";
            }
            cout << "+" << endl;
            cout << setw(2) << (dimY-i);
            for (int j=0; j<dimX; ++j)
            {
                cout << "|" << map[i][j];
            }
            cout << "|" << endl;
        }

        cout << "  ";
        for (int j=0; j<dimX; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        cout << "  ";
        for (int j=0; j<dimX; ++j)
        {
            int digit = (j+1)/10;
            cout << " ";
            if (digit==0)
                cout << " ";
            else
                cout << digit;
        }
        cout << endl;
        cout << "  ";
        for (int j=0; j<dimX; ++j)
        {
            cout << " " << (j+1)%10;
        }
        cout << endl << endl;
    }
    void setObject(int x, int y, char ch)
    {
        map[x][y] = ch;
    }
    char getObject(int x, int y)
    {
        char object = map[x][y];
        return object;
    }
    bool isEmpty(int x, int y)
    {
        if(getObject(x, y) == ' ')
        {
            return true;
        }
        else
            return false;
    }
    bool isHill(int x, int y)
    {
        if(getObject(x, y) == HILL)
        {
            return true;
        }
        else
            return false;
    }
    bool isTrap(int x, int y)
    {
        if(getObject(x, y) == TRAP)
        {
            return true;
        }
        else
            return false;
    }
    bool isGold(int x, int y)
    {
        if (getObject(x, y) == GOLD) {
            return true;
        }
        else
            return false;
    }
    bool isInsideMap(int x, int y)
    {
        if ((x>=0 && x<dimY) && (y>=0 && y<dimX))
        {
            return true;
        }
        else
            return false;
    }
    int getDimX()
    {
        return dimX;
    }
    int getDimY()
    {
        return dimY;
    }
}; //Map

class Rover
{
private:
    int x, y, goldCollected = 0;
    bool quit = false;
    Direction heading;
    char objectUnderRover;
    Map* ptrToMars; //a pointer to the map for Mars
    Map mapper; //a map that keeps track of observed cells so far
public:
    Rover()
    {
    }

    void land(Map& mars) //links a map of Mars to a Rover
    {
        int dimX = mars.getDimX(), dimY = mars.getDimY();
        ptrToMars = &mars;
        mapper.resize(dimX, dimY, HIDDEN);
        x = dimX/2;
        y = dimY/2;

        const int SIZE = 4;
        Direction directions[SIZE] = {north, east, west, south};

        int dir = rand() % SIZE;
        heading = directions[dir];

        switch (heading) {
            case north:
                mapper.setObject(y, x, '^');
                unhideNearbyObj();
                break;
            case east:
                mapper.setObject(y, x, '>');
                unhideNearbyObj();
                break;
            case west:
                mapper.setObject(y, x, '<');
                unhideNearbyObj();
                break;
            case south:
                mapper.setObject(y, x, 'v');
                unhideNearbyObj();
                break;
        }
    }

    Map* getPtrToMars()
    {
        return ptrToMars;
    }

    int getGoldCollected()
    {
        return goldCollected;
    }

    void setGoldCollected(int no)
    {
        goldCollected = no;
    }

    char getObjUnderRover()
    {
        return objectUnderRover;
    }

    void setObjUnderRover(char obj)
    {
        objectUnderRover = obj;
    }

    bool getQuitVal()
    {
        return quit;
    }

    void unhideNearbyObj() {
        switch (heading) {
            case north:
                if(mapper.isInsideMap(y-1, x))
                {
                    mapper.setObject(y-1, x, ptrToMars->getObject(y-1, x));
                }
                if(mapper.isInsideMap(y-1, x-1))
                {
                    mapper.setObject(y-1, x-1, ptrToMars->getObject(y-1, x-1));
                }
                if(mapper.isInsideMap(y-1, x+1))
                {
                    mapper.setObject(y-1, x+1, ptrToMars->getObject(y-1, x+1));
                }
                break;
            case east:
                if(mapper.isInsideMap(y, x+1))
                {
                    mapper.setObject(y, x+1, ptrToMars->getObject(y, x+1));
                }
                if(mapper.isInsideMap(y-1, x+1))
                {
                    mapper.setObject(y-1, x+1, ptrToMars->getObject(y-1, x+1));
                }
                if(mapper.isInsideMap(y+1, x+1))
                {
                    mapper.setObject(y+1, x+1, ptrToMars->getObject(y+1, x+1));
                }
                break;
            case west:
                if(mapper.isInsideMap(y, x-1))
                {
                    mapper.setObject(y, x-1, ptrToMars->getObject(y, x-1));
                }
                if(mapper.isInsideMap(y-1, x-1))
                {
                    mapper.setObject(y-1, x-1, ptrToMars->getObject(y-1, x-1));
                }
                if(mapper.isInsideMap(y+1, x-1))
                {
                    mapper.setObject(y+1, x-1, ptrToMars->getObject(y+1, x-1));
                }
                break;
            case south:
                if(mapper.isInsideMap(y+1, x))
                {
                    mapper.setObject(y+1, x, ptrToMars->getObject(y+1, x));
                }
                if(mapper.isInsideMap(y+1, x-1))
                {
                    mapper.setObject(y+1, x-1, ptrToMars->getObject(y+1, x-1));
                }
                if(mapper.isInsideMap(y+1, x+1))
                {
                    mapper.setObject(y+1, x+1, ptrToMars->getObject(y+1, x+1));
                }
                break;
        }
    }

    bool turnLeft()
    {
        switch (heading) {
            case north:
                mapper.setObject(y, x, '<');
                heading = west;
                unhideNearbyObj();
                break;
            case east:
                mapper.setObject(y, x, '^');
                heading = north;
                unhideNearbyObj();
                break;
            case west:
                mapper.setObject(y, x, 'v');
                heading = south;
                unhideNearbyObj();
                break;
            case south:
                mapper.setObject(y, x, '>');
                heading = east;
                unhideNearbyObj();
                break;
        }
        return true;
    }
    bool turnRight()
    {
        switch (heading) {
            case north:
                mapper.setObject(y, x, '>');
                heading = east;
                unhideNearbyObj();
                break;
            case east:
                mapper.setObject(y, x, 'v');
                heading = south;
                unhideNearbyObj();
                break;
            case west:
                mapper.setObject(y, x, '^');
                heading = north;
                unhideNearbyObj();
                break;
            case south:
                mapper.setObject(y, x, '<');
                heading = west;
                unhideNearbyObj();
                break;
        }
        return true;
    }
    bool move()
    {
        switch (heading) {
            case north:
                if ((mapper.isInsideMap(y-1, x)) && (mapper.isEmpty(y-1, x)==true))
                {
                    mapper.setObject(y, x, ' ');
                    y-=1;
                    objectUnderRover = mapper.getObject(y, x);
                    mapper.setObject(y, x, '^');
                    unhideNearbyObj();
                    return true;
                }
                else if ((mapper.isInsideMap(y-1, x)) && (mapper.isTrap(y-1, x)==true))
                {
                    mapper.setObject(y, x, ' ');
                    y-=1;
                    objectUnderRover = mapper.getObject(y, x);
                    mapper.setObject(y, x, TRAPPED);
                    unhideNearbyObj();
                    return true;
                }
                else if ((mapper.isInsideMap(y-1, x)) && (mapper.isGold(y-1, x)==true))
                {
                    mapper.setObject(y, x, ' ');
                    y-=1;
                    objectUnderRover = mapper.getObject(y, x);
                    goldCollected++;
                    mapper.setObject(y, x, '^');
                    ptrToMars->setObject(y, x, ' ');
                    unhideNearbyObj();
                    return true;
                }
                else
                    return false;
                break;
            case east:
                if ((mapper.isInsideMap(y, x+1)) && (mapper.isEmpty(y, x+1)==true))
                {
                    mapper.setObject(y, x, ' ');
                    x+=1;
                    objectUnderRover = mapper.getObject(y, x);
                    mapper.setObject(y, x, '>');
                    unhideNearbyObj();
                    return true;
                }
                else if ((mapper.isInsideMap(y, x+1)) && (mapper.isTrap(y, x+1)==true))
                {
                    mapper.setObject(y, x, ' ');
                    x+=1;
                    objectUnderRover = mapper.getObject(y, x);
                    mapper.setObject(y, x, TRAPPED);
                    unhideNearbyObj();
                    return true;
                }
                else if ((mapper.isInsideMap(y, x+1)) && (mapper.isGold(y, x+1)==true))
                {
                    mapper.setObject(y, x, ' ');
                    x+=1;
                    objectUnderRover = mapper.getObject(y, x);
                    goldCollected++;
                    mapper.setObject(y, x, '>');
                    ptrToMars->setObject(y, x, ' ');
                    unhideNearbyObj();
                    return true;
                }
                else
                    return false;
                break;
            case west:
                if ((mapper.isInsideMap(y, x-1)) && (mapper.isEmpty(y, x-1)==true))
                {
                    mapper.setObject(y, x, ' ');
                    x-=1;
                    objectUnderRover = mapper.getObject(y, x);
                    mapper.setObject(y, x, '<');
                    unhideNearbyObj();
                    return true;
                }
                else if ((mapper.isInsideMap(y, x-1)) && (mapper.isTrap(y, x-1)==true))
                {
                    mapper.setObject(y, x, ' ');
                    x-=1;
                    objectUnderRover = mapper.getObject(y, x);
                    mapper.setObject(y, x, TRAPPED);
                    unhideNearbyObj();
                    return true;
                }
                else if ((mapper.isInsideMap(y, x-1)) && (mapper.isGold(y, x-1)==true))
                {
                    mapper.setObject(y, x, ' ');
                    x-=1;
                    objectUnderRover = mapper.getObject(y, x);
                    goldCollected++;
                    mapper.setObject(y, x, '<');
                    ptrToMars->setObject(y, x, ' ');
                    unhideNearbyObj();
                    return true;
                }
                else
                    return false;
                break;
            case south:
                if ((mapper.isInsideMap(y+1, x)) && (mapper.isEmpty(y+1, x)==true))
                {
                    mapper.setObject(y, x, ' ');
                    y+=1;
                    objectUnderRover = mapper.getObject(y, x);
                    mapper.setObject(y, x, 'v');
                    unhideNearbyObj();
                    return true;
                }
                else if ((mapper.isInsideMap(y+1, x)) && (mapper.isTrap(y+1, x)==true))
                {
                    mapper.setObject(y, x, ' ');
                    y+=1;
                    objectUnderRover = mapper.getObject(y, x);
                    mapper.setObject(y, x, TRAPPED);
                    unhideNearbyObj();
                    return true;
                }
                else if ((mapper.isInsideMap(y+1, x)) && (mapper.isGold(y+1, x)==true))
                {
                    mapper.setObject(y, x, ' ');
                    y+=1;
                    objectUnderRover = mapper.getObject(y, x);
                    goldCollected++;
                    mapper.setObject(y, x, 'v');
                    ptrToMars->setObject(y, x, ' ');
                    unhideNearbyObj();
                    return true;
                }
                else
                    return false;
                break;
        }
    }
    void displayMapper()
    {
        int dimX = mapper.getDimX(), dimY = mapper.getDimY();
        cout << "\n  --__--__--Mars Rover Mapper--__--__--" << endl;

        for (int i=0; i<dimY; ++i)
        {
            cout << "  ";
            for (int j=0; j<dimX; ++j)
            {
                cout << "+-";
            }
            cout << "+" << endl;
            cout << setw(2) << (dimY-i);
            for (int j=0; j<dimX; ++j)
            {
                cout << "|" << mapper.getObject(i, j);
            }
            cout << "|" << endl;
        }

        cout << "  ";
        for (int j=0; j<dimX; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        cout << "  ";
        for (int j=0; j<dimX; ++j)
        {
            int digit = (j+1)/10;
            cout << " ";
            if (digit==0)
                cout << " ";
            else
                cout << digit;
        }
        cout << endl;
        cout << "  ";
        for (int j=0; j<dimX; ++j)
        {
            cout << " " << (j+1)%10;
        }
        cout << endl << endl;
    }
    bool executeCommand(char command) {
        bool success;
        if (command == 'M')
        {
            success = move();
            return success;
        }
        else if (command == 'R')
        {
            success = turnRight();
            return success;
        }
        else if (command == 'L')
        {
            success = turnLeft();
            return success;
        }
        else if (command == 'Q')
        {
            quit = true;
            return true;
        }
        else
            return false;
    }
}; //Rover

void menu();
void score(int, int, int, int);
void enterCSeq(Rover&, int*, int*, int*, char*);


int main()
{
    char again = 'Y';
    char *ptrToAgain = &again;
    do
    {
        int dimx, dimy, noOfGold, commandSScore = 0, totalCommands = 0;
        int *ptrToNoOfGold = &noOfGold, *ptrToCSScore = &commandSScore, *ptrToTotalCommands = &totalCommands;
        cout << "Let's explore Mars..." << endl;
        cout << "Mars Dimension X => ";
        cin >> dimx;
        while (dimx<1 || dimx>30) {
            cout << "Please enter an integer between 1-30" << endl;
            cout << "Mars Dimension X => ";
            cin >> dimx;
        }
        cout << "Mars Dimension Y => ";
        cin >> dimy;
        while (dimy<1 || dimy>30) {
            cout << "Please enter an integer between 1-30" << endl;
            cout << "Mars Dimension Y => ";
            cin >> dimy;
        }
        cout << "No of Golds => ";
        cin >> noOfGold;
        while (noOfGold<1 || noOfGold>10) {
            cout << "Please enter an integer between 1-10" << endl;
            cout << "No of Golds => ";
            cin >> noOfGold;
        }
        Map mars(dimx, dimy);
        mars.populateGold(noOfGold);
        Rover curiosity;
        curiosity.land(mars);
        do
        {
            curiosity.displayMapper();
            menu();
            score(commandSScore, totalCommands, curiosity.getGoldCollected(), noOfGold);
            enterCSeq(curiosity, ptrToNoOfGold, ptrToCSScore, ptrToTotalCommands, ptrToAgain);
        } while (again == 'Y' || again == 'y');
        cout << "Do you want to explore Mars again? => ";
        cin >> again;
    } while (again == 'Y' || again == 'y');
    cout << "\nGood Bye from Mars!" << endl;
    return 0;

}

void menu()
{
    cout << "\nMission: Get all the golds!!, Do not get trapped!!" << endl;
    cout << "L=Turn Left, R=Turn Right, M=Move, Q=Quit" << endl;
    cout << HILL << "=Hill " << TRAP << "=Trap " << GOLD << "=Gold" << endl;
}

void score(int cScore, int commands, int gCollected, int totalGold)
{
    int totalScore = gCollected*50-cScore*5-commands*1;
    cout << "\nTotal Command Sequences = " << cScore << " [S]" << endl;
    cout << "Total Commands = " << commands << " [C]" << endl;
    cout << "Total Golds = " << gCollected << " [G] out of " << totalGold << endl;
    cout << "Total Score = [G] x 50 - [S] x 5 - [C] x 1 = " << totalScore << endl;
}

void enterCSeq(Rover& curiosity, int* noOfGold, int* commandSScore, int* totalCommands, char* again)
{
    if (curiosity.getObjUnderRover() != TRAP && curiosity.getGoldCollected() < *noOfGold && curiosity.getQuitVal() == false)
    {
        cout << "\nExample Sequence: MMLMMMRMMRMRMLLL" << endl;
        cout << "Enter command sequence => ";
        string commandSequence;
        getline(cin >> ws, commandSequence);
        *commandSScore = *commandSScore+1;

        int len = static_cast<int>(commandSequence.length());
        *totalCommands += commandSequence.length();

        for (int i=0; i<len; ++i)
        {
            char command = commandSequence[i];
            command = toupper(command);   //convert to upper case

            curiosity.displayMapper();
            cout << "Command = " << command << " ..." << endl;

            bool success = curiosity.executeCommand(command);

            curiosity.displayMapper();
            cout << "Command = " << command;
            if (success)
                cout << " [executed]" << endl;
            else
                cout << " [failed to execute]" << endl;
        }
    }
    else if (curiosity.getGoldCollected() == *noOfGold)
    {
        cout << "\nCongratz, Mission ACCOMPLISHED!!" << endl;
        cout << "\nDo you want to see the Map of Mars? (Y / N) => ";
        char seeMapMars;
        cin >> seeMapMars;
        if (seeMapMars == 'Y' || seeMapMars == 'y') {
            curiosity.getPtrToMars()->display();
        }
        *again = 'N';
        curiosity.setObjUnderRover(' ');
        curiosity.setGoldCollected(0);
    }
    else if (curiosity.getObjUnderRover() == TRAP)
    {
        cout << "\nTRAPPED, Mission FAILED!!" << endl;
        cout << "\nDo you want to see the Map of Mars? (Y / N) => ";
        char seeMapMars;
        cin >> seeMapMars;
        if (seeMapMars == 'Y' || seeMapMars == 'y') {
            curiosity.getPtrToMars()->display();
        }
        *again = 'N';
        curiosity.setObjUnderRover(' ');
        curiosity.setGoldCollected(0);
    }
    else if (curiosity.getQuitVal() == true)
    {
        cout << "\nQUITTED, Mission FAILED!!" << endl;
        cout << "\nDo you want to see the Map of Mars? (Y / N) => ";
        char seeMapMars;
        cin >> seeMapMars;
        if (seeMapMars == 'Y' || seeMapMars == 'y') {
            curiosity.getPtrToMars()->display();
        }
        *again = 'N';
        curiosity.setObjUnderRover(' ');
        curiosity.setGoldCollected(0);
    }
}
