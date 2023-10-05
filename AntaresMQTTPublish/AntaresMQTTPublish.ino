#include <iostream>
#include <AntaresESP8266MQTT.h>
#include <SoftwareSerial.h>
#include <AntaresESP8266MQTT.h>
#include <vector>
#include <string>
#include <cstdio>

#define ACCESSKEY "4f87e8792f425a5e:323d91f33a549100"
#define WIFISSID "yosh"
#define PASSWORD "12345678"

#define projectName "PGO-Test-IoT"
#define deviceName "PGO"

#define RXD2 13
#define TXD2 15

using namespace std;

// #include <ESP8266WiFi.h>
char formattedData[5];
vector<String> formattedDatas;

AntaresESP8266MQTT antares(ACCESSKEY);
SoftwareSerial Serial2(RXD2, TXD2);
int data_serial;
// int i;


void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial.println("Start loop");
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
}

void loop() {
  antares.checkMqttConnection();

  while (Serial2.available()) {
    data_serial=Serial2.read();
    sprintf(formattedData, " %02X", data_serial); 
    // Serial.printf(" %02X",data);
    // antares.add(" %02X", data); 
    // antares.add("uhf", formattedData);
    // antares.publish(projectName, deviceName);
    // Serial.println(formattedData);    
    formattedDatas.push_back(formattedData);
  }

  String combinedString;
  for (const String& str : formattedDatas) {
    combinedString += str;
  }
  // Serial.println(combinedString);
  


  // delay(10000)
  if (!formattedDatas.empty()) {
      // cout << combinedString << endl;
      
      antares.add("uhf", combinedString); 
      antares.publish(projectName, deviceName);
      formattedDatas.clear();
      for (int i = 0; i < formattedDatas.size(); i++) {
        Serial.println(formattedDatas[i]);
      }
      return;
      // delay(5000);

  }
}
