#include <LiquidCrystal_I2C.h>
#include <Wire.h>
const int WINCOUNT=30;
const uint8_t BLANK=0;
const uint8_t BLOCK=1;
const uint8_t PLAYER=2;

LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t blk[][2]={
0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 1,0, 1,0, 1,0,
0,0, 0,0, 0,0, 0,1, 0,1, 0,1, 0,1, 0,0, 0,0, 1,0, 1,0, 0,0, 0,0, 0,0, 0,1,
0,1, 0,0, 0,0, 0,0, 0,0, 1,0, 1,0, 1,0, 1,0, 1,0, 1,0,};
byte blank[]={B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000,};
byte block[]={B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111,};
byte player[]={B01100, B01100, B01000, B01111, B01000, B01100, B01010, B01001,};

void initGame();
void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, toLeft, FALLING); // D2 
  attachInterrupt(1, toRight, FALLING); // D3
  lcd.init();
  lcd.createChar(BLANK, blank);
  lcd.createChar(BLOCK, block);
  lcd.createChar(PLAYER, player);
  lcd.backlight();
}

int count = 0; 
int position = 0; 
bool hit=false;
bool gamestart=true;
void loop(){
  if(gamestart){
    for (int i = 0; i < 10; i++){
      lcd.setCursor(i, 0);
      lcd.write(blk[count+i][0]);
      lcd.setCursor(i, 1);
      lcd.write(blk[count+i][1]);
      if(i==3)
      hit=blk[count+i][position]; 
    }
    lcd.setCursor(10, 0);
    lcd.print("score");
    lcd.setCursor(10, 1);
    lcd.print(count);
    if(hit){
      lcd.clear();
      gamestart=false;
    }
    lcd.setCursor(3, position);
    lcd.write(PLAYER);
    count++;
    if(count==WINCOUNT){
      lcd.clear();
      gamestart=false;
    }
  }else{
    lcd.setCursor(0, 0);
    lcd.print("Game Over");
    lcd.setCursor(0, 1);
    if(count==WINCOUNT){ 
      lcd.print("You Win!");
    }else{
      lcd.print("You Lose!");
    }
  }
Serial.println(count);
delay(1000);
}
void toLeft(){
  position = 0;
  if(gamestart==false){
    gamestart=true;
    count=0;
  }
}
void toRight(){
  position = 1;
  if(gamestart==false)
  {
    gamestart=true;
    count=0;
  }
}
 
