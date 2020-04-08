#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <Wire.h>

#include <BMP180MI.h>

#define I2C_ADDRESS 0x77

//create an BMP180 object using the I2C interface
BMP180I2C bmp180(I2C_ADDRESS);

#ifndef STASSID
#define STASSID "WiFi-Arnet-kxde"
#define STAPSK  "dkfkchxbm4"
#define IP_PC     "192.168.1.3"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = IP_PC;//"192.168.0.245";
const uint16_t port = 8050;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  

  //wait for serial connection to open (only necessary on some boards)
  while (!Serial);

  Wire.begin();

  //begin() initializes the interface, checks the sensor ID and reads the calibration parameters.  
  if (!bmp180.begin())
  {
    Serial.println("begin() failed. check your BMP180 Interface and I2C Address.");
    while (1);
  }

  //reset sensor to default parameters.
  bmp180.resetToDefaults();

  //enable ultra high resolution mode for pressure measurements
  bmp180.setSamplingMode(BMP180MI::MODE_UHR);//*/
  
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

void loop() {
  unsigned int Tiempo = 0; float Temperatura = 0, Presion = 0; 
  char buffer[32];
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    //Serial.println("connection failed");
    //delay(5000);
    //return;
  }
  while(1){
    if (client.connected()) {
      digitalWrite(LED_BUILTIN, HIGH);//Led On miestras toma las medidas
      //wait for the measurement to finish. proceed as soon as hasValue() returned true. 
      if (!bmp180.measureTemperature())
        client.println("could not start temperature measurement, is a measurement already running?");
      do{
        delay(10);
        Tiempo+=10;
      } while (!bmp180.hasValue());//*/
      Temperatura=bmp180.getTemperature();
      if (!bmp180.measurePressure())
        client.println("could not start temperature measurement, is a measurement already running?");
      do{
        delay(10);
        Tiempo+=10;
      } while (!bmp180.hasValue());//*/
      Presion=bmp180.getPressure();
      digitalWrite(LED_BUILTIN, LOW);//Led off
      
      sprintf(buffer, "{\"T\":%d,\"P0\":%.2f"/*,\"T0\":%.2f}"*/, Tiempo, Presion/*, /*Temperatura*/);
      ESP.wdtFeed();
      //sprintf(buffer, "{\"Tiempo\":%d,", Tiempo);
      //client.print(buffer);
      //sprintf(buffer, "\"Presion\":%.2f, ", Presion);
      client.print(buffer);
      //sprintf(buffer, "\"Temperatura\":%f}", Temperatura);*/
      //client.print(buffer);
      delay(200);
      Tiempo+=200;
    }
  }
}
