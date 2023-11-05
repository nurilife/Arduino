#include <EtherCard.h>
//#define STATIC 0 
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
//static byte myip[] = { 192,168,0,6 };
//static byte gwip[] = { 192,168,0,1 };
int ledPin10 = 9;
byte Ethernet::buffer[700];
char const page[] PROGMEM =

"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
"<head><title>"
"Service Temporarily Unavailable"
"</title></head>"
"<body>"
"<h3>This page is used behind the scene</h3>"
"<p><em>"
"Commands to control LED are transferred to Arduino.<br />"
"The syntax: http://192.168.0.XX/?LED10=OFF or ON"
"</em></p>"
"</body>"
"</html>"
;

void setup () {
pinMode(ledPin10, OUTPUT);
Serial.begin(9600);
Serial.println("Trying to get an IP...");
Serial.print("MAC: ");
for (byte i = 0; i < 6; ++i) {
Serial.print(mymac[i], HEX);
if (i < 5)
Serial.print(':');
}
Serial.println();
if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
{
Serial.println( "Failed to access Ethernet controller");
}
else
{
Serial.println("Ethernet controller access: OK");
}
;

/* #if STATIC
Serial.println( "Getting static IP.");
if (!ether.staticSetup(myip, gwip)){
Serial.println( "could not get a static IP");
blinkLed(); // blink forever to indicate a problem
}
#else
*/
  
Serial.println("Setting up DHCP");
if (!ether.dhcpSetup()){
Serial.println( "DHCP failed");
// blinkLed(); 
}
//#endif

ether.printIp("My IP: ", ether.myip);
ether.printIp("Netmask: ", ether.netmask);
ether.printIp("GW IP: ", ether.gwip);
ether.printIp("DNS IP: ", ether.dnsip);
}
void loop () {

word len = ether.packetReceive();
word pos = ether.packetLoop(len);

// IF LED10=ON turn it ON
if(strstr((char *)Ethernet::buffer + pos, "GET /?LED10=ON") != 0) {   //Ethernet::buffer에 저장된 패킷을 수신하여 처리
  //strstr() 함수는 "GET /?LED10=ON" 문자열이 Ethernet::buffer에 저장된 패킷에 포함되어 있는지 여부를 확인하는 함수
  //(char *)Ethernet::buffer + pos: 수신된 패킷에서 "pos" 위치부터 시작하여 문자열을 가리킵니다.
Serial.println("Received ON command");
digitalWrite(ledPin10, HIGH);
}

// IF LED10=OFF turn it OFF
if(strstr((char *)Ethernet::buffer + pos, "GET /?LED10=OFF") != 0) {
Serial.println("Received OFF command");
digitalWrite(ledPin10, LOW);
}

// show some data to the user
memcpy_P(ether.tcpOffset(), page, sizeof page);  //ether.tcpOffset() 함수를 호출하여 페이지 변수에 저장된 HTML 코드를 Ethernet::buffer에 복사
   //memcpy_P() 함수는 프로그램 메모리에 저장된 데이터를 일반 메모리에 복사하는 역할
   //ether.tcpOffset() 함수는 Ethernet::buffer 내에서 TCP 데이터가 시작되는 위치를 반환
   //page 변수에는 웹 페이지의 HTML 코드가 저장  
ether.httpServerReply(sizeof page - 1);  //ether.httpServerReply() 함수를 호출하여 복사된 HTML 코드를 사용자에게 전송
}

void blinkLed(){
while (true){
digitalWrite(ledPin10, HIGH);
delay(500);
digitalWrite(ledPin10, LOW);
delay(500);
}
}
