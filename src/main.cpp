#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

ESP8266WebServer server(80);
//*************** variables 

#define SSID_Name "IOTAP"
#define PASSWD "102030ahmad"
void turn_led_off();
void receive_update();
boolean blink_flag = false;
boolean update_flag = true;
float update_timer=0;
void setup()
{
  Serial.begin(115200);
  WiFi.begin(SSID_Name, PASSWD);
  Serial.println();
  Serial.println("Wifi is Connecting.....");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
      type = "sketch";
    }
    else
    { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  server.onNotFound([]() {
    server.send(404, "text/html", "<h1>Error page not Found</h1>");
  });
  server.on("/", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", "<h1><p style="
                                  "text-align:center;"
                                  ">"
                                  "	HalloWorld!	 </p></h1>"
                                  "Access-Control-Allow-Origin: *");
  });

  server.on("/on", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "Led is turned on");
    blink_flag = true;
  });
  server.on("/off", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "Led is turned off");
    blink_flag = false;
  });
  server.on("/update", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200,"text/plain" ,"System is ready to be updated ....");
    receive_update();
     });
     server.on("/reset", []() {
       server.sendHeader("Access-Control-Allow-Origin", "*");
       server.send(200,"text/plain" ,"ESP will bes rested");
       delay(1000);
       ESP.restart();
        });

  pinMode(D5, OUTPUT);
}
//*************************************** Loop
void loop()
{
  //  ArduinoOTA.handle();

  server.handleClient();
  if (blink_flag)
  {
    digitalWrite(D5, HIGH);
    delay(100);
    digitalWrite(D5, LOW);
    delay(100);
  }
  if (!blink_flag)
  {
    digitalWrite(D5, LOW);
  }
  // put your main code here, to run repeatedly:
}

void receive_update()
{
  update_timer=millis();
  while (millis() - update_timer < 15000)
  {
    Serial.print(".");
    ArduinoOTA.handle();
    delay(20);
  }
  Serial.println("Update is complete");
  Serial.println("System Restart in 5.......");
  delay(5000);
  ESP.restart();
}