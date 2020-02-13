#include <SPI.h>
#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
int ledshow[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void spi_write_1 (unsigned char cData){
  shiftOut(DATA_PIN,CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_1,HIGH);
  digitalWrite (SS_PIN_1,LOW);
}
void spi_write_2 (unsigned char cData){
  shiftOut(DATA_PIN,CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_2,HIGH);
  digitalWrite (SS_PIN_2,LOW);
}
void show_num(int x)
{
  spi_write_1(ledshow[x/10]);
  spi_write_2(ledshow[x%10]);
}

void setup(){
  pinMode(SS_PIN_1,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}
void loop(){
    int a;
  for(a=0;a<100;a++){
    show_num(a);
  delay(500);
  }
}
