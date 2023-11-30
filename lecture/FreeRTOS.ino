#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define led_Red 13
#define led_Green 12
#define led_Yellow 11

//define task handles
TaskHandle_t TaskBlink_1_Handler;
TaskHandle_t TaskBlink_2_Handler;
TaskHandle_t TaskBlink_3_Handler;
TaskHandle_t TaskSerial_Handler;

SemaphoreHandle_t sem_1;
SemaphoreHandle_t sem_2;

// define two tasks for Blink & Serial
void TaskBlink_1( void *pvParameters );
void TaskBlink_2( void *pvParameters );
void TaskBlink_3( void *pvParameters );
void TaskSerial(void* pvParameters);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

//  sem_1 = xSemaphoreCreateCounting(2, 0); //세마포어를 주고 시작함
//  sem_2 = xSemaphoreCreateCounting(2, 1);
  
  // Now set up two tasks to run independently.
   xTaskCreate(
    TaskBlink_1
    ,  "Blink_1"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters passed to the task function
    ,  4  // Priority, with 2 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &TaskBlink_1_Handler );//Task handle

   xTaskCreate(
    TaskBlink_2
    ,  "Blink_2"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters passed to the task function
    ,  3  // Priority, with 2 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &TaskBlink_2_Handler );//Task handle

   xTaskCreate(
    TaskBlink_3
    ,  "Blink_3"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters passed to the task function
    ,  2  // Priority, with 2 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &TaskBlink_3_Handler );//Task handle    

   xTaskCreate(
    TaskSerial
    ,  "Serial"
    ,  128  // Stack size
    ,  NULL //Parameters passed to the task function
    ,  1  // Priority
    ,  &TaskSerial_Handler );  //Task handle

}
    

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskSerial(void* pvParameters){
/*
 Serial
 Send "s" or "r" through the serial port to control the suspend and resume of the LED light task.
 This example code is in the public domain.
*/
  (void) pvParameters;
   for (;;) // A Task shall never return or exit.
   {
    while(Serial.available()>0){
      switch(Serial.read()){
        case 's':
          vTaskSuspend(TaskBlink_1_Handler); 
          vTaskSuspend(TaskBlink_2_Handler); 
          Serial.println("Suspend!");
          break;
        case 'r':
          vTaskResume(TaskBlink_1_Handler);
          vTaskResume(TaskBlink_2_Handler); 
          Serial.println("Resume!");
          break;
      }
      vTaskDelay(1);
    }
   }
}

void TaskBlink_1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  pinMode(led_Red, OUTPUT);
  for (;;) // A Task shall never return or exit.
  {
//    xSemaphoreTake(sem_1, portMAX_DELAY);
    //Serial.println(11);
    digitalWrite(led_Red, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(led_Red, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for one second 
//    xSemaphoreGive(sem_2); 

  }
}

void TaskBlink_2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  pinMode(led_Green, OUTPUT);
  for (;;) // A Task shall never return or exit.
  {
    //Serial.println(11);
//    xSemaphoreTake(sem_2, portMAX_DELAY);
    digitalWrite(led_Green, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(led_Green, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
//    xSemaphoreGive(sem_1);    

  }
}

void TaskBlink_3(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  pinMode(led_Yellow, OUTPUT);
  for (;;) // A Task shall never return or exit.
  {
    //Serial.println(11);
    digitalWrite(led_Yellow, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 3000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(led_Yellow, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 3000 / portTICK_PERIOD_MS ); // wait for one second
  }
}
