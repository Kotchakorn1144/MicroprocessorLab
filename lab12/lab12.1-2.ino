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
void setSpeed(int speed){
  if (speed > 0){
    // Motor Forward
    if (speed > 100) {
      speed = 100;
    }
    move_forward(speed);
  }
  else if (speed < 0){
    speed = speed * (-1);
    if (speed > 100){
      speed = 100;
    }
    move_backward(speed);
  }
  else{
    move_forward(1);
  }
}

void Timer1_initailize (int period) {
  // initialize timer1
  noInterrupts(); // disable all interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1 = 0;  // initialize counter value to 0
  // 0 --> 65535
  // OCR1A = 16000000.0 / (256.0 * 1000.0) -1
  OCR1A = (16000000.0 / (256.0 * 1000.0) * period -1);
  // Turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  interrupts(); // enable all interrupts
}

void setup() {
  Serial.begin(9600);
  
  pinMode(MOTOR_D1_PIN, OUTPUT);
  pinMode(MOTOR_D2_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(A0, INPUT);
  
  pinMode(interruptChannelAPin, INPUT_PULLUP);
  pinMode(interruptChannelBPin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(interruptChannelAPin),
                 ChannelA_callback, RISING);
  
  attachInterrupt(digitalPinToInterrupt(interruptChannelBPin),
                 ChannelB_callback, RISING);
  Timer1_initailize(300);
}

int setpoint = 0;
int fb_speed = 0;
int errori = 0;
float kp = 0.3;
float ki = 0.1;

void loop(){
  int error = setpoint - fb_speed;
  int pid = kp * (float)(error) + ki * (float)(errori);
  errori += error;
  setSpeed(pid);  // pid = -255 --> 255
  
  Serial.print(setpoint);
  Serial.print(",");
  Serial.println(fb_speed);
  delay(200);
  //Serial.println(encoderCount);
    
  if(Serial.available()){
    String inString = Serial.readString();
    setpoint = inString.toInt();
    Serial.println(setpoint);
  }
}

void ChannelA_callback() {
  bool A = digitalRead(interruptChannelAPin);
  bool B = digitalRead(interruptChannelBPin);
  if ((A==1)&&(B==0)){
    // encoderDirection = 1
    encoderCount++;
  }
}

void ChannelB_callback(){
  bool A = digitalRead(interruptChannelAPin);
  bool B = digitalRead(interruptChannelBPin);
  if ((B==1)&&(A==0)){
    //encoderDirection = -1
    encoderCount--;
  }
}

/*  Ever 100 ms
  Reset the position encoderCount = 0
    Motor slow: encoderCount in 100ms is 200 pulse
    Motor fast: encoderCount in 100ms is 400 pulse
*/

ISR (TIMER1_COMPA_vect){
  fb_speed = encoderCount;
  encoderCount = 0;
}
