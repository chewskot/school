#include "funshield.h"
constexpr int buttonPins[] { button1_pin, button2_pin, button3_pin };
constexpr int buttonPinsCount = sizeof(buttonPins) / sizeof(buttonPins[0]);
constexpr int activationDelay = 1000; // how long before button starts to perform periodic updates [ms]
constexpr int periodicDelay = 300; // delay between consecutive periodic updates [ms]
constexpr int radCount = sizeof(digit_muxpos) / sizeof(digit_muxpos[0]);
int rad_cisel(int rad, int rady);

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
    Button() { }
    Button(int button) : number_(button), status_(false) { }
};
Button buttons[buttonPinsCount];
int counter;
int rad;
void setup() {
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  for ( int i = 0; i < buttonPinsCount; ++i ) {
    pinMode(buttonPins[i], INPUT);
    buttons[i] = Button(i);
  }
  //Serial.begin(9600);
  counter = 0;
  rad = 0;
}
//casovac pro 3.3
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
//binary s rozsvicenim
//vypis
void write_glyph(int cislo, int pozice)
{
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, MSBFIRST, cislo);
  shiftOut(data_pin, clock_pin, MSBFIRST, pozice);
  digitalWrite(latch_pin, HIGH);
}
/*
void bin()
{
  if (counter > 9 )
  {
    counter = 0;
  }
  else if (counter < 0)
  {
    counter = 9;
  }
  write_glyph(digits[counter], digit_muxpos[0]); 
}
*/
// pro ulohu 4.4

int write_digit(int rad)
{
  
  int cislo = 1;
  for(int i = 0; i< rad; i++)
  {
    cislo *= 10;
  }
  write_glyph(digits[(counter / cislo) % 10],digit_muxpos[3-rad]);
  return cislo;
}
void bin2(int rad)
{
  int omezeni = 10000;
  if (counter > 9999)
  {
    counter = counter % omezeni;
  }
  else if (counter < 0)
  {
    counter = omezeni + counter;
  } 
  write_digit(rad);
}
//4.1
/*
  void glyphs(byte glyph, int pos)
  {
  write_glyph(glyph,digit_muxpos[3-pos]);
  }
  //4.2
  void cislice(int cislo,int pozice)
  {
  write_glyph(digits[cislo],digit_muxpos[3-pozice]);
  }
  //4.3
  void pocitadlo()
  {
   if(buttons[0].is_pressed_())
    {
        counter++;
    }
    else if(buttons[1].is_pressed_())
    {
        counter--;
    }
    else if(buttons[2].is_pressed_())
    {
        counter=0;
    }
  bin();
  }
*/
//4.4
void pocitac()
{
  
  if (buttons[0].is_pressed_())
  {
    counter += write_digit(rad);
  }
  else if (buttons[1].is_pressed_())
  {
    counter -= write_digit(rad);
  }
  else if (buttons[2].is_pressed_())
  {
    rad++;
    if (rad >= 4)
    {
      rad = rad % 4;
    }
  }
  bin2(rad);
}
void loop()
{
  //glyphs(0xf9,2);
  //cislice(2,2);
  //pocitadlo();
  pocitac();
}
