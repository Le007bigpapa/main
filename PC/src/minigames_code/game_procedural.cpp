#include "../libs/minigames.h"


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>

int nombre_aleatoire=5;
int nombre_phrase=8;

int random_procedural(int base)     //Génère un chiffre aleatoire entre 0 et base ( inclut 0 et exclut base)
{
/*
Note utiliser ce code ralentit l'exécution du code car time(NULL) varie très lentements donc la fonction revoit plusieurs fois d'affiller le même nombre
car la seed ne change pas.
*/
    using namespace std;
    srand(time(NULL));
    return rand() % base;

}


int MiniGame::play_proceduralGame(){
    
    int nombre_mots=0;
    using namespace std;
    vector<string> mots;
    ifstream question("procedural.txt");


    if (question.fail()) {
        cerr << "Erreur d'ouverture du fichier" << std::endl;
        return -1;
    }
    
    string lecture;

    for(int h=0;h<random_procedural(nombre_phrase);h++){
        getline(question, lecture);
    }
    

    question.close();

    stringstream ss(lecture);
    std::string mot;
    
    while (ss >> mot) {         //Sépare la phrase en plusieurs mots
        nombre_mots++;
        mots.push_back(mot);
    }

    vector<int> position_mots;
    
    cout<<"Arranger les mots suivants dans le bon ordre"<<endl;

    int index = 0;

    while(index < 5){                                       //Scramble les mots
        int position = random_procedural(5);
        if(position_mots.size() ==0){                       // Ajoute le premier mots
            position_mots.push_back(position);
            index++;
        }

        bool verif = true;
        for(int j = 0; j < position_mots.size(); j++){      //Vérifie si position est dans le vecteur qui contient l'ordre des positions 
            if(position_mots[j] == position){
                verif = false;
            }
        }

        if(verif){                                          //Si la position n'est pas dans le vecteur ajoute la position
            position_mots.push_back(position);
            index++;
        }
    }

    for(int y=0 ; y<position_mots.size(); y++)
    {
        cout << mots[position_mots[y]] << "  :  ";
    }
    cout<<endl;

    
    int count=0;
    while(count<5)
    {
        system("cls");
        cout<<" Ordre melanger : "<<endl;
        for(int y=0 ; y<position_mots.size(); y++)
        {
            cout << mots[position_mots[y]] << "  :  ";
        }

        cout<<endl;
        cout<<endl;

        cout<<" Ordre organise : "<<endl;
        for(int y=0 ; y<count; y++)
        {
            cout << mots[y] << "  :  ";
        }

        cout<<endl;

        cout<<"Entrez au clavier l'ordre dans lequel il faut mettre les mots afin de comprendre ce que voulait dire le prof"<<endl;

        int clavier;

        cin>>clavier;

        clavier--;
                    
        if(count != position_mots[clavier]){
            cout<<"Erreur le cave"<<endl;
        }
        if(count == position_mots[clavier]){
            count++;
        }
        
    }

    cout << "Felicitations vous avez reussis"<<endl;
    cout << "Voici la phrase : "<<endl;
    for(int y=0 ; y<count; y++)
    {
        cout << mots[y]<< " ";
    }

    cout<<endl;

    cout << "Appuyer sur une touche afin de retourner sur la carte" << endl;

    return 0;
    
}