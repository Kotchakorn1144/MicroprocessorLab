#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

int second = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.print("ready");
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("Start");
  Rtc.Begin();
  RtcDateTime time1(2020,2,20,0,0,0);
  Rtc.SetDateTime(time1);
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  //Serial.println(now.Second());
  if (now.Second()%2 == 0){
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10, LOW);
    second += 2;
    Serial.println(second);
  }

  if ( second == 120){
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
    Serial.println("finish");
  }
}
/* the timed result of both the delay method and using the RTC method is almost the same. 
 * but due to human error result in the time is not excatly the same. 
 * but we can assume that its the same in practical use.
 */
