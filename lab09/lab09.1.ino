#define LED_PIN  9
#define INT_PIN 3

int count;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN),
                  ISR_Callback, RISING);
  Serial.begin(9600);
  count = 1;
  Serial.println(count);
  
  // RISING   : 0v to 5v
  // FALLING  : 5v to 0v
  // CHANGE   : 0v to 5v or 5v to 0v
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(count*1000); 
  digitalWrite(LED_PIN, LOW);
  delay(count*1000); 
}

void ISR_Callback() {
  if (count < 3){
    count++;
  }
  else{
    count = 1;
  }
  //check
  Serial.println(count);

}
