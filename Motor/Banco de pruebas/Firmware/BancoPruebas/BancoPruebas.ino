/**
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
#include "HX711.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "BancoPruebasCdR"
#define APPSK  "cdr_coheteria2019"
#endif

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = D2;
const int LOADCELL_SCK_PIN = D3;
const char *ssid = APSSID;
const char *password = APPSK;
const float CALIBRAR = 11.4;
const float PATRON = 204.4;

//ESP8266WebServer server(8000);
WiFiServer wifiServer(8000);
int led = 0;


HX711 scale;
float gramos = 0, lectura = 0, tiempo = 0;
int   BufferIdx = 0;
char Buffer[10240];
char DataBuffer[10000];


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  Serial.println();
  Serial.print("Configurando access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  wifiServer.begin();
  
  Serial.print("Inicializando la escala...");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");  
}

void loop() {  
  WiFiClient cliente  = wifiServer.available();    
  while (cliente.connected()) {
    digitalWrite(LED_BUILTIN, LOW); 
    tiempo = millis();
    lectura = -scale.get_units(1);
    gramos = lectura*PATRON/CALIBRAR;
    sprintf(DataBuffer, "{\"T\":%.3f,\"grs\":%.2f}", tiempo/1000, gramos); 
    scale.power_down();      
    cliente.write(DataBuffer);    
    scale.power_up();
  }
  if(cliente.connected()) 
    cliente.stop();
  else  
    delay(1);
  led++;
  if(led < 100){
    digitalWrite(LED_BUILTIN, LOW);
  }
  else
    digitalWrite(LED_BUILTIN, HIGH);
  if(led > 1000){
    led = 0;
  }
}
