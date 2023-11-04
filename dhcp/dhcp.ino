#include  <EtherCard.h>
 
  //MAC주소-아래에서 지정한대로 설정됨
  static  byte  mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
 
  //이더넷 송수신 데이터 메모리 버퍼 설정
  byte Ethernet::buffer[700];
  void setup () {
   Serial.begin(57600);
   Serial.println(F("\n[testDHCP]"));
   
   //MAC 주소 찍기
 Serial.print("MAC: ");
 for (byte i = 0; i < 6; ++i) {
    Serial.print(mymac[i], HEX);
    if  (i < 5)
   Serial.print(':');
   
}
 Serial.println();
 
   //이더넷 연결 실패
 if  (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
  Serial.println(F("Failed to access Ethernet controller"));
 
   //DHCP 설정
 Serial.println(F("Setting up DHCP"));
 if  (!ether.dhcpSetup())
  Serial.println(F("DHCP failed"));
 
 ether.printIp("My IP: ", ether.myip);
 ether.printIp("Netmask: ", ether.netmask);
 ether.printIp("GW IP: ", ether.gwip);
 ether.printIp("DNS IP: ", ether.dnsip);
}
  void loop () {}
