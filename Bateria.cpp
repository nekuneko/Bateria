#include "Bateria.h"

Bateria::Bateria (float maxVol, float minVol, float maxVolDivTen, float minVolDivTen, int pinBateria)
: maxVol       (maxVol)      , 
  minVol       (minVol)      , 
  maxVolDivTen (maxVolDivTen),
  minVolDivTen (minVolDivTen),
  pinBateria   (pinBateria)  ,
  maxVolAnalog (BATERIA_H_MAX_VOL_ANALOGICO),
  minVolAnalog (minVolDivTen * BATERIA_H_MAX_VOL_ANALOGICO / maxVolDivTen)
{
    // Asociación de la batería a un pin
    pinMode(pinBateria, INPUT);

    // Relé del sistema encendido
}

void Bateria::leer ()
{
  volAnalog = analogRead(pinBateria);
 
  if (volAnalog < minVolAnalog)
  {
    porcentajeC  = 0;      //  0 %
    voltajeB     = maxVol; // voltaje máximo teórico de la batería
  }
  else if (volAnalog > maxVolAnalog)
  {
    porcentajeC  = 99;     // 99 %
    voltajeB     = minVol; // voltaje mínimo teórico de la batería
  } 
  else // (minVolDigital <= volDigital && volDigital <= maxVolDigital)
  {
    porcentajeC  = map(volAnalog, minVolAnalog, maxVolAnalog, 0, 99); // no se puede hacer regla de tres, porque es un rango discreto acotado
    voltajeB     = volAnalog * maxVol / maxVolAnalog; // no se puede usar map porque devuelve un long
  } 
  
}

void Bateria::datos ()
{
  Serial.println("--- Datos de la batería ---");

  Serial.print("Pin de la Bateria:     ");
  Serial.println(pinBateria);

  Serial.print("Voltaje maximo:        ");
  Serial.println(maxVol);

  Serial.print("Voltaje minimo:        ");
  Serial.println(minVol);

  Serial.print("Voltaje maximo DT:     ");
  Serial.println(maxVolDivTen);

  Serial.print("Voltaje minimo DT:     ");
  Serial.println(minVolDivTen);

  Serial.print("Voltaje maximo Analog: ");
  Serial.println(maxVolAnalog);

  Serial.print("Ultimo Voltaje Analog: ");
  Serial.println(volAnalog);

  Serial.print("Voltaje minimo Analog: ");
  Serial.println(minVolAnalog);

  Serial.print("Voltaje actual:        ");
  Serial.println(voltajeB);

  Serial.print("Porcentaje:            ");
  Serial.println(porcentajeC);

  Serial.println("---------------------\n");
}
