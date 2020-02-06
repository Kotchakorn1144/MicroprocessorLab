const int buttonPin1 = A0; // the number of the pushbutton pin
const int buttonPin2 = A1; // the number of the pushbutton pin
int buttonState1 = 0; // variable for reading the pushbutton status
int buttonState2 = 0; // variable for reading the pushbutton status
int i = 0;


void setup() {
  // put your setup code here, to run once:

  // PORT B(pin 8-11)
  DDRB = 0b00001111;
  // PORT D(pin 4-7)
  DDRD = 0b11110000;
}


void loop() {
  // put your main code here, to run repeatedly:

  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  //start pin4 to 11

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == LOW) {
    i++;
    delay(1000);
    if ((i%8) < 4){
      PORTD = 0x10 << (i%4);
      delay(2000);
      PORTD = 0x00;
      }
    else if (4 <= (i%8)){
      PORTB = 1 << (i%4);
      delay(2000);
      PORTB = 0x00;
    }
    
  }
  
  if (buttonState2 == LOW) {
    i--;
    delay(1000);
    if ((i%8) < 4){
      PORTD = 0x10 << (i%4);
      delay(2000);
      PORTD = 0x00;
      }
    else if (4 <= (i%8)){
      PORTB = 1 << (i%4);
      delay(2000);
      PORTB = 0x00;
    }
  }
}
