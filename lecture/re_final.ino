#include <LiquidCrystal_I2C.h>
#include <DHT.h> // DHT11.h 라이브러리를 포함
#define DHTPIN 2 // DHTPIN를 2로 정의
#define DHTTYPE DHT11 // DHTTYPE를 DHT22로 정의(DHT11을 사용하는 경우 22대신 11을 입력)
#include "pitches.h"

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd (0x27 , 16, 2); // 16x2 LCD객체 생성, 이때 확인한 I2C의 주소값을 입력

int melody[] = {
NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,
NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,
NOTE_C5,NOTE_C5,NOTE_C5,

NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_G5,
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_G5,

NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_G5,
NOTE_C6,NOTE_G5,NOTE_C6,NOTE_G5,
NOTE_E5,NOTE_D5,NOTE_C5
};

int noteDurations[]={
4,8,8,4,4,
4,8,8,4,4,
8,8,4,8,8,4,
4,4,2,
4,4,4,4,
4,4,2,
4,4,4,4,
4,4,2,
4,4,4,4,
8,8,8,8,2,
4,4,4,4,
4,4,2
};

const int tonepin = 12;
const int BUTTON = 7;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  lcd.init ();    //I2C LCD 초기화
  lcd.backlight ();  //LCD 백라이트를 켜줍니다.
}

void loop() {

  int h = dht.readHumidity(); // 변수 h를 선언하며 습도 값 대입
  int t = dht.readTemperature(); // 변수 t를 선언하며 온도값 대입
  Serial.println("습도 : " + String(h) + " %" + "\t"); // 시리얼 모니터에 출력(이하 생략)
  Serial.println("온도 : " + String(t) + "'C");
  lcd.clear();
  lcd .setCursor (0 ,0 );
  lcd .print ("temp=");
  lcd .print (t);
  lcd .print ("'C");
  lcd .setCursor (0 ,1 );
  lcd .print ("humi=");
  lcd .print (h);
  lcd .print ("%");

  if (h <= 90) {
    // 스위치가 눌리면 노래를 중단
    noTone(tonepin);
    delay(300); // 중단 후 잠시 기다림
  } else {
    // 스위치가 눌리지 않은 경우 노래를 재생
    for (int i = 0; i < 49; i++) {
      int Durations = 1000 / noteDurations[i];
      //buttonState = digitalRead(BUTTON);
     int h = dht.readHumidity(); 
      
      if (h <= 90) {
        // 스위치가 눌리면 노래를 중단하고 loop에서 빠져나감
        noTone(tonepin);
        delay(1000);
        break;
      }

      tone(tonepin, melody[i], Durations);
      int pauseBetweenNotes = Durations * 1.3;
      delay(pauseBetweenNotes); 
      noTone(tonepin);
    }
  }
}
