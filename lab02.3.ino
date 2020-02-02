const int buttonPin1 = 8; // the number of the pushbutton pin
const int buttonPin2 = 9; // the number of the pushbutton pin
int buttonState1 = 0; // variable for reading pushbutton status
int buttonState2 = 0; // variable for reading pushbutton status
int num = 0;

const byte analog_pin = A2; // the number of variable resistance pin 
byte key; 
int val = 0;

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
  val = analogRead(analog_pin);
  
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  int data = 0b1000000000000000;

  brokenmicro(data>>(num%16));
  if (buttonState1 == LOW) {
    num++;
    delay(val);
  }
  if (buttonState2 == LOW) {
    num--;
    delay(val);
    }
}
