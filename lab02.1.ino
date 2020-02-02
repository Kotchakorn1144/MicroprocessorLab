int clk_pin = 6; //SHCP
int data_pin = 5; //DS
int latch_pin = 4; //STCP


void brokenmicro(int DATA) {
  digitalWrite(latch_pin, LOW);
  for(int i = 0 ; i < 16 ; i++){
    delay(10);
    // compare byte level
    digitalWrite(data_pin, (DATA >> (15-i)) & 0b0000000000000001);
    digitalWrite(clk_pin,HIGH);
    digitalWrite(clk_pin,LOW);
  }
  digitalWrite(latch_pin,HIGH);
  delay(10);
}


void setup() {
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  
}


void loop() {
  int data = 0b1000000000000000;

  for(int i = 0; i < 15; i++){
    brokenmicro(data>>i);
    delay(100);
  }
}
