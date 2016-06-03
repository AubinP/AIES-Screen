#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <cstdlib>
#include <wiringPi.h>
#include <stdio.h>
#include<stdlib.h>

#include <ccapteur.h>

#define capt 0
#define LED 2

using namespace std;

CCapteur::CCapteur()
{
    var1 = 0;
    wiringPiSetup();
    pinMode (LED, OUTPUT) ;
    pinMode(capt, INPUT);
}

float CCapteur::getTemp()
{
    system("find /sys/bus/w1/devices/ -name \"28-*\" -exec cat {}/w1_slave \\; | grep \"t=\" | awk -F \"t=\" '{print $2/1000}' > tab");
    //aller dans le dossier puis rechercher le caractère 't=', imprimer cette ligne et afficher la valeur qui commence a la cellule 2 que l'on divise par 1000
    //on le copie dans tab dans le repertoire local


    char temp[6] = "tab"; // variable qui contient le nom du fichier a ouvrir
    float var; //variable qui contiendra le resultat de la mesure

    ifstream entree (temp, ios::in); //ouvrir le fichier tab
    char T[6];
    entree.read( T , 6 ); //recopie le contenu du fichier (5chiffres + \0 dans un tableau
    entree.close();

    var = ( T[0] - '0' ) * 100 + ( T[1] - '0' ) * 10 + ( T[3] -'0' ); // la partie entiere est utilise ainsi que le premier decimale
    var /= 10;
    return var;
}

bool CCapteur::getPresence()
{
    var1 = digitalRead(capt);
    if(var1)     //var ==1
    {
        digitalWrite(LED, 1); //LED ON
        return true;
    }
    else
    {
        digitalWrite(LED, 0); //LED OFF
        return false;
    }
}

void CCapteur::putinStandby()
{
    system("echo \"standby 0000 \" | cec-client -d 1 -s \"standby 0\" RPI");   //mise en veille
}

void CCapteur::putinOn()
{
    system("echo \"on 0000 \" | cec-client -d 1 -s \"standby 0\" RPI");   //allumer le téléviseur
}
