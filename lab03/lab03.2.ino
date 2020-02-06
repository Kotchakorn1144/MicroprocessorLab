int clk_pin = 6; // SHCP
int latch_pin = 4; //STCP
int data_pin = 5; //DS
int ledshow[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int a =0;

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
   if (Serial.available() > 0) 
   {
    char byt = Serial.read();
     a = byt-'0';
     setLed(ledshow[a]);
   }   
}
