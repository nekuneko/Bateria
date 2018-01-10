#include "Bateria.h"

const float maxVol = 8.4; // Voltios. El diodo de protecciónconsume 0.83 voltios
const float minVol = 7.3; // Voltios.
const float R1 = 10000; // Ohmios
const float R2 = 6800;  // Ohmios
const float corriente = 2200; // mAh
const float maxVolDivTen = R1/(R2+R1)*maxVol;
const float minVolDivTen = R1/(R2+R1)*minVol;
const int pinBateria = A0;  // Pin A0, entrada analogica A0


Bateria bateria(maxVol, minVol, maxVolDivTen, minVolDivTen, pinBateria);

void setup() 
{
  Serial.begin(115200);
  
  while(!Serial);
  Serial.println("¡Serial iniciado!");
}

void loop() 
{
  bateria.leer();
  bateria.datos();

  Serial.println();
  Serial.println();

  delay(1000);
}
