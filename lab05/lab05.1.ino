#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  Serial.println(now.Second());
  if (now.Second()%2 == 0){
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10, LOW); 
  }
}
