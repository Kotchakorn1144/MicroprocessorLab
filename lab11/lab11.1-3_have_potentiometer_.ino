#include <SPI.h>
// 7 segment
#define DATA_PIN  11
#define CLOCK_PIN 13
#define SS_PIN_1  10
#define SS_PIN_2  9
// LED
#define LED_PIN 4
// Motor
#define MOTOR_D1_PIN  7
#define MOTOR_D2_PIN  8
#define MOTOR_PWM_PIN 6

// Counter
int  interruptChannelAPin = 2;
int  interruptChannelBPin = 3;
bool previous_read;
int encoderDirection;
volatile int encoderCount = 0;

// Potentiometer
#define POTENTIOMETER 5
int potMin = 0;
int potMax = 1032;
int actMax = 255;
int actMin = -255;//positions of actuator

int map7seg[10] = {
  0x3f, //0
  0x06, //1
  0x5b, //2
  0x4f, //3
  0x66, //4
  0x6d, //5
  0x7d, //6
  0x07, //7
  0x7f, //8
  0x6f //9
};

// Function for 7 segment
void spi_write_1 (unsigned char cData) {
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_1, HIGH);
  digitalWrite (SS_PIN_1, LOW);
}
void spi_write_2 (unsigned char cData) {
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_2, HIGH);
  digitalWrite (SS_PIN_2, LOW);
}
void show(int num){
  if(num > 0){
    digitalWrite(LED_PIN, LOW);
  }
  else if(num < 0){
    num = num*(-1);
    digitalWrite(LED_PIN, HIGH);
  }
  spi_write_1(map7seg[num/1000]);
  spi_write_2(map7seg[((num/100))%10]);
}

// Function for motor
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
void setSpeed(int speed){
  if (speed > 0){
    // Motor Forward
    if (speed > 255) {
      speed = 255;
    }
    move_forward(speed);
  }
  else if (speed < 0){
    speed = speed * (-1);
    if (speed > 255){
      speed = 255;
    }
    move_backward(speed);
  }
  else{
    move_forward(1);
  }
}

int getSetpoint()
{
    int rawdestination = analogRead(POTENTIOMETER);
  //read the potentiometer to get the destination
    int destination = map(rawdestination, potMin,potMax,actMin,actMax);//convert the potentiometer feedback to match the actuator
    return(destination);
}//end getDestination
void setup() {
  Serial.begin(9600);
  // 7 segment
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  //LED
  pinMode(LED_PIN, OUTPUT);
  // Motor
  pinMode(MOTOR_D1_PIN, OUTPUT);
  pinMode(MOTOR_D2_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  // Potentiometer
  pinMode(POTENTIOMETER, INPUT);
  
  // Interrupt
  pinMode(interruptChannelAPin, INPUT_PULLUP);
  pinMode(interruptChannelBPin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(interruptChannelAPin),
                 ChannelA_callback, RISING);
  
  attachInterrupt(digitalPinToInterrupt(interruptChannelBPin),
                 ChannelB_callback, RISING);
  
}

void loop(){
  // Track
  //int sensor_value = analogRead(POTENTIOMETER);
  //int setpoint = analogRead(POTENTIOMETER);
  int setpoint = getSetpoint();
  int error = setpoint - encoderCount;
  int p = 1.0*(float)(error);
  
  // Show
  setSpeed(p);
  show(encoderCount);
  delay(10);

  // print  
  Serial.print(setpoint);
  Serial.print(",");
  Serial.println(encoderCount);
  delay(10);
  
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
