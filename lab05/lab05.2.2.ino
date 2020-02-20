int second = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.println("ready");
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("Start");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  second += 2;
  Serial.println(second);
  if(second == 10){
    Serial.println("Finish");
  }

}

/* the timed result of both the delay method and using the RTC method is almost the same. 
 * but due to human error result in the time is not excatly the same. 
 * but we can assume that its the same in practical use.
 */
