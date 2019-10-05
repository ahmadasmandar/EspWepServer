#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

#define SSID_Name "Mahya"
#define PASSWD "102030ugd"
void turn_led_off();
boolean blink_flag = false;
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
  Serial.println("Connected");

  Serial.println("Ip Adresse: ");
  Serial.print(WiFi.localIP());

  server.begin();
  server.onNotFound([]() {
    server.send(404, "text/html", "<h1>Error page not Found</h1>");
  });
  server.on("/", []() {
    server.send(200, "text/html", "<h1><p style="
                                  "text-align:center;"
                                  ">"
                                  "	HalloWorld!	 </p></h1>");
  });

  server.on("/on", []() {
    server.send(200, "text/plain", "Led is turned on");
    blink_flag = true;
  });
  server.on("/off", []() {
    server.send(200, "text/plain", "Led is turned off");
    blink_flag = false;
  });

  pinMode(2, OUTPUT);
}

void loop()
{
  server.handleClient();

  if (blink_flag)
  {
    digitalWrite(2, 1);
    delay(500);
    digitalWrite(2, 0);
    delay(500);
  }

  // put your main code here, to run repeatedly:
}

void turn_led_off(){
  digitalWrite(2, 0);
}