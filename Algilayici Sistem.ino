/*
 * 
 *  Kırmızı ---- GND
 *  Sarı ------ dout
 *  T uruncu --- SCK
 *  Kahverengi --- VCC
 */

#include "HX711.h"
#include "string.h"
#include <SoftwareSerial.h>
#include <DHT.h>;
SoftwareSerial BTSerial(10, 11); // TX | RX
#define calibration_factor -23880.00 //Th
#define DOUT  3
#define CLK  2
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
HX711 scale;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.println("HX711 scale demo");
 BTSerial.begin(9600);  
 scale.begin(DOUT, CLK);
 dht.begin();
 scale.set_scale(calibration_factor); 
 scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
 Serial.println("Readings:");
}

void loop() {
  // put your main code here, to run repeatedly:
  static const uint32_t DELAY_1_S = 1000UL;
  static const uint32_t DELAY_1_MINUTE = DELAY_1_S * 60UL;
  static const uint32_t DELAY_1_HOUR   = DELAY_1_MINUTE * 60UL;
  float weights[10];
  float weight;
  float temps[10];
  float temp;
  int j=0;

 for (int i=0;i<10;i++)
  {
    float weight =  scale.get_units();// çıkış değeri
    weights[i]= weight;
    
    Serial.println("Weight:");
    Serial.println(weight);
    temp= dht.readTemperature();
    temps[j] = temp;
    j++;
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(500);
  }
 
 Serial.println("**************************************************");
  
  float f = weights[0] - weights[9]; 
  float t = temps[9]- temps[0];
    if(f>1.11 && t>2.30)
    { 
       char buffer[10];
       String fark = dtostrf(f, 2, 4, buffer);
       BTSerial.print(fark);
       delay(2000);     
       String tempa = dtostrf(temp, 2, 4, buffer);
       BTSerial.print(tempa);
       delay(20);     
    }
  Serial.println(weights[9]);
  delay(5000);
  Serial.println(temp);
}
