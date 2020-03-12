#define led_pin1 10
#define led_pin2 11
float led = 0;
float brightness = 0;
String buff_led;
String buff_bright;
bool state_led = 0; //Go to buff_led
bool state_bright = 0; //Go to buff_bright


void setup() {
  Serial.begin(9600);
}


void loop() {
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    // Choose Buff
    if(inByte == 'L'){
      buff_led = ' ';
      buff_bright = ' ';
      state_led = 1;
      state_bright = 0;
    }
    if(inByte == 'B'){
      state_led = 0;
      state_bright = 1;
    }

    //In buff_led
    if(('0'<= inByte) && (inByte <= '9') && (state_led == 1) && (state_bright == 0)){
      buff_led += inByte;
    }

    //In buff_bright
    if(('0'<= inByte) && (inByte <= '9') && (state_led == 0) && (state_bright == 1)){
      buff_bright += inByte;
    }

    //Set led
    if(inByte == '\n'){
      led = buff_led.toInt();
      brightness = buff_bright.toInt();
      Serial.println(led);
      if (led == 1){
        Serial.println(brightness);
        analogWrite(led_pin1,int(brightness*2.54));
      }
      else if (led == 2){
        Serial.println(brightness);
        analogWrite(led_pin2,int(brightness*2.54));
      }
    }
  }
}
