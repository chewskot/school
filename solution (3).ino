#include "funshield.h"

int prevMill = 0;
const int interval = 300;

const int pins[] = {led1_pin, led2_pin, led3_pin, led4_pin};
const int range = sizeof(pins)/sizeof(pins[0]);
int curLED = 0;
int stav = 1;
//int semafor_stav = 1;
//int citac = 0;
//auto curMill = millis();
void ledka_yes(int i)
{
  digitalWrite(pins[i],LOW);
}
// vypnuti ledky
void ledka_no(int i)
{
  digitalWrite(pins[i],HIGH);
}
void setup() {
  for (int i = 0; i < range; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }
}
/*

 
void blinkings(int inter)
{
  int curMill = millis();
  
  if (curMill - prevMill >= interval)
  {
    prevMill = curMill; 
    prevMill = curMill;
    ledka_yes(0);
  }
  else
  {   
    ledka_no(0);

  }
}
void semafor()
{

 int curMill = millis();
  
  if (curMill - prevMill >= interval)
  {
    prevMill = curMill;
     for (int i = 0; i < range; i+=2) 
    {
      if (semafor_stav == true)
      {
        ledka_yes(i);
        ledka_no(i+1);
      } 
      else
      {
        ledka_no(i);
        ledka_yes(i+1);
      }    
    } 
    semafor_stav = !semafor_stav;   
  } 
}
 
void bin()
{
  int curMill = millis();
  
  if (curMill - prevMill >= interval)
  {
    prevMill = curMill;
    citac++;
    prevMill = curMill;   
    for(int i=0; i<range;i++)
    {
      int bit_poloha = 1 << i;
      int bit_hodnota;
      bit_hodnota = bit_poloha & citac;
      if (bit_hodnota != 0)
      { 
        ledka_yes(i);
      }
      else
      {
        ledka_no(i);
      } 
    }
   }
}

*/
void pong()
{
  int curMill = millis();
  ledka_yes(curLED);
  if (curMill - prevMill >= interval)
  {
    prevMill = curMill;
    if (curLED == 0) {
      stav = 1;
    }
    if (curLED == range-1) {
      stav = -1;
    }
    ledka_no(curLED);
    curLED += stav;
    ledka_yes(curLED);
    }
}

void loop()
{
  pong();
  
}
