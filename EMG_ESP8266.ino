#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> //Library
#include <BlynkSimpleEsp8266.h> //Library

#define ssid "Nasi Bebek" //wifi
#define pass "123kayanya" // wifi
//#define BLYNK_TEMPLATE_ID "TMPLpCT2XruL"
//#define BLYNK_DEVICE_NAME "TrashCanIoT"
#define auth "cz6HBmX0L8jmGv8UJ3lQFoB0CMBGO6nK"
#define BLYNK_HEARTBEAT 100

const int sensorPin = A0;
const int sensInterval = 10000;
unsigned long sensTimer;
const int blynkInterval = 10050;
unsigned long blynkTimer;
float voltage;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
}

void loop() {
  if(millis() - sensTimer >= sensInterval){
    sensTimer = millis();
    sensing();
  } 
  if(millis() - blynkTimer >= blynkInterval){
    blynkTimer = millis();
    blynkCek();
  } 
}

void sensing(){ 
  int sensorValue[20]={0};
  int avgSensorValue=0;
  int currentSensorValue=0;
  int i=0;
  for(i=0 ; i<20 ; i++){
    sensorValue[i] = analogRead(sensorPin);
    avgSensorValue += sensorValue[i];
  }
  currentSensorValue = avgSensorValue/20;
  voltage=currentSensorValue*3.3/1024;
  Blynk.virtualWrite(V1, currentSensorValue);
  Blynk.virtualWrite(V2, voltage);
  //Serial.print("sensor = ");
  Serial.println(currentSensorValue);
  Serial.println(voltage, 3);
}
void blynkCek()
{
  if (Blynk.connected()==false) 
  {
    Serial.print("Koneksi Server Terputus...");
    Serial.println();
    Blynk.connect();
  }
}