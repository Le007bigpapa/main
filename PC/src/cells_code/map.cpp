/*
	S'ASSURER QUE LA HAUTEUR ET LA LARGEUR SOIT BIEN DÉFINIS DANS MAP.TXT
*/


#include "../libs/map.h"






#include <fstream>
#include <string>
#include <iostream>
#include <sstream>





Map::Map()
{
	std::ifstream carte("map.txt");
	if (carte.fail()) {
		std::cerr << "Erreur d'ouverture du fichier" << std::endl;
		// Gérer l'erreur ici, peut-être en quittant la fonction ou en lançant une exception
	}
	std::string lecture;


	std::getline(carte, lecture);
	//Ramasse la hauteur de la map dans le fichier map
	hauteur = std::stoi(lecture);	

	//std::cout<< "Hauteur : " <<hauteur<<std::endl;

	std::getline(carte, lecture);

	largeur = std::stoi(lecture);				//Ramasse la largeur de la map dans les fichiers
	
	//std::cout<< "Largeur : " <<largeur<<std::endl;

	// Créer un tableau de pointeurs

	this->cell = new Cell**[largeur];
	
	// Pour chaque pointeur, créer un tableau
	for(int i = 0; i < largeur; i++) 
	{
		cell[i] = new Cell*[hauteur];
	}			//Cree le tableau de cellule de la map
		
	coordonne = new int*[hauteur];					//Cree le tableau des coordonne de cases de la map
	for (int i = 0; i < hauteur; ++i) 
	{
		coordonne[i] = new int[largeur];
	}
	
	for(int y=0; y<hauteur; y++) {
		for(int x=0; x<largeur; x++) {
			std::getline(carte, lecture, x == largeur - 1 ? '\n' : ' ');
			coordonne[x][y] = std::stoi(lecture);
			int type = std::stoi(lecture);
			if(type != 6 && type < 3000)
			{
				cell[x][y] = new Cell(type);
			}
			else if(type < 3000)
			{
				cell[x][y] = new IntersectionCell(type);
			}

			else
			{
				printf("type : GameCell%d\n", type);
				cell[x][y] = new GameCell(type);
			}
			
			//cell[x][y]->printCell();
		}
	}


	
	for(int x=0; x<largeur; x++)	//Assigne les pointeurs des cases autour de chaque case
	{
		for(int y=0; y<hauteur;y++)
			{	//printf("type : %d\n", *cell[x][y]->getType()); //Les print ici c'est pour le debug
				if(*cell[x][y]->getType()!=0)
				{	
					
					if(y+1 < hauteur && *cell[x][y+1]->getType()>0) 
					{
						cell[x][y]->setCellAround(south, cell[x][y+1]);
					}
					else
					{
						cell[x][y]->setCellAround(south, NULL);
					}

					if(y-1 >= 0 && *cell[x][y-1]->getType()>0)
					{
						cell[x][y]->setCellAround(north, cell[x][y-1]);
					}
					else
					{
						cell[x][y]->setCellAround(north, NULL);
					}

					if(x+1 < largeur && *cell[x+1][y]->getType()>0)
					{
						cell[x][y]->setCellAround(east, cell[x+1][y]);
					}
					else
					{
						cell[x][y]->setCellAround(east, NULL);
					}

					if(x-1 >= 0 && *cell[x-1][y]->getType()>0)
					{
						cell[x][y]->setCellAround(west, cell[x-1][y]);
					}
					else
					{
						cell[x][y]->setCellAround(west, NULL);
					}

				}
			}
	}

	

	for(int i=0;i<maxRoom;i++)
	{	
		cle[i]=0;
	}
	
		
	activeCell = new ActiveCell();
	activeCell->cpyCell(cell[6][3]); //Ici je place le joueur dans la case 1,1
	
	cell[2][1]->setKeyToUnlock(1); //Ici je dis que la case 2,1 a besoin de la cle 1 pour etre debloquee
	cell[3][5]->setKeyToUnlock(2); //Ici je dis que la case 3,5 a besoin de la cle 2 pour etre debloquee

}

Map::~Map()
{
	//std::cout<<"Destruction de la map"<<std::endl;
	for (int i = 0; i < largeur; ++i) 
	{
		for(int j = 0; j < hauteur; j++)
		{
			delete cell[i][j];
		}
		delete[] cell[i];
	}

	delete[] cell;
	
	for (int i = 0; i < hauteur; ++i) 
	{
    	delete[] coordonne[i];
	}

	delete[] coordonne;
	delete activeCell;

}




void Map::printMap()
{
	
	system("cls");
	for(int y=0;y<hauteur;y++)
	{
		for(int i=0;i<3;i++)
		{
			for(int x=0;x<largeur;x++)
			{
				for(int k=0; k<3; k++)
				{
					std::cout << cell[x][y]->imageCell[i][k];
				}
			}
			std::cout << std::endl;
		}
		
	}
	std::cout << "\x1b[0m";


}

void Map::addCle(int index)
{
	cle[index]=index;
}

void Map::removeCle(int index)
{
	cle[index]=0;
}

bool Map::verifCle(int index)
{
	if(index==cle[index])
	{
		return true;
	} else return false;
}


void Map::updateMap()
{
	
	for(int y=0;y<this->hauteur;y++)
	{
		for(int x=0;x<this->largeur;x++)
		{
			cell[x][y]->setImageCell(cell[x][y]);
		}
	}
	
	activeCell->setImageCell(activeCell);
}

