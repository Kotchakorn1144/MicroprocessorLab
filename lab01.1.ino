void setup() {
  // put your setup code here, to run once:
  
  // PORT B(pin 8-11)
  DDRB = 0b00001111;
  // PORT D(pin 4-7)
  DDRD = 0b11110000;
  
}


void loop() {
  // put your main code here, to run repeatedly:
  //start pin4 to 11

  for(int i1=0; i1<4; i1++) {
    PORTD = 0x10 << i1;
    delay(1000);
    PORTD = 0x00;
    delay(1000);
  }

  for(int i2=0; i2<4; i2++) {
    PORTB = 1 << i2;
    delay(1000);
    PORTB = 0x00;
    delay(1000);
  }
}
