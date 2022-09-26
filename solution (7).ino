#include "funshield.h"
#include "input.h"
#include <cstring>
// map of letter glyphs
constexpr byte LETTER_GLYPH[] {
  0b10001000,   // A
  0b10000011,   // b
  0b11000110,   // C
  0b10100001,   // d
  0b10000110,   // E
  0b10001110,   // F
  0b10000010,   // G
  0b10001001,   // H
  0b11111001,   // I
  0b11100001,   // J
  0b10000101,   // K
  0b11000111,   // L
  0b11001000,   // M
  0b10101011,   // n
  0b10100011,   // o
  0b10001100,   // P
  0b10011000,   // q
  0b10101111,   // r
  0b10010010,   // S
  0b10000111,   // t
  0b11000001,   // U
  0b11100011,   // v
  0b10000001,   // W
  0b10110110,   // ksi
  0b10010001,   // Y
  0b10100100,   // Z
};
constexpr byte EMPTY_GLYPH = 0b11111111;
constexpr int positionsCount = 4;
constexpr unsigned int scrollingInterval = 300;

/**
   Show chararcter on given position. If character is not letter, empty glyph is displayed instead.
   @param ch character to be displayed
   @param pos position (0 = leftmost)
*/
void displayChar(char ch, byte pos)
{
  byte glyph = EMPTY_GLYPH;
  if (isAlpha(ch)) {
    glyph = LETTER_GLYPH[ ch - (isUpperCase(ch) ? 'A' : 'a') ];
  }
  else if (isDigit(ch))
  {

    int a = ch - '0';
    glyph = digits[a];
  }
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, MSBFIRST, glyph);
  shiftOut(data_pin, clock_pin, MSBFIRST, digit_muxpos[pos]);
  digitalWrite(latch_pin, HIGH);
}

SerialInputHandler input;

void setup() {
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  //Serial.begin(9600);
  input.initialize();
}/*
  void ukol1(char a)
  {
  displayChar(a, digit_muxpos[1]);
  }
  int i = 0;
  void ukol2(String textik)
  {
  char pole[sizeof(textik)];
  int velikost = sizeof(textik);
  Serial.println(velikost);
  textik.toCharArray(pole, sizeof(textik));
  displayChar(pole[i], digit_muxpos[i]);
  i++;
  i = i % 4;

  }*/

size_t getStringSize( const char *str) {
  size_t i = 0;
  while ( str[i]) ++i;
  return i;
}

class Timer {
    unsigned long lTime = 0;
    unsigned long t;
  public:
    Timer(unsigned long t)
    {
      this->t = t;
    }

    boolean run() {
      unsigned long c = millis();
      if (lTime + t <= c) {
        lTime = c;
        return true;
      }
      return false;
    }
};

Timer timer1(300);
Timer timer2(1);

int d_index = 0;
int pos = 4;
const int display_size = 4;
int textIndex = 0;
void zobrazovani(char *text)
{
  if (!timer2.run()) return;
  int lentgh = getStringSize(text);
  if (!(d_index < display_size)) {
    d_index = 0;
    textIndex = 0;
    if (pos < 0) textIndex = -pos;
  }
  if (d_index >= pos && textIndex < lentgh) {
    displayChar(text[textIndex++], d_index);
  }
  else {
    displayChar("", d_index);
  }
  d_index++;
  if (timer1.run()) {

    pos--;
    if (pos < -lentgh) pos = display_size;
  }
  if (!timer2.run()) return;
}/*
  void ukol3(const char* text)
  {
  zobrazovani(text);
  }*/
char oldmsg[256] = "";
void ukol4()
{
  const char* msg = input.getMessage();
  if (strcmp(msg, oldmsg) != 0 && pos == display_size)
  {
    strcpy(oldmsg, msg);
  }
  zobrazovani(oldmsg);

}
void loop() {
  input.updateInLoop();
  //ukol1('w');
  //ukol2("gm");

  //ukol3("hello world");
  ukol4();
}
