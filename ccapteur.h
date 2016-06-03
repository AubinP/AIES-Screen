#ifndef CCAPTEUR_H
#define CCAPTEUR_H

#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <cstdlib>
#include "wiringPi.h"
#include <stdio.h>
#include <stdlib.h>


class CCapteur
{
public:
   CCapteur();
   float getTemp();
   bool getPresence();
   void putinStandby();
   void putinOn();
private:
   int var1;
};

#endif // CCAPTEUR_H

