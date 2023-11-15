#include <LedControl.h>
LedControl dot =LedControl(12,11,10,2);
void shift_mat(byte* mat1, byte* mat2, String sft_direction, int n_shift, LedControl dot);
  byte mat1[8]={0x00, 0x6c, 0x52, 0x52, 0x4c, 0x40, 0x5e, 0x00}; //인
  byte mat2[8]={0x40, 0x22, 0x1e, 0x22, 0x48, 0x3e, 0x00, 0x7e}; //제

void setup(){
  for(int i = 0; i<2; i++){
    dot.shutdown(i, false);                  
    dot.setIntensity(i, 7);                     
    dot.clearDisplay(i); 
  }                         
}
void loop() 
{
  for (int j = 0; j<16; j++){     //왼쪽으로 움직이게
    shift_mat(mat1, mat2, "left", 1, dot);           
    delay(100);                                       
  }
}

void shift_mat(byte* mat1, byte* mat2, String sft_direction, int n_shift, LedControl dot){
  for (int jj = 0; jj <n_shift; jj++){      //시프트 횟수만큼 반복
    byte tmp1, tmp2;              //사용할 임시값들 선언
    tmp1 = mat1[0];               //매트릭스의 가장 첫 열을 임시값에 저장
    tmp2 = mat2[0];              
    for (int ii=0; ii<7; ii++){       //매트릭스의 다음 행을 이전 열에 저장
      mat1[ii] = mat1[ii+1];
      mat2[ii] = mat2[ii+1];                            
    }
     mat1[7] = tmp2;              //매트릭스의 끝 열에 임시값(첫열) 저장
     mat2[7] = tmp1;

  }                                                      
  for(int ii=0; ii<8; ii++){
    dot.setRow(0, ii, mat1[ii]);  //0번째 매트릭스에 mat1 출력
    dot.setRow(1, ii, mat2[ii]);  //1번째 매트릭스에 mat2 출력
  }
}
