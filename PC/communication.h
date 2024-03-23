#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>


/*-------------------------- Librairies externes ----------------------------*/

#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"
using json = nlohmann::json;

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 9600           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message


/*------------------------- Prototypes de fonctions -------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg);
bool RcvFromSerial(SerialPort *arduino, std::string &msg);


/*---------------------------- Variables globales ---------------------------*/
extern SerialPort * arduino; //doit etre un objet global!

#endif