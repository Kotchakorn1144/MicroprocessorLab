int clk_pin = 6; // SHCP
int latch_pin = 4; //STCP
int data_pin = 5; //DS
int ledshow[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

const int buttonPin1 = 8;
const int buttonPin2 = 9;
int buttonState1 = 0;
int buttonState2 = 0;
int num = 0;

void setLed(uint8_t _state)
{
  digitalWrite(latch_pin,LOW);
  for(int i = 0 ; i < 8 ; i++)
  {
    digitalWrite(data_pin,(_state >> (7-i)) & 0x01); 
    digitalWrite(clk_pin,HIGH); 
    digitalWrite(clk_pin,LOW);
  }
  digitalWrite(latch_pin,HIGH); 
}

void setup() 
{
  pinMode(clk_pin,OUTPUT); 
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  Serial.begin(9600);
 } 
void loop() 
{ 
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  if (buttonState1 == LOW) {
    num++;
    delay(100);
    Serial.println("buttomState1");
  }
  if (buttonState2 == LOW) {
    num--;
    delay(100);
  }
  if (num<0){
    num = 9;
  }
  setLed(ledshow[num%10]);
  delay(100);
  
}
