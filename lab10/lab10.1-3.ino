#define MOTOR_D1_PIN  7
#define MOTOR_D2_PIN  8
#define MOTOR_PWM_PIN 6

int  interruptChannelAPin = 2;
int  interruptChannelBPin = 3;

int encoderDirection;
volatile int encoderCount = 0;

bool previous_read;

void move_forward(int speed){
  digitalWrite(MOTOR_D1_PIN, HIGH);
  digitalWrite(MOTOR_D2_PIN, LOW);
  analogWrite(MOTOR_PWM_PIN, speed);
}
void move_backward(int speed){
  digitalWrite(MOTOR_D2_PIN, HIGH);
  digitalWrite(MOTOR_D1_PIN, LOW);
  analogWrite(MOTOR_PWM_PIN, speed);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(MOTOR_D1_PIN, OUTPUT);
  pinMode(MOTOR_D2_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  
  pinMode(interruptChannelAPin, INPUT_PULLUP);
  pinMode(interruptChannelBPin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(interruptChannelAPin),
                 ChannelA_callback, RISING);
  
  attachInterrupt(digitalPinToInterrupt(interruptChannelBPin),
                 ChannelB_callback, RISING);
  
}

void loop(){
  //move_forward(10);
  move_backward(10);
  Serial.print("Direction:  ");
  Serial.print(encoderDirection); //Fw = 1, Bw = -1
  Serial.print(", Position: ");
  Serial.println(encoderCount);
  delay(100);
}

void ChannelA_callback() {
  bool A = digitalRead(interruptChannelAPin);
  bool B = digitalRead(interruptChannelBPin);
  if ((A==1)&&(B==0)){
    encoderCount++;
    encoderDirection = 1;
  }
}

void ChannelB_callback(){
  bool A = digitalRead(interruptChannelAPin);
  bool B = digitalRead(interruptChannelBPin);
  if ((B==1)&&(A==0)){
    encoderCount--;
    encoderDirection = -1;
  }
}
