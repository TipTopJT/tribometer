#include <Wire.h>
#include <avr/wdt.h>
#define SLAVE_ADDRESS 0x08

int buf= 70;
volatile unsigned long time[70];
int tic=0;
int RPM; 
unsigned long t=0;

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT); 
  attachInterrupt(digitalPinToInterrupt(2), tickk, FALLING); 
  wdt_enable(WDTO_8S); 
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(sendData);
 
}

void sendData()
{
 if(tic<buf - 1)
 {
   RPM=buf*60000/(millis()-time[tic+1]);
   Serial.println(RPM);  
  }
 if(tic==buf-1)
 {
   RPM=buf*60000/(millis()-time[0]);
   Serial.println(RPM);
 }   
 Wire.write((const uint8_t*)&RPM,4);
   
}



void loop()
{
 wdt_reset();
}

void tickk() 
{ 
  time[tic]=millis();
  tic++; 
  if(tic>=buf) 
  {
    tic=0;
  }
}
