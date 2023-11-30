//동시에 여러가지 일을 할 때 처리를 빨리해 줄 수 있는 방법 연구
#define LED_ 13
#define SW_R  7
#define SW_B  8
void setup(){
  Serial.begin(9600);
  pinMode(LED_, OUTPUT);
  pinMode(SW_R, INPUT);
  pinMode(SW_B, INPUT);
}

void loop(){
  digitalWrite(LED_, HIGH);
  delay(1000);
  digitalWrite(LED_, LOW);
  delay(1000);
       

  if(digitalRead(SW_R)==0){
    Serial.println("e");
  }
}
//문제 해결 한번만 누르는데로 순식간에 여러번 인식 ---------------------------------
//프로그램 절차적으로 진행하다가 10ms마다 aa로 가서 확인 기존에 센서를 1초마다 한번 확인--------------------------------
//깜박이는 것을 메인 센서 감지를 서브로 둠 --------------------

#include <MsTimer2.h>
#define LED_ 13
#define SW_R  7
#define SW_B  8

void setup(){
  Serial.begin(9600);
  pinMode(LED_, OUTPUT);
  pinMode(SW_R, INPUT);
  pinMode(SW_B, INPUT);

  MsTimer2::set(10,aa);
  MsTimer2::start();
}
void loop(){
  digitalWrite(LED_, HIGH);
  delay(1000);
  digitalWrite(LED_, LOW);
  delay(1000);   
}
void aa(){
  if(digitalRead(SW_R) ==0 )
  Serial.println("e");
  }
//센서 감지를 메인으로  깜박이는 것을 서브로 둠 -----------------------------------------------------------
//만약 delay(200); 추가로 한번에 여러개 대신 한번에 한번만 나오게 수정 --------------------
#include <MsTimer2.h>
#define LED_ 13
#define SW_R  7
#define SW_B  8

boolean b1 = true;

void setup(){
  Serial.begin(9600);
  pinMode(LED_, OUTPUT);
  pinMode(SW_R, INPUT);
  pinMode(SW_B, INPUT);

  MsTimer2::set(1000,aa);
  MsTimer2::start();
}
void loop(){
  if(digitalRead(SW_R)==0){
    Serial.println("e");
    delay(200);
  }
}
void aa(){
  digitalWrite(LED_, b1);
  b1=!b1;
}

외부 인터럽트(타이머 인터럽트 보다 우선 순위 있음)-------------------------------------------------------
#include <MsTimer2.h>
#define LED_ 13
#define SW_R  7
#define SW_B  8

boolean b1 = true;

void setup(){
  Serial.begin(9600);
  pinMode(LED_, OUTPUT);
  pinMode(SW_R, INPUT);
  pinMode(SW_B, INPUT);

  attachInterrupt(1, bb, FALLING);  //RISING, LOW, CHANGE

  MsTimer2::set(1000,aa);
  MsTimer2::start();
}
void loop(){
  if(digitalRead(SW_R)==0){
    Serial.println("e");
    delay(200);
  }
}
void aa(){
  digitalWrite(LED_, b1);
  b1=!b1;
}
void bb(){
  Serial.println("bb");
}
  



