#include "pump.h"
#include <Arduino.h>
#include <Thermistor.h>
#include <NTC_Thermistor.h>

sensor::sensor(int analog_in)
{
    in_pin = analog_in;
}

int sensor::read()
{
    return analogRead(in_pin);
}

float sensor::voltage()
{
    return (read()*5.0/1023);
}

float sensor::temperature()
{
    Thermistor* thermistor;
    thermistor = new NTC_Thermistor(
    in_pin,
    10000,
    10000,
    25,
    3500
  );
  const double celsius = thermistor->readCelsius();
  delete thermistor;
  return celsius;
}

relay::relay(int digital_out)
{
    out_pin = digital_out; 
    pinMode(out_pin, OUTPUT);
    digitalWrite(out_pin, LOW);
    setStatus(false);
}

void relay::on()
{
    digitalWrite(out_pin, HIGH);
    setStatus(true);
    delay(8000);
}

void relay::off()
{
    digitalWrite(out_pin, LOW);
    setStatus(false);
}

bool relay::sense()
{
    pinMode(out_pin, INPUT);
    bool isON;
    if ((digitalRead(out_pin))==true)
    {
        isON = true;
    }
    else
    {
        isON = false;
    }
    pinMode(out_pin, OUTPUT);
    return isON;
}

void relay::setStatus (bool stat)
{
    status = stat;
}

bool relay::getStatus()
{
    return status;
}

led::led(int digital_out)
{
    out_pin = digital_out;
    pinMode (out_pin, OUTPUT);
    digitalWrite(out_pin, LOW);
}

void led::on()
{
    digitalWrite(out_pin, HIGH);
}

void led::off()
{
    digitalWrite(out_pin, LOW);
}

void led::blink(int nr)
{
    int delay_ms = 300;
    for (int i = 0; i < nr; i++)
    {
        digitalWrite(out_pin, HIGH);
        delay (delay_ms);
        digitalWrite(out_pin, LOW);
        delay (delay_ms);
    }
}