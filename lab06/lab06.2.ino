#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <ThreeWire.h>  
#include <RtcDS1302.h>
ThreeWire myWire(4,5,6); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void displayDateTime(const RtcDateTime& dt){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(dt.Year(), DEC);
  display.print('/');
  display.print(dt.Month(), DEC); 
  display.print('/'); 
  display.print(dt.Day(), DEC); 
  display.println();
  display.println(); 
  display.print(dt.Hour(), DEC);
  display.print(':'); 
  display.print(dt.Minute(), DEC);
  display.print(':'); 
  display.print(dt.Second(), DEC);
  display.display();
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
  display.clearDisplay(); // clears the screen and buffer
  display.drawPixel(127, 63, WHITE);

  Rtc.Begin();
  RtcDateTime setting_time(2020,2,27,3,06,00);
  Rtc.SetDateTime(setting_time);
  }
  
  void loop() {
    RtcDateTime now = Rtc.GetDateTime();
    displayDateTime(now);
}
