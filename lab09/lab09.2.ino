// Timer Interrrupt

#define LED_PIN  9
#define INT_PIN 3

int timer1_counter;
int count;
volatile int timer1_ovf = 62500;

/*
analogWrite() to create the PWM (Changing freq)
PWM will call the Timer module

*/

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(INT_PIN, INPUT);
  
  Serial.begin(9600);
  count = 1;
  
  // Time Interupt
  noInterrupts(); // Disable all interrupt while configuring
  TCCR1A = 0;   // Reset timer
  TCCR1B = 0;   // Reset Timer register
  
  /*
  MCU freq is 16 MHz
  Prescaler CS12 is 256
  
  Timer freq will be 16 MHz/ 256(prescaler) = 62500 Hz.
  TCNT1 (Timer counter register) --> Max value is 65536.
  TCNT1 = 65536 = 62500 Hz
  TNCT1 = 1 = 1.01 Hz
  TCNT1 = 65536/52500 * Interrupt Timer Freq
  */
  
  timer1_counter = 1;   // about 1 sec.
  TCNT1 = timer1_counter; // Timer counter register
  TCCR1B |= (1 << CS12);  // Prescaler
  TIMSK1 |= (1 << TOIE1); // Enable timer overflow interrupt
  
  interrupts();
  
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(count*1000); 
  digitalWrite(LED_PIN, LOW);
  delay(count*1000);
}

ISR (TIMER1_OVF_vect){
  if (count < 3){
    count++;
  }
  else{
    count = 1;
  }
  
  //check
  Serial.println(count);
}
