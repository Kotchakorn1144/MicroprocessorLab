#include <Adafruit_SSD1306.h>
#include <splash.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <SPI.h> 
#include <Wire.h> 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins) 
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin) 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() 
{ 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c 
  display.clearDisplay(); // clears the screen and buffer
  display.drawPixel(127, 63, WHITE);
  display.drawLine(0, 63, 127, 21, WHITE); 
  display.drawCircle(110, 50, 12, WHITE); 
  display.fillCircle(45, 50, 8, WHITE); 
  display.drawTriangle(70, 60, 90, 60, 80, 46, WHITE); 
  display.setTextSize(1); 
  display.setTextColor(WHITE); 
  display.setCursor(10,0); 
  display.println("Welcome");
  display.setTextSize(2);
  display.println("KRAI 2nd"); 
  display.setTextColor(BLACK, WHITE); 
  display.setTextSize(1); 
  display.println("www.krai.io"); 
  display.setTextColor(WHITE, BLACK);
  display.display();
  pinMode(A0,INPUT);
  Serial.begin(9600);
  
}
void loop()
{
  int VR = analogRead(A0);
  String VRSGU = String(VR);
  Serial.println(VR);
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(2);
  display.setCursor(10,0); 
  String KJ = Serial.readString();
  display.print(KJ);
  display.display();
  delay(500);
  
  
}




  
