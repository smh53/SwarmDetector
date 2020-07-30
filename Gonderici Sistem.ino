#include "mythologygsm.h"
#include "SoftwareSerial.h"
#include <Sodaq_DS3231.h>
#include <Wire.h>
mythologygsm mythologygsm;
SoftwareSerial BluetoothSerial(10, 11); // TX | RX

void setup() {
 Serial.begin(9600);
 BluetoothSerial.begin(9600);  
 Wire.begin();
 rtc.begin();
}

uint32_t old_ts;

void loop(){
   DateTime now = rtc.now(); //get the current date-time
   uint32_t ts = now.getEpoch();
   float x[2];
   String message = "0";
 
 while ( BluetoothSerial.available() ) {
  if ( message == "0" ) {
    String saat = (String)now.hour() + ":" + (String)now.minute() + ":" + (String)now.second() ;
    message = (BluetoothSerial.readStringUntil('\n'));  
    delay(1000);
    x[1] = message.toFloat();
    mythologygsm.mesaj_yollama("+905457430886", "1 Nolu Kovanda : " + saat + " 'saatinde " + x[1] + " kg dusus goruldu ve"); 
    Serial.println("Kilo Değeri : ");
    Serial.print(String(x[1]));
    Serial.println(" kg");
    Serial.println("Saat : ");
    Serial.println(saat);
   }
   else if ( message != "0") {
    String saat = (String)now.hour() + ":" + (String)now.minute() + ":" + (String)now.second() ;
    message = (BluetoothSerial.readStringUntil('\n'));
    delay(1000);
    x[0] = message.toFloat();
    mythologygsm.mesaj_yollama("+905457430886", String(x[0]) + " Celcius sicaklik artisi tespit edildi."); 
    Serial.println("Sicaklik Değeri : ");
    Serial.print(x[0]);
    Serial.println(" Celcius");
    message = "0";   
   }
   continue;
 }
  mythologygsm.seri_durum();
}
