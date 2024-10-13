#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#define DISPLAY_ADDRESS 0x70
Adafruit_AlphaNum4 disp = Adafruit_AlphaNum4();
String text_to_display = " HELLO WORLD ";
int string_pointer = 0;
char display_buffer[4];
long last_display_refresh = 0L;
void setup() {
  disp.begin(DISPLAY_ADDRESS);
  disp.setBrightness(4);
  disp.clear();
  disp.writeDisplay();
}
void loop() {
  long current_millis = millis();
  if (current_millis - last_display_refresh > 300) {
    if (string_pointer >= text_to_display.length())
      string_pointer = 0;
    // Move the existing characters one position to the left
    for (int u = 0; u < 3; u++)
      display_buffer[u] = display_buffer[u + 1];
    // Replace the right-most character with the next
    // character from the text_to_display variable
    display_buffer[3] = text_to_display.charAt(string_pointer++);
    // send the text to the display
    for (int i = 0; i < 4; i++)
      disp.writeDigitAscii(i, display_buffer[i]);
    // display the text
    disp.writeDisplay();
    // update the timing variable
    last_display_refresh = current_millis;
  }
}