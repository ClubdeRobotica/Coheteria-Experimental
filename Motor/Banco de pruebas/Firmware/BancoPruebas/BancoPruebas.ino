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

ESP8266WebServer server(80);


HX711 scale;
float gramos = 0, lectura = 0, tiempo = 0;
bool ClientOnline;

void handleRoot() {
  char Buffer[128];
  sprintf(Buffer, "<meta http-equiv=\"refresh\" content=\"0.1\";><h1>{\"T\":%.1f,\"grs\":%.2f}</h1>", tiempo, gramos);
  server.send(200, "text/html", Buffer);
  ClientOnline = true;
}


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configurando access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  
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
  tiempo = millis();
  Serial.print((tiempo / 1000), 1);
  Serial.print("\t ms\t");  
  lectura = -scale.get_units(3);
  Serial.print("\t| ");
  gramos = lectura*PATRON/CALIBRAR;
  Serial.print(gramos, 1);
  Serial.print(" gramos\n");  
   

  scale.power_down();             // put the ADC in sleep mode
  delay(10);
  server.handleClient();
  scale.power_up();
}
