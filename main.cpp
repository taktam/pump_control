#include <Arduino.h>
#include "pump.h"

sensor *top = new sensor(A0);
sensor *bottom = new sensor(A1);
relay *pump = new relay (13);
led *red = new led (2);
led *yellow = new led (3);
led *green = new led (4);

//display temperature
void showTemp()
{
  if ((pump->getStatus())==true)
  {
    Serial.println("Pump on");
  }
  else
  {
    Serial.println("Pump off");
  }
  Serial.print("Top:\t");
  Serial.println(top->temperature());
  Serial.print("Bottom:\t");
  Serial.println(bottom->temperature());
  Serial.println("-----------");
}

void setup() {
  red->blink(2);
  yellow->blink(2);
  green->blink(2);
  green->on();
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2));
  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);
  ADMUX = bit (REFS0) | bit (REFS1);
  Serial.begin(9600);
}

void loop() {

  if ((pump->sense()) == true)
  {
    Serial.println ("Control off");
    yellow->on();
  }
  else
  {

  yellow->off();

  if (((top->voltage())<(0.5))|((top->voltage())>(4.0)))
  {
    Serial.println("Error (Top Sensor)");
    red->blink(3);
  }

  if (((bottom->voltage())<(0.5))|((bottom->voltage())>(4.0)))
  {
    Serial.println("Error (Bottom Sensor)");
    red->blink(3);
  }

  if ((top->temperature() > 40.0))
  {
    do
    {
      yellow->on();
      pump->on();
      showTemp();
      if (top->temperature() < 35.0)
      {
        break;
      }
    }
    while (bottom->temperature() < 37.5);
    
    pump->off();
    yellow->off();
  } 
  showTemp();
  }
  delay (1000);
}