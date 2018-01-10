//#include "arduino.h"
#include "Bateria.h"

Bateria::Bateria (float maxVol,        float minVol, 
                  float maxVolDivTen,  float minVolDivTen,
                  int pinBateria)
: maxVol        (maxVol)      , 
  minVol        (minVol)      , 
  maxVolDivTen  (maxVolDivTen),
  minVolDivTen  (minVolDivTen),
  pinBateria    (pinBateria)  ,
  maxVolDigital (maxVolDivTen * 1023 / 5),
  minVolDigital (minVolDivTen * 1023 / 5)
{
    // Asociación de la batería a un pin
    pinMode(pinBateria, INPUT);

    // Relé del sistema encendido
}

void Bateria::leer ()
{
  volDigital = analogRead(pinBateria);
  
  if (minVolDigital <= volDigital && volDigital <= maxVolDigital)
  {
    porcentajeC  = map(volDigital, minVolDigital, maxVolDigital, 0, 99); //volDigital * 99 / maxVolDigital;         
    voltajeB     = volDigital * maxVol / maxVolDigital; //map(volDigital, minVolDigital, maxVolDigital, minVol, maxVol);
  } 
  else if (volDigital < minVolDigital)
  {
    porcentajeC  = 0;            //  0 %
    voltajeB     = volDigital * maxVol / maxVolDigital; //map(volDigital, minVolDigital, maxVolDigital, minVol, maxVol);

    //voltajeB     = minVol;
  }
  else // (maxVolDigital < volDigital)
  {
    porcentajeC  = 99;          // 99 %
    voltajeB     = volDigital * maxVol / maxVolDigital; //map(volDigital, minVolDigital, maxVolDigital, minVol, maxVol);

    //voltajeB     = maxVol; 
  }
  
}

void Bateria::datos ()
{
  Serial.println("\n------ Bateria ------");

  Serial.print("Pin de la Bateria:  ");
  Serial.println(pinBateria);

  Serial.print("Voltaje maximo:     ");
  Serial.println(maxVol);

  Serial.print("Voltaje minimo:     ");
  Serial.println(minVol);

  Serial.print("Voltaje maximo DT:  ");
  Serial.println(maxVolDivTen);

  Serial.print("Voltaje minimo DT:  ");
  Serial.println(minVolDivTen);

  Serial.print("Voltaje maximo Dig: ");
  Serial.println(maxVolDigital);

  Serial.print("Voltaje minimo Dig: ");
  Serial.println(minVolDigital);

  Serial.print("Ultimo Voltaje Dig: ");
  Serial.println(volDigital);

  Serial.print("Voltaje:    ");
  Serial.println(voltajeB);

  Serial.print("Porcentaje: ");
  Serial.println(porcentajeC);

  Serial.println("---------------------\n");
}