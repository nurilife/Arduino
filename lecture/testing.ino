#include <LiquidCrystal_I2C.h>

// LCD 객체를 생성합니다.
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // LCD를 초기화합니다.
  lcd.init();                // LCD 초기화
  lcd.backlight();           // 백라이트 켜기
}

void loop() {
  // 현재 시간을 구합니다.
  long currentTime = millis() / 1000;

  // LCD에 현재 시간을 표시합니다.
  lcd.setCursor(0, 0);
  lcd.print(currentTime);

  // 1초 동안 대기합니다.
  delay(1000);
}


//--------------------------------------------------------------------------------------------
#include <DHT.h> // DHT11.h 라이브러리를 포함
#define DHTPIN 2 // DHTPIN를 2로 정의
#define DHTTYPE DHT11// DHTTYPE를 DHT22로 정의(DHT11을 사용하는 경우 22대신 11을 입력)

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd (0x27 , 16, 2); // 16x2 LCD객체 생성, 이때 확인한 I2C의 주소값을 입력
DHT dht(DHTPIN, DHTTYPE);
#define trigPin1 8  // 초음파 발신핀 define은 쉽게말하면, 숫자의 이름을 정의해주는것. 
#define echoPin1 9  // 초음파 수신핀
#define bz  6

//변수를 설정합니다. 
long duration1, distance1;


void setup(){
  Serial.begin(9600); // 시리얼 통신을 시작하며,통신속도는 9600
  pinMode(3, OUTPUT); //red
  pinMode(4, OUTPUT); //green
  pinMode(5, OUTPUT); //blue
  pinMode(bz, OUTPUT);
  pinMode(trigPin1,OUTPUT);   // trig를 출력 모드로 설정
  pinMode(echoPin1,INPUT);    // echo를 입력모드로 설정

 lcd .init ();    //I2C LCD 초기화
 lcd .backlight ();  //LCD 백라이트를 켜줍니다.
}
void loop()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1= duration1*0.034/2;
  
  if(distance1 <= 50){
    buzzer();
  }

 
  int h = dht.readHumidity(); // 변수 h를 선언하며 습도 값 대입
  int t = dht.readTemperature(); // 변수 t를 선언하며 온도값 대입
  Serial.println("습도 : " + String(h) + " \t"); // 시리얼 모니터에 출력(이하 생략)
  Serial.println("온도 : " + String(t) + " C");
  lcd .setCursor (0 ,0 );
  lcd .print ("temp=");
  lcd .print (t);
  lcd .setCursor (0 ,1 );
  lcd .print ("humi=");
  lcd .print (h);
  delay(300); // 1초 대기
  lcd.clear();

if(h>=60){
    digitalWrite(3, 1);
    digitalWrite(4, 0);
    digitalWrite(5, 0);
  }else if(h>=50){
    digitalWrite(3, 0);
    digitalWrite(4, 0);
    digitalWrite(5, 1);
  }else{
    digitalWrite(3, 0);
    digitalWrite(4, 1);
    digitalWrite(5, 0);
  }
}

int buzzer(){
   digitalWrite(bz, HIGH);
   delay(80);
   digitalWrite(bz, LOW);
 }
//------------------------------------------------------
#include <Wire.h>                     // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>        // LCD 2004 I2C용 라이브러리
LiquidCrystal_I2C lcd(0x27,16,2);     //  0x3F or 0x27를 선택하여 주세요. 작동이 되지 않는 경우 0x27로 바꾸어주세요. 확인결과 0x3f가 작동하지 않을 수 있습니다.
//고유주소가 LCD마다 다르기 때문입니다.



#define trigPin1 8  // 초음파 발신핀 define은 쉽게말하면, 숫자의 이름을 정의해주는것. 
#define echoPin1 9  // 초음파 수신핀

//변수를 설정합니다. 
long duration1, distance1;


void setup() 
{
  pinMode(trigPin1,OUTPUT);   // trig를 출력 모드로 설정
  pinMode(echoPin1,INPUT);    // echo를 입력모드로 설정

  Serial.begin(9600);        //시리얼 프린트 시작
  lcd.init();                // LCD 초기화
  lcd.backlight();           // 백라이트 켜기

}

void loop() 
{
  //초음파 센서를 한번 초기화 하는 과정입니다. 마치 껏다 켯다를 하면서 거리를 초기화합니다.
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1= duration1*0.034/2;

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Distance Check");
  lcd.setCursor(4,1);
  lcd.print(distance1); lcd.print(" cm");
  delay(800);
  lcd.setCursor(1,3);
  lcd.print("Warning from a crash!");

}
