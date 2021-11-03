#include<stdio.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
void tostring(uint8_t Temperature[], int num);
DHT my_sensor(5, DHT22);
#define mqtt_server "192.168.0.75"

#define mqtttest "temp1"
const char* ssid = "NAMA_WIFI_28";
const char* password = "5Nov1995coolbk";

WiFiClient espClient;
PubSubClient client(espClient); 

 
 float temp;
 char Temperature[10];
void setup() {

Serial.begin(115200);
my_sensor.begin();
Serial.print("connecting to ");
Serial.println(ssid);
WiFi.mode(WIFI_STA);
WiFi.disconnect();
delay(2000);
WiFi.begin(ssid,password);
while (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
  }
  Serial.print("");
  Serial.print("WIFI connected");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());

  client.setServer(mqtt_server,1883);   
  client.connect ("espIOT");
  
}

void loop() {
  // put your main code here, to run repeatedly:

 temp = my_sensor.readTemperature();

sprintf(Temperature,"%.3f", temp);
Serial.println(temp);


client.publish(mqtttest,(uint8_t *)Temperature,5,true);
delay(2000);


}
