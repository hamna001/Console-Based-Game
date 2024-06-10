#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;
//for coloring
HANDLE acolor = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void readmazefromfile();
// start game
void startPage();
void WelcomeScreen();
int MainMenuScreen();
void Game();
// end game
void GameOver();
// winning page
void GameWon();
// maze

char maze[49][156];

//
void Instructions();

void printMaze();
// fireboy
void printFireboy();
void eraseFireboy();
void moveFireboyRight();
void moveFireboyLeft();
void moveFireboyUp();
void moveFireboyDown();
// bullets of fireBoy right direction
void generateBullet();
void moveBullet();
void printBullet(int x, int y);
void eraseBullet(int x, int y);
void makeBulletInactive(int idx);
// bullets of fireBoy left direction
void printBulletLeft(int leftx, int lefty);
void eraseLeftBullet(int leftx, int lefty);
void makeLeftBulletInactive(int idx);
void generateBulletLeft();
void moveBulletLeft();
// ghost1
void printGhost();
void eraseGhost();
void moveGhostHorizontal();
// ghost 2
void moveGhostVertical();
void printGhost2();
void eraseGhost2();
// bullets of ghost 1
void printBulletGhost(int Gx, int Gy);
void generateBulletGhostright();
void generateBulletGhostleft();
void eraseBulletGhost(int Gx, int Gy);
void moveBulletGhost();
void makeGhostBulletInactive(int x);
// bullets of ghost2
void printBulletGhost2(int gx, int gy);
void eraseBulletGhost2(int gx, int gy);
void generateBulletGhost2();
void moveBulletGhost2();
void makeGhost2BulletInactive(int x);
// score of fireboy
void addScore();
void printScore();
void decreaseScore();
// lives of fireboy
void addLives();
void DecreaseLives();
void printLives();
// score of ghost 1
void AddhealthOfOggy();
void deacreaseHealthOfOggy();
void printHealthOfOggy();
int Oggy_Health = 100;
// score of ghost 2
void printHealthOfFangy();
int Fangy_Health = 100;
void AddhealthOfFangy();
void deacreaseHealthOfFangy();
// power pallets
void FoodPalletsRight();
void FoodPalletsLeft();
void PowerPallets();
void RandomPowerPallet();
// collisions...
void bulletCollionWithGhost(); // right
void bulletCollionWithGhost2();
void bulletLeftCollionWithGhost(); // left
void bulletLeftCollionWithGhost2();
void CollisionOfGhosts1BulletWithFireBoy();
void CollisionOfGhosts2BulletWithFireBoy();
void CollisionOfFireboyWithChasingGhost();
// Chasing Ghost
void moveChasingGhost();
void printChasingGhost();
void eraseGChasingGhost();
//file handling for resuming game
 void ScoreToFile();
 void ScoreToArray( );

bool flag = true;

int bulletX[10000];   //bullets of fireboy in right direction
int bulletY[10000];
int bulletGX[10000]; //bullets of Oggy
int bulletGY[10000];
int bulletgX[10000]; //bullets of Fangy
int bulletgY[10000];
int bulletLeftX[10000];  //bullets of fireboy in left direction
int bulletLeftY[10000];
bool isBulletActive[10000];        //bullet active function for fireboy's right bullets
bool isLeftBulletActive[10000];     //bullet active function for fireboy's left bullets
bool isGhostBulletActive[10000];     //bullet active function for Oggy's bullets
bool isGhost2BulletActive[10000];     //bullet active function for Fangy's bullets

//printing hero(Fireboy)
char l = 1;
char m = 178;
char z = 16;
char a = 17;
char b = 193;
char player1[3][3] = {{' ', l, ' '},
                      {a, m, z},
                      {' ', b, ' '}};

 //printing enemy(Oggy)                     
char i = 2;
char j = 176;
char o = 247;
char t = 247;
char enemy1[5][5] = {{' ', ' ', i, ' ', ' '}, {o, j, j, j, o}, {' ', o, ' ', t, ' '}};

int bulletCount = 0; //bullet count for fireboy
int option = 0;
int bulletCountLeft = 0; //bullet count for fireboy's left bullet
int palletTimer = 0;
int counts = 0;        //bullet count for Oggy
int counter = 0;        //bullet count for Fangy
int lives = 50;  
int score = 0;
int timer = 0;
//coodinates of fireboy
int Fx = 40;
int Fy = 44;
//Coordinates of Oggy
int Gx = 130;
int Gy = 8;
//coordinates of Fangy
int gx = 110;
int gy = 25;
//coordinates for chasing ghost

int Fyre_X = 12;
int Fyre_Y = 44;

string enemy1dir = "left";
string enemy2dir = "Down";           //directions...
string enemy3dir = "right";

main()
{
    startPage();
    cout << "press any key to continue";
    getch();
    system("cls");
    SetConsoleTextAttribute(acolor, 12);
    WelcomeScreen();
    cout << "press any key to continue";
    getch();
    system("cls");
    MainMenuScreen();
    system("cls");
    //Main Menu for Options
    if (option == 1)
    {
        Game();
    }
    if (option == 2)
    {
        Instructions();
        cout << "press any key to continue";
        getch();
        system("cls");
        MainMenuScreen();
        if (option == 1)
        {
            system("cls");
            Game();
        }
    }
     if (option == 4)
    {
       ScoreToArray( );
        Game();
       


    }

  
}
void printMaze()   //printing maze
{
    for (int i = 0; i < 49; i++)
    {
        for (int j = 0; j < 156; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}
void readmazefromfile()       //reading maze fron file
{
    fstream file;
    string line;
    int row = 0;
    file.open("maze.txt", ios::in);

    while (!file.eof())
    {
        getline(file, line);
        for (int col = 0; col < 156; col++)
        {
            maze[row][col] = line[col];
        }
        row++;
    }
    file.close();
    row = 0;
}
void printFireboy()         //printing hero
{
    SetConsoleTextAttribute(acolor, 4);
    gotoxy(Fx, Fy);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << player1[i][j];
        }
    }

    gotoxy(Fx, Fy + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << player1[i][j];
        }
    }
    gotoxy(Fx, Fy + 2);
    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << player1[i][j];
        }
    }
}


void eraseFireboy()                          //Erarasing 
{ 
    gotoxy(Fx, Fy);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << " ";
        }
    }

    gotoxy(Fx, Fy + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << " ";
        }
    }
    gotoxy(Fx, Fy + 2);
    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << " ";
        }
    }
}

void moveFireboyRight()       //right direction of fireboy
{
    char next1 = getCharAtxy(Fx + 3, Fy);
    char next2 = getCharAtxy(Fx + 3, Fy + 1);
    char next3 = getCharAtxy(Fx + 3, Fy + 2);

    if (next1 == ' ' && next2 == ' ' && next3 == ' ')
    {
        eraseFireboy();
        Fx = Fx + 1;
        printFireboy();
    }
    if (next1 == '-' || next2 == '-' || next3 == '-')
    {
        DecreaseLives();
    }
    if (next1 == '%' || next2 == '%' || next3 == '%')
    {
        eraseFireboy();
        Fx = Fx + 1;
        printFireboy();
    }
    if (next1 == '|' || next2 == '|' || next3 == '|')
    {
        GameWon();
        Sleep(100000);
        system("cls");
    }
}
void moveFireboyLeft()                                 //right direction of fireboy
{
    char next1 = getCharAtxy(Fx - 1, Fy); 
    char next2 = getCharAtxy(Fx - 1, Fy + 1);
    char next3 = getCharAtxy(Fx - 1, Fy + 2);
    if (next1 == ' ' && next2 == ' ' && next3 == ' ')
    {
        eraseFireboy();
        Fx = Fx - 1;  
        printFireboy();
    }
    if (next1 == '-' || next2 == '-' || next3 == '-')
    {
        DecreaseLives();
    }
    if (next1 == '@' || next2 == '@' || next3 == '@')
    {
        eraseFireboy();
        Fx = Fx - 1;
        printFireboy();
        addLives();
    }
}
void moveFireboyUp()    //up  direction of fireboy
{
    char next1 = getCharAtxy(Fx, Fy - 1);
    char next2 = getCharAtxy(Fx, Fy - 2);
    char next3=  getCharAtxy(Fx, Fy - 2);
    if (next1 == ' ' && next2 == ' '  &&  next3==' ')
    {
        eraseFireboy();
        Fy = Fy - 2;
        printFireboy();
    }
     if (next1 == '#' && next2 == '#' && next3=='#')
    {
        eraseFireboy();
        Fy = Fy -5;
        printFireboy();
    }
}

void moveFireboyDown()               //down  direction of fireboy
{
    char next1 = getCharAtxy(Fx + 1, Fy + 3);
    char next2 = getCharAtxy(Fx, Fy + 3);
    char next3 = getCharAtxy(Fx + 2, Fy + 3);
    if (next1 == ' ' && next2 == ' ' && next3 == ' ')
    {
        eraseFireboy();
        Fy = Fy + 1;
        printFireboy();
    }
    if (next1 == '-' || next2 == '-' || next3 == '-')
    {
        DecreaseLives();
    }
}
void printGhost()        //printing Oggy
{
    SetConsoleTextAttribute(acolor, 1);
    char i = 2;
    char j = 176;
    char o = 247;
    char t = 247;
    char enemy1[5][5] = {{' ', ' ', i, ' ', ' '}, {o, j, j, j, o}, {' ', o, ' ', t, ' '}};

    gotoxy(Gx, Gy);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << enemy1[i][j];
        }
    }

    gotoxy(Gx, Gy + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << enemy1[i][j];
        }
    }
    gotoxy(Gx, Gy + 2);
    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << enemy1[i][j];
        }
    }
}
void eraseGhost()     //erasing Oggy
{
    gotoxy(Gx, Gy);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }

    gotoxy(Gx, Gy + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }
    gotoxy(Gx, Gy + 2);
    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }
}
void moveGhostHorizontal()       //Horizontal moment Oggy
{
    if (enemy1dir == "right")
    {

        char next1 = getCharAtxy(Gx + 5, Gy);
        char next2 = getCharAtxy(Gx + 5, Gy + 1);
        char next3 = getCharAtxy(Gx + 5, Gy + 2);
        if (next1 == ' ' && next2 == ' ' && next3 == ' ' || next1 == '-' && next2 == '-' && next3 == '-')
        {
            eraseGhost();
            Gx++;
            printGhost();
        }
        if (next1 == '#' || next2 == '#' || next3 == '#' && next1 == '|' || next2 == '|' || next3 == '|' && next1 == '_' || next2 == '_' || next3 == '_')
        {
            enemy1dir = "left";
        }
    }
    if (enemy1dir == "left")
    {
        char next1 = getCharAtxy(Gx - 3, Gy);
        char next2 = getCharAtxy(Gx - 3, Gy + 1);
        char next3 = getCharAtxy(Gx - 3, Gy + 2);

        if (next1 == ' ' && next2 == ' ' && next3 == ' ' || next1 == '-' && next2 == '-' && next3 == '-')
        {
            eraseGhost();
            Gx = Gx - 1;
            printGhost();
        }
        if (next1 == '#' || next2 == '#' | next3 == '#')
        {
            enemy1dir = "right";
        }
    }
}
void printGhost2()     //printing Fangy
{
    SetConsoleTextAttribute(acolor, 1);

    char i = 2;
    char j = 176;
    char o = 247;
    char t = 247;
    char enemy2[5][5] = {{' ', ' ', i, ' ', ' '}, {o, j, j, j, o}, {' ', o, ' ', t, ' '}};
    if (Fangy_Health != 0)
    {
        gotoxy(gx, gy);
        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                cout << enemy2[i][j];
            }
        }
        gotoxy(gx, gy + 1);
        for (int i = 1; i < 2; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                cout << enemy2[i][j];
            }
        }
        gotoxy(gx, gy + 2);
        for (int i = 2; i < 3; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                cout << enemy2[i][j];
            }
        }
    }
    else
    {
        eraseGhost2();
    }
}

void eraseGhost2()                 //erasing Fangy
{
    gotoxy(gx, gy);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }

    gotoxy(gx, gy + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }
    gotoxy(gx, gy + 2);
    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }
}
void moveGhostVertical()  //vertical ghost2
{
    if (enemy2dir == "Up")
    {
        char next = getCharAtxy(gx, gy - 1);
        if (next == ' ')
        {
            eraseGhost2();
            gy--;
            printGhost2();
        }
        else // if (next == '#'), this is not needed, - ke saath bhi check krna h
        {
            enemy2dir = "Down";
        }
    }
    if (enemy2dir == "Down")
    {
        char next = getCharAtxy(gx, gy + 3);
        if (next == ' ')
        {
            eraseGhost2();
            gy++;
            printGhost2();
        }
        if (next == '#')
        {
            enemy2dir = "Up";
        }
    }
}

//**************************************************Bullets of FireBoy**********************************************
void generateBullet()
{

    bulletX[bulletCount] = Fx + 6;
    bulletY[bulletCount] = Fy;
    isBulletActive[bulletCount] = true;
    gotoxy(Fx + 6, Fy);
    cout << ".";
    bulletCount++;
}

void moveBullet()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {
            char next = getCharAtxy(bulletX[x] + 1, bulletY[x]);
            char next1 = getCharAtxy(bulletX[x] + 1, bulletY[x]);
            char next2 = getCharAtxy(bulletX[x] + 1, bulletY[x]);
            if ((next == '#' || next1 == '#' || next2 == '#') ||
                (next == '-' || next1 == '-' || next2 == '-') ||
                (next == '*' || next1 == '*' || next2 == '*') ||
                (next == '|' || next1 == '|' || next2 == '|') || 
                (next == '_' || next1 == '_' || next2 == '_'))
               
            {
                eraseBullet(bulletX[x], bulletY[x]);
                makeBulletInactive(x);
            }
            else
            {
                eraseBullet(bulletX[x], bulletY[x]);
                bulletX[x] = bulletX[x] + 1;
                printBullet(bulletX[x], bulletY[x]);
            }
        }
    }
}

//**************************************************Collisions of fireboy's bullet with ghost**********************************************
void printBullet(int x, int y)
{
    SetConsoleTextAttribute(acolor, 4);
    gotoxy(x, y);
    cout << ".";
}
void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void makeBulletInactive(int idx)
{
    isBulletActive[idx] = false;
}
//**************************************************Collisions of fireboy's bullet with ghost**********************************************
void bulletCollionWithGhost()
{ 
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {

            if (bulletX[x] + 1 == Gx && (bulletY[x] == Gy || bulletY[x] == Gy + 2 || bulletY[x] == Gy + 5))
            {
                addScore();
                deacreaseHealthOfOggy();
            }
            if (Gx - 1 == bulletX[x] && Gy + 1 == bulletY[x])
            {
                addScore();
                deacreaseHealthOfOggy();
            }
            if (bulletX[x] + 1 == gx && (bulletY[x] == Gy || bulletY[x] == Gy + 2 || bulletY[x] == Gy + 5))
            {
                addScore();
                deacreaseHealthOfOggy();
            }
        }
    }
}


void bulletCollionWithGhost2()

{

    //**************************************************Collisions of fireboy's bullet with ghost2**********************************************
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {

            if (bulletX[x] + 1 == gx && (bulletY[x] == gy || bulletY[x] == gy + 2 || bulletY[x] == gy + 5))
            {
                addScore();
                deacreaseHealthOfFangy();
            }
            if (gx - 1 == bulletX[x] && gy + 1 == bulletY[x])
            {
                addScore();
                deacreaseHealthOfFangy();
            }
            if (bulletX[x] + 5 == gx && (bulletY[x] == gy || bulletY[x] == gy + 2 || bulletY[x] == gy + 5))
            {
                addScore();
                deacreaseHealthOfFangy();
            }
        }
    }
}

//Score of fireboy
void addScore()
{
    score++;
}
void printScore()
{
    SetConsoleTextAttribute(acolor, 4);
    if (score >= 0)
    {
        gotoxy(185, 11);
        cout << "Fireboy_score : " << score;
    }
}

//food pallets for maze
void FoodPalletsRight()
{

    char next1 = getCharAtxy(Fx + 3, Fy);
    char next2 = getCharAtxy(Fx + 3, Fy + 1);
    char next3 = getCharAtxy(Fx + 3, Fy + 2);

    if (next1 == '*' || next2 == '*' || next3 == '*')
    {
        eraseFireboy();
        Fx = Fx + 1;
        printFireboy();
        addScore();
    }
}
void FoodPalletsLeft()
{
    char next1 = getCharAtxy(Fx - 1, Fy);
    char next2 = getCharAtxy(Fx - 1, Fy + 1);
    char next3 = getCharAtxy(Fx - 1, Fy + 2);
    if (next1 == '*' || next2 == '*' || next3 == '*')
    {
        eraseFireboy();
        Fx = Fx - 1;
        printFireboy();
        addScore();
    }
}

//lives of FireBoy
void addLives()
{
    lives++;
}
void printLives()
{
    SetConsoleTextAttribute(acolor, 4);
    gotoxy(185, 14);
    cout << "Fireboy_Lives : " << lives;
    if (lives == 0)
    {
        system("cls");
        GameOver();
        Sleep(100000);
        system("cls");
    }
}
void DecreaseLives()
{
    lives--;
}
void PowerPallets()
{

    char next1 = getCharAtxy(Fx + 3, Fy);
    char next2 = getCharAtxy(Fx + 3, Fy + 1);
    char next3 = getCharAtxy(Fx + 3, Fy + 2);

    if (next1 == '@' || next2 == '@' || next3 == '@')
    {
        eraseFireboy();
        Fx = Fx + 1;
        printFireboy();
        addLives();
    }
}
// ghost bullet
void printBulletGhost(int x, int y)
{
    SetConsoleTextAttribute(acolor, 1);
    gotoxy(x, y);
    cout << "-";
}
void eraseBulletGhost(int x, int y)
{

    gotoxy(x, y);
    cout << " ";
}
void generateBulletGhostright()
{
    char next = getCharAtxy(Gx + 6, Gy);
    if (next == ' ' && Gx < 140)
    {
        bulletGX[counts] = Gx + 6;
        bulletGY[counts] = Gy;
        isGhostBulletActive[counts] = true;
        gotoxy(Gx + 6, Gy);
        cout << "-";
        counts++;
    }
}
void generateBulletGhostleft()
{
    bulletGX[counts] = Gx - 1;
    bulletGY[counts] = Gy;
    isGhostBulletActive[counts] = true;
    gotoxy(Gx - 1, Gy);
    cout << "-";
    counts++;
}

void moveBulletGhost()
{
    for (int x = 0; x < counts; x++)
    {
        if (isGhostBulletActive[x] == true && enemy1dir == "right")
        {
            char next = getCharAtxy(bulletGX[x] + 6, bulletGY[x]);
            if (next != ' ')
            {
                eraseBulletGhost(bulletGX[x], bulletGY[x]);
                makeGhostBulletInactive(x);
            }
            else
            {
                eraseBulletGhost(bulletGX[x], bulletGY[x]);
                bulletGX[x] = bulletGX[x] + 1;
                printBulletGhost(bulletGX[x], bulletGY[x]);
            }
        }
        if (isGhostBulletActive[x] == true && enemy1dir == "left")
        {
            char next = getCharAtxy(bulletGX[x] - 1, bulletGY[x]);
            if (next != ' ')
            {
                eraseBulletGhost(bulletGX[x], bulletGY[x]);
                makeGhostBulletInactive(x);
            }
            else
            {
                eraseBulletGhost(bulletGX[x], bulletGY[x]);
                bulletGX[x] = bulletGX[x] - 1;
                printBulletGhost(bulletGX[x], bulletGY[x]);
            }
        }
    }
}
void makeGhostBulletInactive(int x)
{
    isGhostBulletActive[x] = false; 
}

// ghost 2 bullets

void printBulletGhost2(int x, int y)
{
    SetConsoleTextAttribute(acolor, 1);
    gotoxy(x, y);
    cout << "-";
}
void eraseBulletGhost2(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void generateBulletGhost2()
{
    bulletgX[counter] = gx + 6;
    bulletgY[counter] = gy;
    isGhost2BulletActive[counter] = true;
    gotoxy(gx + 6, gy);
    cout << "-";
    counter++;
}
void moveBulletGhost2()
{
    for (int x = 0; x < counter; x++)
    {
        char next = getCharAtxy(bulletgX[x] + -1, bulletgY[x]);
        if (next != ' ')
        {
            eraseBulletGhost(bulletgX[x], bulletgY[x]);
            makeGhost2BulletInactive(x);
        }
        else
        {
            eraseBulletGhost2(bulletgX[x], bulletgY[x]);
            bulletgX[x] = bulletgX[x] - 1;
            printBulletGhost2(bulletgX[x], bulletgY[x]);
        }
    }
}
void makeGhost2BulletInactive(int x)
{
    isGhost2BulletActive[x] = false; 
}
void decreaseScore()
{
    score--;
}

//********************************************************CollisionOfGhosts1BulletWithFireBoy*************************************
void CollisionOfGhosts1BulletWithFireBoy()
{
    for (int x = 0; x < 1000; x++)
    {

        if (isGhostBulletActive[x] == true)
        {

            if (bulletGX[x] + 1 == Fx && (bulletGX[x] == Fy || bulletGY[x] == Fy + 2 || bulletGY[x] == Gy + 5))
            {
                decreaseScore();
                AddhealthOfOggy();
            }
            if (Fx - 1 == bulletGX[x] && Fy + 1 == bulletGY[x])
            {
                decreaseScore();
                AddhealthOfOggy();
            }
            if (bulletGX[x] + 5 == Fx && (bulletGY[x] == Fy || bulletGY[x] == Fy + 2 || bulletGY[x] == Fy + 5))
            {
                decreaseScore();
                AddhealthOfOggy();
            }
        }
    }
}
void CollisionOfGhosts2BulletWithFireBoy()
{
    for (int x = 0; x < 10000; x++)
    {
        if (isGhost2BulletActive[x] == true)
        {
            if (bulletgX[x] - 2 == Fx && (bulletgX[x] == Fy || bulletgY[x] == Fy + 1 || bulletgY[x] == Fy + 2))
            {
                decreaseScore();
                AddhealthOfOggy();
            }
            if (Fx + 2 == bulletgX[x])
            {
                decreaseScore();
                AddhealthOfOggy();
            }
            if (bulletgX[x] - 3 == Fx && (bulletgY[x] == Fy || bulletgY[x] == Fy + 1 || bulletgY[x] == Fy + 2))
            {
                decreaseScore();
                AddhealthOfOggy();
            }
        }
    }
}

//Health of game
void AddhealthOfOggy()
{
    Oggy_Health++;
}
void printHealthOfOggy()
{
    SetConsoleTextAttribute(acolor, 1);
    if (Oggy_Health >= 0)
    {
        gotoxy(185, 20);
        cout << "Oggy_Health : " << Oggy_Health << "   ";
    }
}
void deacreaseHealthOfOggy()
{
    Oggy_Health--;
}
void printHealthOfFangy()
{
    SetConsoleTextAttribute(acolor, 1);
    if (Fangy_Health >= 0)
    {
        gotoxy(185, 23);
        cout << "Fangy_Health : " << Fangy_Health << "    ";
    }
    gotoxy(185, 24);
}

//health of fangy
void AddhealthOfFangy()
{
    Fangy_Health++;
}
void deacreaseHealthOfFangy()
{
    Fangy_Health--;
}

void printBulletLeft(int leftx, int lefty)
{

    gotoxy(leftx, lefty);
    cout << ".";
}
void eraseLeftBullet(int leftx, int lefty)
{
    gotoxy(leftx, lefty);
    cout << " ";
}
void generateBulletLeft()
{
    bulletLeftX[bulletCountLeft] = Fx - 1;
    bulletLeftY[bulletCountLeft] = Fy + 1;
    isLeftBulletActive[bulletCountLeft] = true;
    gotoxy(Fx - 1, Fy + 1);
    cout << ".";
    bulletCountLeft++;
}
void moveBulletLeft()
{
    for (int x = 0; x < bulletCountLeft; x++)
    {
        if (isLeftBulletActive[x] == true)
        {
            char next = getCharAtxy(bulletLeftX[x] - 1, bulletLeftY[x]);
            if (next != ' ')
            {
                eraseLeftBullet(bulletLeftX[x], bulletLeftY[x]);
                makeLeftBulletInactive(x);
            }
            else
            {
                eraseLeftBullet(bulletLeftX[x], bulletLeftY[x]);
                bulletLeftX[x] = bulletLeftX[x] - 1;
                printBullet(bulletLeftX[x], bulletLeftY[x]);
            }
        }
    }
}
void makeLeftBulletInactive(int idx)
{
    isLeftBulletActive[idx] = false;
}

void bulletLeftCollionWithGhost()
{

    for (int x = 0; x < bulletCountLeft; x++)
    {
        if (isLeftBulletActive[x] == true)
        {

            if (bulletLeftX[x] - 1 == Gx + 4 && (bulletLeftY[x] == Gy || bulletLeftY[x] == Gy + 1 || bulletLeftY[x] == Gy + 2))
            {
                addScore();
                deacreaseHealthOfOggy();
            }
            if (Gx - 1 == bulletLeftX[x] && Gy + 1 == bulletLeftX[x])
            {
                addScore();
                deacreaseHealthOfOggy();
            }
            if (bulletLeftX[x] - 1 == gx && (bulletLeftY[x] == Gy || bulletLeftY[x] == Gy - 2 || bulletLeftY[x] == Gy - 5))
            {
                addScore();
                deacreaseHealthOfOggy();
            }
        }
    }
}
void bulletLeftCollionWithGhost2()
{
    for (int x = 0; x < bulletCountLeft; x++)
    {
        if (isLeftBulletActive[x] == true)
        {

            if (bulletLeftX[x] - 1 == gx + 4 && (bulletLeftX[x] == gy || bulletLeftY[x] == gy + 1 || bulletLeftY[x] == gy + 2))
            {
                addScore();
                deacreaseHealthOfFangy();
            }
        }
    }
}

void GameOver()
{
    SetConsoleTextAttribute(acolor, 13);
    system("cls");
    cout << "## ##     ##     ##   ##  ### ###            ## ##   ### ###  ### ###  ### ##  " << endl;
    cout << "##   ##     ##     ## ##    ##  ##           ##   ##   ##  ##   ##  ##   ##  ##" << endl;
    cout << "##        ## ##   # ### #   ##               ##   ##   ##  ##   ##       ##  ##" << endl;
    cout << "##  ###   ##  ##  ## # ##   ## ##            ##   ##   ##  ##   ## ##    ## ## " << endl;
    cout << "##   ##   ## ###  ##   ##   ##               ##   ##   ### ##   ##       ## ## " << endl;
    cout << "##   ##   ##  ##  ##   ##   ##  ##           ##   ##    ###     ##  ##   ##  ##" << endl;
    cout << " ## ##   ###  ##  ##   ##  ### ###            ## ##      ##    ### ###  #### ##" << endl;
    cout << "                                                                               " << endl;
    cout << "YOUR SCORE IS:" << score;
    char ch;
    cin >> ch;
    abort();
}

void printChasingGhost()
{
    SetConsoleTextAttribute(acolor, 1);
    char i = 2;
    char j = 176;
    char o = 247;
    char t = 247;
    char enemy1[5][5] = {{' ', ' ', i, ' ', ' '}, {o, j, j, j, o}, {' ', o, ' ', t, ' '}};

    gotoxy(Fyre_X, Fyre_Y);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << enemy1[i][j];
        }
    }

    gotoxy(Fyre_X, Fyre_Y + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << enemy1[i][j];
        }
    }
    gotoxy(Fyre_X, Fyre_Y + 2);
    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << enemy1[i][j];
        }
    }
}

void eraseGChasingGhost()
{
    gotoxy(Fyre_X, Fyre_Y);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }

    gotoxy(Fyre_X, Fyre_Y + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }
    gotoxy(Fyre_X, Fyre_Y + 2);
    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }
}
void moveChasingGhost()
{
    eraseGChasingGhost();
    if (Fx > Fyre_X)
    {
        char next1 = getCharAtxy(Fyre_X + 5, Fyre_Y);
        char next2 = getCharAtxy(Fyre_X + 5, Fyre_Y + 1);
        char next3 = getCharAtxy(Fyre_X + 5, Fyre_Y + 2);
        if (next1 == ' ' && next2 == ' ' && next3 == ' ')
        {
            Fyre_X++;
        }
        if (next1 == '-' || next2 == '-' || next3 == '-')
        {
            Fyre_X = Fyre_X + 21;
            gotoxy(Fyre_X, Fyre_Y);
            printChasingGhost();
        }
    }
    if (Fx < Fyre_X)
    {
        char next1 = getCharAtxy(Fyre_X - 1, Fyre_Y);
        char next2 = getCharAtxy(Fyre_X - 1, Fyre_Y + 1);
        char next3 = getCharAtxy(Fyre_X - 1, Fyre_Y + 2);
        if (next1 == ' ' && next2 == ' ' && next3 == ' ')
        {
            Fyre_X--;
        }
        if (next1 == '-' || next2 == '-' || next3 == '-')
        {
            Fyre_X = Fyre_X - 21;
            gotoxy(Fyre_X, Fyre_Y);
            printChasingGhost();
        }
    }
    if (Fy > Fyre_Y)
    {
        char next1 = getCharAtxy(Fyre_X, Fyre_Y + 3);
        char next2 = getCharAtxy(Fyre_X + 1, Fyre_Y + 3);
        char next3 = getCharAtxy(Fyre_X + 2, Fyre_Y + 3);
        if (next1 == ' ' && next2 == ' ' && next3 == ' ')
        {
            Fyre_Y++;
        }
    }
    if (Fy < Fyre_Y)
    {
        char next1 = getCharAtxy(Fyre_X, Fyre_Y - 1);
        char next2 = getCharAtxy(Fyre_X + 1, Fyre_Y - 1);
        char next3 = getCharAtxy(Fyre_X + 2, Fyre_Y - 1);

        char collision1 = getCharAtxy(Fyre_X + 2, Fyre_Y - 1);

        if (next1 == ' ' && next2 == ' ' && next3 == ' ')
        {
            Fyre_Y--;
        }
        if (collision1 == '#' /*|collision2 =='#'||collision3 =='#'||collision4 =='#'||collision5 =='#'*/)
        {
            gotoxy(159, 20);
            // cout<<"value"<<Fyre_Y -1 ;

            eraseGChasingGhost();
            Fyre_Y++;
            //    gotoxy(Fyre_X,Fyre_Y);
            printChasingGhost();
        }
    }
    printChasingGhost();
}
void RandomPowerPallet()             //RANDOM FUNCTION
{
    if (palletTimer == 1000)
    { 
        int x = rand() % 98 + 1;
        int y = rand() % 23 + 1;
        char location = getCharAtxy(x, y);
        if (location == ' ')
        {
            SetConsoleTextAttribute(acolor, 6);
            gotoxy(x, y);
            cout << "@";
        }
        palletTimer = 0;
    }
    palletTimer++;
}

//collision with chasing ghost
void CollisionOfFireboyWithChasingGhost()
{
    char next1 = getCharAtxy(Fyre_X + 6, Fyre_Y);//right
    char next5 = getCharAtxy(Fyre_X + 6, Fyre_Y+1);
    char next6 = getCharAtxy(Fyre_X + 6, Fyre_Y+2);
    char next2 = getCharAtxy(Fyre_X - 1, Fyre_Y);//left
    char next7 = getCharAtxy(Fyre_X - 1, Fyre_Y+1);
    char next8 = getCharAtxy(Fyre_X - 1, Fyre_Y+2);
    char next3 = getCharAtxy(Fyre_X , Fyre_Y - 1);//up
    char next9 = getCharAtxy(Fyre_X +1, Fyre_Y - 1);
    char next10 = getCharAtxy(Fyre_X+2 , Fyre_Y - 1);
    char next4 = getCharAtxy(Fyre_X, Fyre_Y + 3);//down
    char next11 = getCharAtxy(Fyre_X+1, Fyre_Y + 3);
    char next12 = getCharAtxy(Fyre_X+2, Fyre_Y + 3);
   // char next5 = getCharAtxy(Fx+2 , Fy + 2);
    //char next3 = getCharAtxy(Fyre_X + 5, Fyre_Y + 2);

    
    if ((next1 == l || next2 == l || next3 == l || next4 == l  
    ||next5 == l || next6 == l || next7 == l || next8 == l
    ||next9 == l || next10 == l || next11 == l || next12 == l) 
    || (next1 == m || next2 == m || next3 == m || next4 == m  
    ||next5 == m || next6 == m || next7 == m || next8 == m
    ||next9 == m || next10 == m || next11 == m || next12 == m) 
    || (next1 == b || next2 == b || next3 == b || next4 == b  
    ||next5 == b || next6 == b || next7 == b || next8 == b
    ||next9 == b || next10 == b || next11 == b || next12 == b) || 
    (next1 == z || next2 == z || next3 == z || next4 == z  
    ||next5 == z || next6 == z || next7 == z || next8 == z
    ||next9 == z || next10 == z || next11 == z || next12 == z) || 
    (next1 == a || next2 == a || next3 == a || next4 == a  
    ||next5 == a || next6 == a || next7 == a || next8 == a
    ||next9 == a || next10 == a || next11 == a || next12 == a)) 
    {
            GameOver();
    }
    
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@GAME START@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void Game()
{
    readmazefromfile();
    SetConsoleTextAttribute(acolor, 14);
    printMaze();
    printGhost();
    printGhost2();
    printChasingGhost();

    printFireboy();
    while (true)
    {
        if (option == 2)
        {
            Instructions();
        }
        printScore();
        printLives();
        RandomPowerPallet();
        SetConsoleTextAttribute(acolor, 11);
        printHealthOfOggy();
        printHealthOfFangy();

        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveFireboyRight();
        }

        if (GetAsyncKeyState(VK_LEFT))
        {
            moveFireboyLeft();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            flag = true;
            moveFireboyUp();
        }
        else
        {
            flag = false;
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            generateBullet();
        }
        if (GetAsyncKeyState(VK_CONTROL))
        {
            generateBulletLeft();
        }

        if (timer == 3)
        {
            moveGhostHorizontal();
            moveGhostVertical();
            moveChasingGhost();

            if (Oggy_Health > 0)
            {
                if (enemy1dir == "left")
                {
                    generateBulletGhostleft();
                }
                else
                {
                    generateBulletGhostright();
                }
            }
            if (Fangy_Health > 0)
            {
                generateBulletGhost2();
            }
            timer = 0;
        }
        timer++;
        moveBullet();
        moveBulletLeft();
        moveBulletGhost();
        moveBulletGhost2(); 
        bulletCollionWithGhost();
        bulletCollionWithGhost2();
        CollisionOfGhosts1BulletWithFireBoy();
        CollisionOfGhosts2BulletWithFireBoy();
        CollisionOfFireboyWithChasingGhost();
        FoodPalletsRight();
        FoodPalletsLeft();
        PowerPallets();
        bulletLeftCollionWithGhost();
        bulletLeftCollionWithGhost2();
        moveFireboyDown();
         

        Sleep(03);
        ScoreToFile();
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

//********************************************Headers**********************************************

void startPage()
{
    SetConsoleTextAttribute(acolor, 13);
    system("cls");
    cout << "##   ##  ### ###  ####      ## ##    ## ##   ##   ##  ### ##" << endl;
    cout << "##   ##   ##  ##   ##      ##   ##  ##   ##   ## ##    ##  #" << endl;
    cout << "##   ##   ##       ##      ##       ##   ##  # ### #   ## " << endl;
    cout << "## # ##   ## ##    ##      ##       ##   ##  ## # ##   ## ## " << endl;
    cout << "# ### #   ##       ##      ##       ##   ##  ##   ##   ##   " << endl;
    cout << " ## ##    ##  ##   ##  ##  ##   ##  ##   ##  ##   ##   ##  ## " << endl;
    cout << "##   ##  ### ###  ### ###   ## ##    ## ##   ##   ##  ### ### " << endl;
    cout << "                                                              " << endl;
    cout << " #### ##   ## ##" << endl;
    cout << "# ## ##  ##   ##" << endl;
    cout << "  ##     ##   ##" << endl;
    cout << "  ##     ##   ##" << endl;
    cout << "  ##     ##   ##" << endl;
    cout << "  ##     ##   ##" << endl;
    cout << " ####     ## ## " << endl;
    cout << "                                                              " << endl;
    cout << "#### ##  ###  ##  ### ###           ##   ##   ## ##   ### ##   ####     ### ##             ## ##   ### ###           ### ###    ####   ### ##   ### ## " << endl;
    cout << "# ## ##   ##  ##   ##  ##           ##   ##  ##   ##   ##  ##   ##       ##  ##           ##   ##   ##  ##            ##  ##     ##     ##  ##   ##  ##" << endl;
    cout << "  ##      ##  ##   ##               ##   ##  ##   ##   ##  ##   ##       ##  ##           ##   ##   ##                ##         ##     ##  ##   ##    " << endl;
    cout << "  ##      ## ###   ## ##            ## # ##  ##   ##   ## ##    ##       ##  ##           ##   ##   ## ##             ## ##      ##     ## ##    ## ## " << endl;
    cout << "  ##      ##  ##   ##               # ### #  ##   ##   ## ##    ##       ##  ##           ##   ##   ##                ##         ##     ## ##    ##    " << endl;
    cout << "  ##      ##  ##   ##  ##            ## ##   ##   ##   ##  ##   ##  ##   ##  ##           ##   ##   ##                ##         ##     ##  ##   ##  ## " << endl;
    cout << " ####    ###  ##  ### ###           ##   ##   ## ##   #### ##  ### ###  ### ##             ## ##   ####              ####       ####   #### ##  ### ### " << endl;
}
void WelcomeScreen()
{

    cout << "                                               :=                    " << endl;
    cout << "                                               =@%.                  " << endl;
    cout << "                                  .+:          #%#@:                 " << endl;
    cout << "                                   %@%-        @%##@=                " << endl;
    cout << "                                .  #%%@#.  .  -@###%@-               " << endl;
    cout << "                                   %%##%@:    #@####%@.              " << endl;
    cout << "                                  -@####@@.  .@%%####@#    -         " << endl;
    cout << "                                 :@%#%%%%@#  *@######%@=  .@#        " << endl;
    cout << "                          :%=   :@%#%%#%%@@::@%%#####%@%  #@@=       " << endl;
    cout << "                          #%@#  @%#%%###%%@*@%%######%%@:*@#%@       " << endl;
    cout << "                         .@##@*-@#%%#####%@%#%########%@@@%##@+      " << endl;
    cout << "                         =@##%@@%#%#######%%##########%@@%###%@      " << endl;
    cout << "                         +%###@@#%####################%%######@=     " << endl;
    cout << "                         *%###%%#%############################%%  .  " << endl;
    cout << "                         *%#####%############%################%@.    " << endl;
    cout << "                         *%#####%##########%%%%%%%%############@-    " << endl;
    cout << "                         =@#######%#+=---=*%%%%%%#***#%########@+    " << endl;
    cout << "                         .@#######%+=--+=-=%%%%%%-=---%########@+    " << endl;
    cout << "                          %%######%#=--=-=#%%%%%%*+==+%########@+    " << endl;
    cout << "                          =@########%%##%%%%%%%%%%%%%##########@:    " << endl;
    cout << "                           @##################################%%  .  " << endl;
    cout << "                           =@#################################@:     " << endl;
    cout << "                            +@#########%#####################@-      " << endl;
    cout << "                             +@#########%%%%%%#############%%:       " << endl;
    cout << "                              :#%########################%%+         " << endl;
    cout << "                                -#%%##################%%#-           " << endl;
    cout << "                                   -*#%%%#######%%%@%+-              " << endl;
    cout << "                                      +%%%%@@@%%%%%#:                " << endl;
    cout << "                                     =%%%%%%%%%%%%*%%-               " << endl;
    cout << "                                    .%%%:#%%%%%%%%.*%%-              " << endl;
    cout << "                                     ++. #%%%%%%%%. --               " << endl;
    cout << "                                         %%%%%%%%%:                  " << endl;
    cout << "                                         %%%%-*%%%-                  " << endl;
    cout << "                                         #%%% -%%%-                  " << endl;
    cout << "                                         -**-  =++                   " << endl;
    cout << "                                                                     " << endl;
}
int MainMenuScreen()
{
    cout << "#### ##  ###  ##  ### ###           ### ###    ####   ### ###  ### ##   ##  ##            ###  ##    ####    ## ##   ###  ##  #### ##" << endl;
    cout << "# ## ##   ##  ##   ##  ##            ##  ##     ##     ##  ##   ##  ##  ##  ##              ## ##     ##    ##   ##   ##  ##  # ## ##" << endl;
    cout << "  ##      ##  ##   ##                ##         ##     ##       ##  ##  ##  ##             # ## #     ##    ##        ##  ##    ##    " << endl;
    cout << "  ##      ## ###   ## ##             ## ##      ##     ## ##    ## ##    ## ##             ## ##      ##    ##  ###   ## ###    ##    " << endl;
    cout << "  ##      ##  ##   ##                ##         ##     ##       ## ##     ##               ##  ##     ##    ##   ##   ##  ##    ##    " << endl;
    cout << "  ##      ##  ##   ##  ##            ##         ##     ##  ##   ##  ##    ##               ##  ##     ##    ##   ##   ##  ##    ##    " << endl;
    cout << " ####    ###  ##  ### ###           ####       ####   ### ###  #### ##    ##              ###  ##    ####    ## ##   ###  ##   ####   " << endl;
    cout << "                                                                                                                                         " << endl;
    cout << "Enter your Option" << endl;
    cout << "1.Start Game" << endl;
    cout << "2.See Instructions" << endl;
    cout << "3.Exit" << endl;
    cout << "4.Resume" << endl;

    cout << "Enter your choice:" << endl;
    cin >> option;
}
void GameWon()
{
    SetConsoleTextAttribute(acolor, 13);
    system("cls");
    cout << "##  ##    ## ##   ##  ###           ##   ##   ## ##   ###  ##" << endl;
    cout << "##  ##   ##   ##  ##   ##           ##   ##  ##   ##    ## ##" << endl;
    cout << "##  ##   ##   ##  ##   ##           ##   ##  ##   ##   # ## #" << endl;
    cout << " ## ##   ##   ##  ##   ##           ## # ##  ##   ##   ## ## " << endl;
    cout << "  ##     ##   ##  ##   ##           # ### #  ##   ##   ##  ##" << endl;
    cout << "  ##     ##   ##  ##   ##            ## ##   ##   ##   ##  ##" << endl;
    cout << "  ##      ## ##    ## ##            ##   ##   ## ##   ###  ##" << endl;

    cout << "                                                                               " << endl;
    cout << "YOUR SCORE IS:" << score;
}
void Instructions()
{
    cout << "***********************************************************INSTRUCTIONS**************************************************************" << endl;
    cout << "*************************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************************" << endl;
    cout << "01.The Character Fire boy has 3 lives. He has to escape from the 3 ghosts" << endl;
    cout << "02.There are three ghosts in the first level Fyre,Oogy and Fang. Oogy is the intelligent ghost. He..........Fyre moves horizontal and Fang moves vertical" << endl;
    cout << "03.If bullet attacks fireboy his score decreases and if he touches the ghosts his lives decreases. Fireboy will die if his lives become zero" << endl;
    cout << "04.Ghosts also has lives that decreaes on being attacked by bullet" << endl;
    cout << "05.If fire boy touches water his lives will decrease" << endl;
    cout << "You will reach level 2 on getting the key" << endl;
    cout << "There will be four ghosts in 2nd level" << endl;
    cout << "                                                                               " << endl;
    cout << "                                                                               " << endl;
    cout << "***********************************************************INSTRUCTIONS FOR KEYS*****************************************************" << endl;
    cout << "*************************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************************" << endl;
    cout << "01.Use up down key to jump" << endl;
    cout << "02. use left right key move left or right" << endl;
    cout << "03.use space to fire" << endl;
}

//file handling for resuming  game
void ScoreToFile()
{

    fstream file;
    file.open("store.txt", ios::out);
    if (score > 0 || score > 0)
    {
    file << score << endl;
    file << Fx << endl;
    file << Fy << endl;
    file << Gx << endl;
    file << Gy << endl;
    file << gx << endl;
    file << gy << endl;
    file << Fyre_X << endl;
    file << Fyre_Y << endl;
    file << printHealthOfOggy << endl;
    file <<printHealthOfFangy << endl;

    file.close();
    if (lives < 0)
    {
        file.open("store.txt", ios::out);
        file << 0 << endl;
        file << 22 << endl;
        file << 44 << endl;
        file << 130 << endl;
        file << 8 << endl;
        file << 110 << endl;
        file << 25 << endl;
        file << 12 << endl;
        file << 44 << endl;
         file << 100<< endl;
        file << 100 << endl;
    }
    }
 
    else if(score==0)
    {
        score=0;
        file << 0 << endl;
        file << 22 << endl;
        file << 44 << endl;
        file << 130 << endl;
        file << 8 << endl;
        file << 110 << endl;
        file << 25 << endl;
        file << 12 << endl;
        file << 44 << endl;
         file << 100<< endl;
        file << 100 << endl;
    }

}
 void ScoreToArray()
{
   int collect1=0;
   int collect2=0;
   int collect3=0;
   int collect4=0;
   int collect5=0;
   int collect6=0;
   int collect7=0;
   int collect8=0;
   int collect9=0;
   int collect10=0;
   int collect11=0;

   fstream file;
   file.open("store.txt",ios:: in);
   file>>collect1;
   file>>collect2;
   file>>collect3;
   file>>collect4;
   file>>collect5;
   file>>collect6;
   file>>collect7;
   file>>collect8;
   file>>collect9;
   file>>collect10;
   file>>collect11;

   score=collect1;
   Fx=collect2;
   Fy=collect3;
   Gx=collect4;
   Gy=collect5;
   gx=collect6;
   gy=collect7;
   Fyre_X=collect8;
  Fyre_Y=collect9;
  Oggy_Health=collect10;
  Fangy_Health=collect11;

  file.close();
}