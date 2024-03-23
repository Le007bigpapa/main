/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
 * Modif : Janvier 2023, Compatible VisualStudio, JpGouin
*/



#include "./src/libs/map.h"
#include "communication.h"





int main(){
    
    #define TEST 1

    if(TEST != 1)
    {
        Map map;
        std::string raw_msg;

        // Initialisation du port de communication
        /*std::string com;
        std::cout << "Entrer le port de communication du Arduino: ";
        cin >> com;
        arduino = new SerialPort(com.c_str(), BAUD);*/
        
        char com[] = "\\\\.\\COM4"; 
        arduino = new SerialPort(com, BAUD);
        if(!arduino->isConnected()){
            std::cerr << "Impossible de se connecter au port "<< std::string(com) <<". Fermeture du programme!" <<std::endl;
            exit(1);
        }
        
        // Structure de donnees JSON pour envoie et reception
        int led_state = 1;
        json j_msg_send, j_msg_rcv;

        // Boucle pour tester la communication bidirectionnelle Arduino-PC
        while(1)
        {
            if(!RcvFromSerial(arduino, raw_msg)){
                std::cerr << "Erreur lors de la reception du message. " << std::endl;
            }
            
            // Impression du message de l'Arduino si valide
            if(raw_msg.size()>0){
                //std::cout << "raw_msg: " << raw_msg << std::endl;  // debug
                // Transfert du message en json
                j_msg_rcv = json::parse(raw_msg);
                std::cout << "Message de l'Arduino: " << j_msg_rcv << std::endl;
            }

            if(j_msg_rcv["btn_180"] == "HIGH")
            {
                map.activeCell->move(DOWN);
            }

            if(j_msg_rcv["btn_up"] == "HIGH")
            {
                map.activeCell->move(UP);
            }

            if(j_msg_rcv["btn_left"] == "HIGH")
            {
                map.activeCell->move(LEFT);
            }

            if(j_msg_rcv["btn_right"] == "HIGH")
            {
                map.activeCell->move(RIGHT);
            }
            
            map.printMap();
            Sleep(1000); // 1000ms
        }
    }

    if(TEST == 1)
    {
        Map map;
        std::cout << "Test de la classe Map" << std::endl;;
        

        while(true)
        {
            
            map.printMap();
            char input;

            std::cin >> input;
            //std::cout<< "input "<<input<<std::endl;
            
            switch (input)
            {

            case 'w':
                map.activeCell->move(UP);
                break;
            
            case 'a':
                map.activeCell->move(LEFT);
                break;
            
            case 's':
                map.activeCell->move(DOWN);
                break;
            case 'd':
                map.activeCell->move(RIGHT);
                break;
                
                

            }
            
            map.updateMap();
            //system("cls");
        }
    }

    return 0;
}




