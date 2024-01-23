// A_OLED
// File for seting up OLED and storing OLED specific functions and variabels

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void oledSetup() {
  Wire.begin();
  Wire.beginTransmission(60);
  byte error = Wire.endTransmission();

  if (error != 0) {                                             // If there is an error
    Serial.println("ERROR: OLED was not detected by Arduino."); // Send message to Serial
    return;                                                     // Exit OLED Setup function
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    return;
  }

  // Clear the buffer
  display.clearDisplay();
}

// Draw Functions
void drawMenu(int val) {                                    // Draws the menu corresponding to the current state
  display.clearDisplay();                                   // Clears the display buffer
  display.drawBitmap(0, 0, bmp_menuArray[val], 128, 64, 1); // Adds the corresponding menu BMP to the buffer
  display.display();                                        // Pushes buffer to screen and draws everything
}

void drawManual() { // Draws the menu for the manual mode
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.print("Manual");
  display.display();
}

void drawSense() {  // Draws the menu for the sensor mode
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.print("Sense");
  display.display();
}

void drawDelayed(int val) { // Draws the menu for the delayed mode
  display.clearDisplay();
  display.drawBitmap(0, 0, bmp_verticalarrows, 128, 64, 1);
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.print(val);
  display.print(" ms");
  display.display();
}
