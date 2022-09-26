#include "funshield.h"
constexpr int buttonPins[] { button1_pin, button2_pin, button3_pin };
constexpr int buttonPinsCount = sizeof(buttonPins) / sizeof(buttonPins[0]);
constexpr int activationDelay = 1000; // how long before button starts to perform periodic updates [ms]
constexpr int periodicDelay = 300; // delay between consecutive periodic updates [ms]
constexpr int radCount = sizeof(digit_muxpos) / sizeof(digit_muxpos[0]);
class Button {
  private:
    int number_;
    bool status_;
    long timeNext_ = 0;
    long timeLongPress = 0;
    bool previousState_ = false;
    bool previousLongState = false;
    bool check_pressed(bool state)
    {
      if (previousState_ == false && state == true)
      {
        timeLongPress = activationDelay + millis();
        previousState_ = state;
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
      long timec = millis();
      bool result = false;
      bool state = !digitalRead(buttonPins[number_]);
      state = state && timec >= timeLongPress;
      if (timeNext_ <= timec && state == true)
      {
        timeNext_ = periodicDelay + timec;
        result = true;
      }
      previousLongState = state;
      return result;
    }
    Button() { }
    Button(int button) : number_(button), status_(false) { }
};
int prevMill = 0;
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
class Display {
  private:
    int pos_ = 0;
    long data_;
  public:
    int dot = 0x7F;
    void set( long n) {
      data_ = n;
      loop();
    }
    void loop()
    {
      write_digit(data_);
    }
    int count_digit(long number)
    {
      unsigned count = 0;
      if (number <= 100)
      {
        count = 2;
      }
      else
      {
        while (number != 0) {
          number = number / 10;
          count++;
        }
      }
      return count;
    }
    void write_digit(long data)
    {
      
      long number = data/100;
      int velikost = count_digit(number);
      int pole[velikost];

      for (int i = 0; i < velikost; i++) {
        pole[i] = number % 10;
        number /= 10;
      }
      if (pos_ < velikost)
      {        
          if(pos_ != 1)
          {
            write_glyph(digits[pole[pos_]], digit_muxpos[3 - pos_]);
          }
          else
          {
            write_glyph(digits[pole[pos_]] & dot, digit_muxpos[3 - pos_]);
          }        
      }   
      pos_= ++pos_ % 4;
      
      
    }
    void write_glyph(int cislo, int pozice)
    {
      digitalWrite(latch_pin, LOW);
      shiftOut(data_pin, clock_pin, MSBFIRST, cislo);
      shiftOut(data_pin, clock_pin, MSBFIRST, pozice);
      digitalWrite(latch_pin, HIGH);
    }
};
Display d;
Button buttons[buttonPinsCount];
class Counter {
  public:
    bool firstp = true;
    bool butt1_ = false;
    bool butt2_ = false;
    long presst = 0;
    long presst2 = 0;
    long odecet = 0;
    long reset = 0;
};
Counter c;
void setup() {
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  for ( int i = 0; i < buttonPinsCount; ++i ) {
    pinMode(buttonPins[i], INPUT);
    buttons[i] = Button(i);
  }
  //Serial.begin(9600);
}
enum states {
  stopped,
  running,
  lapped,
};
unsigned long start = 0;
unsigned long displayed = 0;
states state = stopped;
unsigned long oldmill=0;

void tlacitka(unsigned long mill)
{
 
  unsigned long delta = mill - oldmill;
  oldmill = mill;
  switch (state)
  {
    case (stopped):
      {
        if (buttons[0].is_pressed_())
        {
          state = running;       
        }
        if (buttons[2].is_pressed_())
        {
          start = 0;
        }
        displayed = start;
      }
      break;
    case (running):
      {
        displayed = start;
        start = start + delta;
        if (buttons[0].is_pressed_())
        {
          state = stopped;
        }
        if (buttons[1].is_pressed_())
        {
          state = lapped;
        }
      }
      break;
    case (lapped):
      {
        if (buttons[1].is_pressed_())
        {
          state = running;
        }
        start = start + delta;
      }
      break;
  }
  d.set(displayed);
}

void loop()
{
  unsigned long mil = millis();
  tlacitka(mil);
  
}
