#ifndef PUMP_H
#define PUMP_H

//pt1000 sensors
class sensor
{
private:
    int in_pin;
    
public:    
    sensor(int);
    int read();
    float voltage();
    float temperature();
};

//actor (solid state relay)
class relay
{
private:
    int out_pin;
    bool status;

public:
    relay(int);
    void on();
    void off();
    bool sense();
    void setStatus(bool);
    bool getStatus();
};

//status leds
class led
{
private:
    int out_pin;
public:
    led(int);
    void on();
    void off();
    void blink(int);
};

#endif