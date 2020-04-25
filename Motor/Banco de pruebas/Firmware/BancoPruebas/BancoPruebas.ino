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
#define PIN_RELE  D8

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = D2;
const int LOADCELL_SCK_PIN = D3;
const char *ssid = APSSID;
const char *password = APPSK;
const float PATRON = 138.5;     //TODO: Falta calibrar bien

//ESP8266WebServer server(8000);
WiFiServer wifiServer(8000);
int led = 0;


HX711 scale;
float gramos = 0, lectura = 0, tiempo = 0;
int   BufferIdx = 0;
char Buffer[10240];
char DataBuffer[10000];


void setup() {
  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, LOW);
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.print("Configurando access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  wifiServer.begin();

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  
  Serial.print("Valor ADC:  ");
  Serial.println(scale.read());
  scale.set_scale(PATRON);        // Este valor, se tomo a mano, depende de la construccion del banco
  scale.tare(60);                 //El peso actual es considerado Tara, se hacen 60 mediciones, asi que lleva un tiempo, pero con esto se logra un error menor a 1 gramo
/*/  
  // Esto es para calibrar, el valor que se muestre en el serial hay que usarlo como 
  Serial.print("Lectura del valor del ADC:  ");
  Serial.println(scale.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  scale.set_scale(); //La escala por defecto es 1
  scale.tare(20);  //El peso actual es considerado Tara.
  Serial.println("Coloque un peso conocido:");//*/
}

void loop() {  
  WiFiClient cliente  = wifiServer.available();    
  while (cliente.connected()) {        
    digitalWrite(PIN_RELE, HIGH);
    digitalWrite(LED_BUILTIN, LOW); 
    lectura = -scale.get_units(3);
    tiempo = millis();
    sprintf(DataBuffer, "{\"T\":%.3f,\"grs\":%.2f}", tiempo/1000, lectura);    
    Serial.println(lectura,3);
    //scale.power_down();      
    cliente.write(DataBuffer);    
    //scale.power_up();
  }
  if(cliente.connected()){
    cliente.stop();        
    digitalWrite(PIN_RELE, LOW);
  }
  else  
    delay(1);
  led++;
  if(led < 100){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(PIN_RELE, LOW);
  }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(PIN_RELE, LOW);
  }
  if(led > 1000){
    led = 0;      
    lectura = -scale.get_units(3);
    tiempo = millis();
    Serial.print(" s\nPeso: ");
    Serial.print(lectura,3);
    Serial.print(" g  Tiempo: ");
    Serial.print(tiempo/1000,3);
  }
}
