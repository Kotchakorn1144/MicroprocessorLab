#include <SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
int i = 0;
int charmap[10] = {
  0x3f, //0b00111111
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

int timer1_counter;
volatile int timer1_ovf = 62500;

void spi_write_1 (unsigned char cData) {
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_1, HIGH);
  digitalWrite (SS_PIN_1, LOW);
}

void setup()
{
  Serial.begin(9600);
  // 7 segment
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  
  // Time Interupt
  noInterrupts();  // Disable all interrupt while configuring
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
  
  timer1_counter = 1;
  TCNT1 = timer1_counter; // Timer counter register
  TCCR1B |= (1 << CS12);  // Prescaler
  TIMSK1 |= (1 << TOIE1); // Enable timer overflow interrupt
  
  interrupts();
}

void loop(){
  spi_write_1(charmap[(i/2+1)%10]);
  delay(500);
}

ISR (TIMER1_OVF_vect){
  //spi_write_1(charmap[i%10]);
  i++;
  //Serial.println(i);
}
