#include "../libs/gameCell.h"
#include "../libs/minigames.h"


MiniGame minigame;

GameCell::GameCell(int type)
{
    std::cout << "Constructeur GameCell" << std::endl;
    cell_north = new Cell;
    cell_south = new Cell;
    cell_east = new Cell;
    cell_west = new Cell;
    this->type = type;

    this->setImageCell(this);
}

GameCell::~GameCell()
{
    delete cell_north;
    delete cell_south;
    delete cell_east;
    delete cell_west;

    this->setImageCell(this);
}

Cell *GameCell::enterCell(int *orientation, int key[maxRoom], int direction)
{
    int inverseOrientation[] = {south, west, north, east};
    switch(type)
    {
        case(3022):
            l3022();
            break;
        case(3019):
            l3019();
            break;
        case(3018):
            l3018();
            break;
        case(3041):
            l3041();
            break;
        case(3016):
            l3016();
            break;
        case(3024):
            l3024();
            break;
    }

    *orientation = inverseOrientation[*orientation];
    return this->getCellAround(*orientation);


}

void GameCell::setImageCell(Cell *cell)
{
    std::string RESET  = "\x1b[0m";
    std::string BLACK  = "\x1b[30m";      /* Black */
    std::string RED    = "\x1b[31m";      /* Red */
    std::string GREEN  = "\x1b[32m";      /* Green */
    std::string YELLOW = "\x1b[33m";      /* Yellow */
    std::string BLUE   = "\x1b[34m";      /* Blue */
    std::string MAGENTA = "\x1b[35m";      /* Magenta */
    std::string CYAN   = "\x1b[36m";      /* Cyan */
    std::string WHITE  = "\x1b[37m";      /* White */
    std::string typeColor;

    typeColor = GREEN;

    for(int i=0; i<3; i++)
    {
        for(int y=0; y<3; y++)
            {
                {
                    imageCell[i][y] = typeColor+"0";
                }
            }
    }

    switch (this->type)
    {
        case 3022:
            imageCell[1][2] = BLUE+"X";
            break;
        case 3019:
            imageCell[1][0] = BLUE+"X";
            break;
        case 3018:
            imageCell[1][0] = BLUE+"X";
            break;
        case 3041:
            imageCell[1][2] = BLUE+"X";
            break;
        case 3016:
            imageCell[1][0] = BLUE+"X";
            break;
        case 3024:
            imageCell[1][2] = BLUE+"X";
            break;
    
    }
}

void GameCell::l3022()
{
    system("cls");
    std::cout << "Jeu local 3022" << std::endl;
    minigame.play_resistanceGame();
    
}

void GameCell::l3019()
{
    system("cls");
    std::cout << "Jeu local 3019" << std::endl;
    char wait;
    std::cin >> wait;
}

void GameCell::l3018()
{
    system("cls");
    std::cout << "Jeu local 3018" << std::endl;
    char wait;
    std::cin >> wait;
}

void GameCell::l3041()
{  
    system("cls");
    minigame.play_proceduralGame();
    char wait;
    std::cin >> wait;
}

void GameCell::l3016()
{
    system("cls");
    std::cout << "Jeu local 3041" << std::endl;
    char wait;
    std::cin >> wait;
}

void GameCell::l3024()
{
    system("cls");
    std::cout << "Jeu local 3024" << std::endl;
    char wait;
    std::cin >> wait;
}

