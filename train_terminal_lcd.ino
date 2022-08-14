/*
  // ce_pin  (RST):  4
  // sck_pin (CLK):  5
  // io_pin  (DAT):  6
*/

// กำหนดขาเซนเซอร์
#define sensor1 8
#define sensor2 9
#define sensor3 10
#define sensor4 11

#include <RTClib.h>    // RTClib by NeiroNx from library manager
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>   // LiquidCrystal_PCF8574 by mathertel from library manager

DS1307 rtc;
//DS1302 rtc;

LiquidCrystal_PCF8574 lcd(0x3F);

uint16_t timeleft[5] = {5, 10, 15, 20, 30}; // time to destination in minute from sensor 1 2 3 4 และ ขณะตรวจจับอะไรไม่ได้
bool state[4];
bool start = 0;
DateTime trainA_lasttime;

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();
  delay(100);
  //      สำหรับตั้งเวลาปัจจุบัน
  //    rtc.adjust(DateTime(__DATE__, __TIME__));

  pinMode(13, OUTPUT);  digitalWrite(13, HIGH);

  lcd.begin(16, 2);  // initialize the lcd
  //lcd.begin(20, 4);  // initialize the lcd
  lcd.noBlink();
  lcd.noCursor();


  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);


}

void loop() {
  // เรียกเวลาปัจจุบัน
  DateTime now = rtc.now();

  // buffer for DateTime.tostr
  char buf[50];
  strncpy(buf, "hh:mm:ss", 50);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;


    Serial.println(now.format(buf));

  }

  //Serial.println(digitalRead(sensor1));
  if (digitalRead(sensor1)) {                     // เซนเซอร์1ตรวจจับได้
    state[0] = true;
  } else if (!digitalRead(sensor1) && state[0]) { // จับขอบขาลงเซนเซอร์
    state[0] = false;
    DateTime future(now + (timeleft[0] * 60));
    LCDdisplay(String(timeleft[0]), future.format(buf));
  } else if (digitalRead(sensor2)) {              // เซนเซอร์2ตรวจจับได้
    state[1] = true;
  } else if (!digitalRead(sensor2) && state[1]) { // จับขอบขาลงเซนเซอร์
    state[1] = false;
    DateTime future(now + (timeleft[1] * 60));
    LCDdisplay(String(timeleft[1]), future.format(buf));
  } else if (digitalRead(sensor3)) {              // เซนเซอร์3ตรวจจับได้
    state[2] = true;
  } else if (!digitalRead(sensor3) && state[2]) { // จับขอบขาลงเซนเซอร์
    state[2] = false;
    DateTime future(now + (timeleft[2] * 60));
    LCDdisplay(String(timeleft[2]), future.format(buf));
  } else if (digitalRead(sensor4)) {              // เซนเซอร์4ตรวจจับได้
    state[3] = true;
  } else if (!digitalRead(sensor4) && state[3]) { // จับขอบขาลงเซนเซอร์
    state[3] = false;
    DateTime future(now + (timeleft[3] * 60));
    LCDdisplay(String(timeleft[3]), future.format(buf));
  }

  if (!start) { // แสดงค่าครังแรก
    start = 1;
    DateTime starttime(now + (timeleft[4] * 60));
    //    Serial.println("start time : " + String(starttime.format(buf)));
    LCDdisplay(String(timeleft[4]), String(starttime.format(buf)));
  }
}

void LCDdisplay(String est, String time) {
  uint8_t column[3] = {0, 4, 11};   // กำหนดขนาดตารางแต่ละ column
  Serial.println("start time : " + time);

  lcd.setBacklight(127);
  lcd.home();
  lcd.clear();

  lcd.setCursor(column[0], 0); lcd.print("No.");
  lcd.setCursor(column[1], 0); lcd.print("Est.");
  lcd.setCursor(column[2], 0); lcd.print("Time");

  lcd.setCursor(column[0], 1); lcd.print("A");
  lcd.setCursor(column[1], 1); lcd.print(">" + est + "min");
  lcd.setCursor(column[2], 1); lcd.print(time);

}
