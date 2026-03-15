// system("cls"); This is use to clear the screen
#include<iostream>
#include <thread>
#include <chrono> // work with time.
using namespace std;

void message(string msg);
void clearScreen();
void drawMap();
void movement(char move);

enum GameState
{
    CONTINUE,
    COLLIDE,
    LOSE,
    WIN
};
struct vec2
{
    int x;
    int y;
    vec2() : x(0), y(0) {}
    vec2(int xVal, int yVal) : x(xVal), y(yVal) {}
};
struct player
{
    string name;
    vec2 position;
    int health;
    int move;
};

// void wait(int ms)
// {
//     std::this_thread::sleep_for(std::chrono::milliseconds(ms));
// }

const int N = 20; // This is const because it can change any time without const

char map[N][N] =
{
{'S','.','.','|','.','.','.','.','.','.','|','.','.','.','.','E','.','.','.','.'},
{'.','|','.','|','.','E','.','|','.','.','|','.','|','.','.','.','.','|','.','.'},
{'.','|','.','.','.','.','.','|','.','.','.','.','|','.','E','.','.','|','.','.'},
{'.','|','|','|','.','|','.','|','E','.','.','.','|','.','.','.','.','|','.','.'},
{'.','.','.','.','.','|','.','.','.','.','|','.','.','.','|','.','.','.','.','.'},
{'|','|','|','.','E','|','|','|','.','.','|','.','|','.','|','.','|','|','|','.'},
{'.','.','.','.','.','.','.','.','.','.','.','.','|','.','.','.','.','.','|','.'},
{'.','E','.','|','.','|','|','|','.','|','.','.','|','.','|','|','|','.','|','.'},
{'.','.','.','|','.','.','.','|','.','|','.','E','.','.','.','.','|','.','.','.'},
{'|','|','.','|','|','|','.','|','.','|','.','.','|','|','|','.','|','|','|','.'},
{'.','.','.','.','.','|','.','.','.','|','.','.','.','.','|','.','.','.','.','.'},
{'.','|','|','|','.','|','|','|','.','|','|','|','|','.','|','.','|','|','|','.'},
{'.','.','.','|','.','.','.','.','.','.','.','.','|','.','.','.','|','.','.','.'},
{'.','E','.','|','|','|','|','|','|','|','|','.','|','E','.','|','|','.','|','.'},
{'.','.','.','.','.','.','.','.','.','.','|','.','.','.','.','.','.','.','|','.'},
{'|','|','|','|','.','|','|','|','|','.','|','|','|','|','|','|','.','|','|','.'},
{'.','.','.','|','.','.','.','.','|','.','.','.','.','.','.','|','.','.','.','.'},
{'.','|','.','|','|','|','.','.','|','|','|','|','|','|','.','|','|','|','.','.'},
{'.','|','.','.','.','.','.','E','.','.','.','.','.','.','.','.','.','.','.','G'},
{'.','|','|','|','|','|','|','|','|','|','|','|','|','|','|','|','|','|','.','.'}
};

// rendering part (clearing and redrawing the things)
void clearScreen()
{
    system("cls");
}

void drawMap()
{
    for(int i=0;i<N;i++)
    {
        for(int j =0;j<N;j++)
        {
            cout<<map[i][j]<<"  ";
        }
        cout<<endl;
    }
}
void message(string msg)
{
    cout<<msg<<endl;
}

GameState movement(char move,player &pl)
{
    int x = 0;
    int y = 0;
    switch (move)
    {
        case 'a':
        {
            // message("you press A");
            y -= 1;
            break;
        }
        case 'd':
        {
            // message("you press D");
            y += 1;
            break;
        }
        case 'w':
        {
            // message("you press W");
            x -= 1;
            break;
        }
        case 's':
        {
            // message("you press S");
            x += 1;
            break;
        }
    }
    pl.move += 1;
    int i = pl.position.x;
    int j = pl.position.y;
    int nX = pl.position.x+x;
    int nY = pl.position.y+y;
    if(nX < 0 || nX >= N || nY < 0 || nY >= N)
    {
        message("You can't move outside map");
        cin.get();
        return CONTINUE;
    }
    if(map[nX][nY] == '|')
    {
        message("You can't able to move wall is there.");
        message("AAAAaaaa!!! I hurt");
        cin.get();
        return COLLIDE;
    }
    else if(map[nX][nY]== 'E')
    {
        pl.health -= 40;
        message("Enemy attacked you");
        message("AAAAaaaa!!! I hurt");
        cin.get();
        map[i][j] = 'S';
        map[nX][nY] = 'E';
        if(pl.health<=0)
        {
            message("AAAaaaaaa!!!! I Dieeingggg.... Help me");
            message("GameOver");
            cin.get();
            return LOSE;
        }
        return CONTINUE;

    }
    else if(map[nX][nY]=='G')
    {
        message("Hoo ! I found the Gate lets run way");
        message("Haa What is this !!!!!");
        message("No this is not an exit ");
        cin.get();
        return WIN;
    }
    else
    {
        map[i][j] = '.';
        map[nX][nY] = 'S';
        pl.position.x = nX;
        pl.position.y = nY;
        return CONTINUE;
    }
}

int main()
{
    clearScreen();
    message("Welcome to ninja world press A to start the game");
    message("You can control the game using W S A D key for up down left right");
    char press;
    cin>>press;
    bool running = false;

    player pl;
    pl.name = "Sam";
    pl.position = vec2(0,0);
    pl.health = 100;
    pl.move = 0;

    if (press=='a' || press=='A')
    {
        running = true;
    }
    else if(press == 'p')
    {
        message("you unlock secrete key you scored rank 1st !!!!!");
    }
    else
    {
        message("GameOver you press wrong key");
    }
    while(running)
    {
        char move;
        clearScreen();
        drawMap();
        cout<<pl.health;
        cin>>move;
        GameState check = movement(move,pl);
        // wait(10000);
        if (check==WIN)
        {
            cout<<"you completed in "<<pl.move<<" move"<<endl;
            cout<<"your health left "<<pl.health<<"hp"<<endl;
            message("You win the game");
            running = false;
        }
        else if(check==LOSE)
        {   
            message("you loose the game");
            running = false;
        }
    }
    cin.get();
    cin.get();
    return 0;
}