// 부저를 이용하여 주어진 주제의 멜로디를 만들어 낸다.[체크]
// 멜로디 출력핀은 D12번으로 한다. 


//온습도센서(DHT11, DHT22)를 이용하여 온습도를 측정할 수 있다. [체크]
//습도 측정값에 따라 주어진 조건값(   이상은 적색,   이상은 청색, 그이하는 녹색) 에 따라(시리얼 모니터 표현(온도: 온도값 C 습도: 습도값 %)[체크]
//LCD 표현(예: 첫번째줄 Temp= 온도값C, 두번째줄 Humi= 습도값%) 및 출력 위치 지정) 삼색LED 색깔로 표현할 수 있다.[체크]
//습도값을 나타내는 삼색LED연결 출력 핀은 적색: D3, 녹색:D4, 청색:D5 로 한다.

#include <DHT.h> // DHT11.h 라이브러리를 포함
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define DHTPIN 2 // DHTPIN를 2로 정의
#define DHTTYPE DHT11 // DHTTYPE를 DHT22로 정의(DHT11을 사용하는 경우 22대신 11을 입력)
#include "pitches.h"
int tonepin = 12;
const int BUTTON = 7;

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

void setup(){
  Serial.begin(9600); // 시리얼 통신을 시작하며,통신속도는 9600
  pinMode(3, OUTPUT); //red
  pinMode(4, OUTPUT); //green
  pinMode(5, OUTPUT); //blue
  pinMode(7, INPUT);
  lcd.init ();    //I2C LCD 초기화
  lcd.backlight ();  //LCD 백라이트를 켜줍니다.
}

void loop(){
  delay(1000); // 1초 대기
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

  if(h>=90){
    melody_play();
    digitalWrite(3, 1);
    digitalWrite(4, 0);
    digitalWrite(5, 0);
  }else if(h>=70){
    digitalWrite(3, 0);
    digitalWrite(4, 0);
    digitalWrite(5, 1);
  }else{
    digitalWrite(3, 0);
    digitalWrite(4, 1);
    digitalWrite(5, 0);
  }
} 

void melody_play(){
  int buttonState = 1;
  for(int i = 0; i<49; i++)
  {
    int Durations = 1000/noteDurations[i];    // 음계의 음길이 계산
    buttonState = digitalRead(BUTTON);
    if(buttonState == LOW) break;
    tone(tonepin, melody[i], Durations);    
    int pauseBetweenNotes = Durations *1.3 ;  //
    delay(pauseBetweenNotes);
    noTone(tonepin);   
  }    
}

//멜로디(음악) + 온습도 LCD 표현 + 스위치 프로그램을 합치고 최종 동작  
//멜로디 동작은 melody_play() 함수로 만들어서 코딩한다.
//습도값이 적색이면 멜로디가 나온다. [ 체크 ]
//스위치는 D7으로풀업 회로를 구성하여 누르면 음악을 멈추고 다시 측정을 시작한다.



