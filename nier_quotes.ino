#include <RGBmatrixPanel.h>

#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

char quotes[] = "      BECOME AS GODS      \
  THIS CANNOT CONTINUE      \
  Everything that lives is designed to end. \
  We are perpetually trapped in a never-ending spiral of life and death. \
  Is this a curse? Or some kind of punishment? \
  I often think about the god who blessed us with this cryptic puzzle, \
  and wonder if we'll ever get the chance to kill him.      \
  You want to **** 2B don't you.      \
  Emotions are prohibited.";

int quotesChars = sizeof(quotes) / sizeof(quotes[0]);

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
const int CHAR_WIDTH = 6;
const int CHARS_PER_LINE = 6;
const int MARQUEE_DELAY = 75; //ms before scrolling a character off screen

void setup() {
  matrix.begin();
  Serial.begin(9600);
  matrix.setTextColor(matrix.Color333(1, 0, 0));
}

void loop() {
  for (int offset = 0; offset < quotesChars; offset++) {
    //constantly change the start of the cursor to be off screen to smoothly scroll the text one LED at a time, instead of a full character
    for (int i = 0; i < CHAR_WIDTH; i++) {
      matrix.setCursor(0 - i, 4);
      //blank the screen 
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      
      //a character will wrap to the next line if the cursor is at 0 and we are trying to display too many characters
      int chars = i < 0 ? CHARS_PER_LINE : CHARS_PER_LINE - 1;
      //print characters individually, using a String seems to have issues
      for (int c = 0; c < chars; c++) {
        matrix.print(quotes[offset + c]);
      }
      delay(MARQUEE_DELAY / CHAR_WIDTH);
    }
  }
}
