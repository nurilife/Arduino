#include <LedControl.h>
LedControl dot = LedControl(12, 11, 10, 1);  // (DIN, CLK, LOAD, 모듈 개수)
byte injego[3][8] = {
    {0b00000000, 0b00110010, 0b01001010, 0b01001010, 0b00110010, 0b00000000, 0b01000000, 0b01111110},
    {0b00000000, 0b01110101, 0b00100101, 0b00101101, 0b01010101, 0b01010101, 0b01010101, 0b00000000},
    {0b00000000, 0b01111110, 0b00000010, 0b00000010, 0b00010010, 0b00010100, 0b01111110, 0b00000000}
};
void setup() {
    dot.shutdown(0, false);    // 표시 활성화
    dot.setIntensity(0, 8);    // 밝기 설정 (0-15)
    dot.clearDisplay(0);       // 표시 초기화
}
void loop() {
    for (int i = 0; i <3; i++) {
        for (int j = 0; j <8; j++) {
          dot.setRow(0, j, injego[i][j]);
        }
     delay(500);
    }
}




#include <LedControl.h>
LedControl dot =LedControl(12,11,10,1)
void shift_mat(byte* mat1, byte* mat2, String sft_direction, intn_shift, LedControl dot);
byte mat1[8]={0x00, 0x6c, 0x52, 0x52, 0x4c, 0x40, 0x5e, 0x00}; //인
byte mat1[8]={0x40, 0x22, 0x1e, 0x22, 0x48, 0x3e, 0x00, 0x7e}; //인

void setup() 
{
  for(int i = 0; i<2; i++){
  dot.shutdown(i, false);                    // 절전모드로 (첫번째 모듈, 절전모드를 하지 않는다) 설정 
  dot.setIntensity(i, 7);                       // 밝기를 조절 (첫번째 모듈, 1~15까지 원하는 밝기) 설정
  dot.clearDisplay(i); 
  }                         // LED를 초기화 설정 (첫번째 모듈)
}
void loop() 
{
  for (j = 0; j<16; j++){
    shift_mat(mat1, mat2, "left", 1, dot);           // setRow는 x축 LED를 한번에 제어하며,
    delay (100);                                         // 0.5초의 딜레이
  }
}

void shift_mat(byte* mat1, byte* mat2, String sft_direction, intn_shift, LedControl dot){
  for (jj = 0; jj <n ; i++)                           // i는 0~9까지 10개의 숫자를 하나씩 표시 한다
  {
    for (j = 0; j <8; j++)                            // j는 미리 제작한 비트맵의 y축 8비트 신호를 하나씩 보낸다
    {
      dot.setRow(0, j, inje[i][j]);           // setRow는 x축 LED를 한번에 제어하며,
    }                                                         // (첫번째 모듈 , y축 신호, 2차원배열값 [숫자] [8비트신호])
  delay (500);                                         // 0.5초의 딜레이
  }
}
