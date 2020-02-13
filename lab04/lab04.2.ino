#include<SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
#define BUTTON_UP A0
#define BUTTON_DOWN A1
#define BUTTON_CD A2
#define PIEZO_PIN 3

int a;

int ledshow[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void spi_write_1(unsigned char cData){
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST, cData);
  digitalWrite(SS_PIN_1,HIGH);
  digitalWrite(SS_PIN_1,LOW);

}
void spi_write_2(unsigned char cData){
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST, cData);
  digitalWrite(SS_PIN_2,HIGH);
  digitalWrite(SS_PIN_2,LOW);
}
void show_num(int x)
{
  spi_write_1(ledshow[x/10]);
  spi_write_2(ledshow[x%10]);
}
void setup()
{
  Serial.begin(9600);
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_CD, INPUT_PULLUP);
  
  show_num(0);
}

void loop()
{   
  if(digitalRead(BUTTON_UP)==0){
    delay(100);
    a++;
    Serial.println(a);
  }
  else if(digitalRead(BUTTON_DOWN)==0){
    delay(100);
    a--;
    Serial.println(a);
  }
  else if(digitalRead(BUTTON_CD) ==0){
    for(;a>0;a--){
      show_num(a);
      delay(1000);
      tone(PIEZO_PIN, 5000, 50);
    }
     tone(PIEZO_PIN, 1000, 2000);
  }
    show_num(a);
}
