/*
  // ce_pin  (RST):  4
  // sck_pin (CLK):  5
  // io_pin  (DAT):  6
*/

#include <RTClib.h>
#include <Wire.h>
DS1307 rtc;
//DS1302 rtc;

// buffer for DateTime.tostr
char buf[20];

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();

  //      สำหรับตั้งเวลาปัจจุบัน
  //    rtc.adjust(DateTime(__DATE__, __TIME__));

}

void loop() {
  DateTime now = rtc.now();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    Serial.println(now.tostr(buf));
  }
}
