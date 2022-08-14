/*
  // ce_pin  (RST):  4
  // sck_pin (CLK):  5
  // io_pin  (DAT):  6
*/

#include <RTClib.h>    // RTClib by NeiroNx from library manager
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>   // LiquidCrystal_PCF8574 by mathertel from library manager

DS1307 rtc;
//DS1302 rtc;

LiquidCrystal_PCF8574 lcd(0x3F);

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();
  delay(100);
  //      สำหรับตั้งเวลาปัจจุบัน
  //    rtc.adjust(DateTime(__DATE__, __TIME__));

  lcd.begin(16, 2);  // initialize the lcd
  //lcd.begin(20, 4);  // initialize the lcd
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  // เรียกเวลาปัจจุบัน
  DateTime now = rtc.now();

  // buffer for DateTime.tostr
  char buf[100];
  strncpy(buf, "hh:mm:ss", 100);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;


    Serial.println(now.format(buf));

    lcd.setBacklight(127);
    lcd.home();
    lcd.clear();
    lcd.print(now.format(buf));
  }
}
