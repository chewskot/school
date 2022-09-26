#include "funshield.h"

constexpr int ledPins[] { led1_pin, led2_pin, led3_pin, led4_pin };
constexpr int ledPinsCount = sizeof(ledPins) / sizeof(ledPins[0]);
constexpr int buttonPins[] { button1_pin, button2_pin, button3_pin };
constexpr int buttonPinsCount = sizeof(buttonPins) / sizeof(buttonPins[0]);

constexpr int activationDelay = 1000; // how long before button starts to perform periodic updates [ms]
constexpr int periodicDelay = 300; // delay between consecutive periodic updates [ms]

constexpr int maxInt = 1 << ledPinsCount;

class Diode {
  private:
    int number_;
    bool status_;
  public:
    Diode() { }
    Diode(int diode) : number_(diode), status_(false) { }
    void change(bool newStatus) {
      status_ = newStatus;
      digitalWrite(ledPins[number_], status_ ? ON : OFF);
    }
    void change() {
      status_ = !status_;
      digitalWrite(ledPins[number_], status_ ? ON : OFF);
    }
};

class Button {
  private:
    int number_;
    bool status_;
    unsigned long timeNext_ = 0;
    unsigned long timeLongPress = 0;
    bool previousState_ = false;
    bool previousLongState = false;
    bool check_pressed(bool state)
    {
      if (previousState_ == false && state == true)
      {
        timeLongPress = activationDelay + millis();
        previousState_=state;
        return true;
      }
      previousState_ = state;
      return false;
    }
  public: 
   bool is_pressed_()
    {
      bool state = !digitalRead(buttonPins[number_]);
      state = check_pressed(state);
      return (state);
    }
    bool is_long_pressed_()
    {
      unsigned long timec = millis();
      bool result = false;
      bool state = !digitalRead(buttonPins[number_]);
      state = state && timec>=timeLongPress;
      if (timeNext_ <= timec && state == true)
      {
        timeNext_ = periodicDelay + timec;
        result = true; 
      }  
      previousLongState=state;
      return result;
    }
    Button() { }
    Button(int button) : number_(button), status_(false) { }
};

Diode leds[ledPinsCount];
Button buttons[buttonPinsCount];
int counter;

void setup() {

  for ( int i = 0; i < ledPinsCount; ++i ) {
    pinMode(ledPins[i], OUTPUT);
    leds[i] = Diode(i);
    leds[i].change(false);
  }

  for ( int i = 0; i < buttonPinsCount; ++i ) {
    pinMode(buttonPins[i], INPUT);
    buttons[i] = Button(i);
  }
  
  counter = 0;

}

void incrementCounter() {

  counter = ((counter + 1) % maxInt);

}

void decrementCounter() {

  counter = ((counter - 1) % maxInt);

}
//casovac pro 3.3
/*
int prevMill =0;
bool Timer(int interval)
{
  int curMill = millis();
  if (curMill - prevMill >= interval )
  {
    prevMill = curMill;
    return true;
  }
  else
  {
    return false;
  }
}
//binary s rozsvicenim
void bin(int citac)
{
    for(int i=0; i<ledPinsCount;i++)
    {
      int bit_poloha = 1 << i;
      int bit_hodnota;
      bit_hodnota = bit_poloha & citac;
      if (bit_hodnota != 0)
      { 
       leds[i].change(OFF);
      }
      else
      {
        leds[i].change(ON);
      }
    }
}
//3.1
void ButLight()
{
      for(int i =0;i < buttonPinsCount;i++)
      {
        if(digitalRead(buttonPins[0]) == false)
        {
          leds[0].change(OFF);
        }
      }
}

//3.2
bool pressed;
void ButBlink()
{
      if(digitalRead(buttonPins[0]) == false)
        {
          pressed = !pressed;
          leds[0].change(pressed);
        }  
}

//3.3
int citac;
void bincounter()
{
  bool but1 = digitalRead(buttonPins[0]);
  bool but2 = digitalRead(buttonPins[1]);
  bool but3 = digitalRead(buttonPins[2]);
    if(but1 == false)
      {
      if(Timer(200))
      {
        citac++;
      }      
    }
    else if(but2 == false)
    {
      if(Timer(200))
      {
        citac--;
      }
    }
    else if(but3 == false)
    {
      if(Timer(2000))
      {
        citac=0;
      }
    } 
  bin(citac);
}
*/
//3.4

void ukol()
{
  if(buttons[0].is_pressed_()|| buttons[0].is_long_pressed_())  
  {
    incrementCounter();
  }
  if(buttons[1].is_pressed_()|| buttons[1].is_long_pressed_())
  {
    decrementCounter();
  }
  for(int i=0; i<ledPinsCount;i++)
  {
    leds[3-i].change((counter >> i)&1);
  }
}

void loop() 
{
  //ButBlink();
  //ButLight();
  //bincounter();
  ukol();
  
}
