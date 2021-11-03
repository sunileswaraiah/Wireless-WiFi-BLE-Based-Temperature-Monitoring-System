//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include "esp_bt_device.h"

#include "DHT.h"

#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
DHT dht(DHTPIN, DHTTYPE);
// Bluetooth Serial object
BluetoothSerial SerialBT;

void printDeviceAddress() {

  const uint8_t* point = esp_bt_dev_get_address();

  for (int i = 0; i < 6; i++) {

    char str[3];

    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);

    if (i < 5) {
      Serial.print(":");
    }

  }
}
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  Serial.println("Device Name: ESP32test");
  Serial.print("BT MAC: ");
  printDeviceAddress();
  Serial.println();
  dht.begin();
}
float t;
String temp = "";


void loop() {

  char buf[4] = {0};
  int i = 0;
  
    if (SerialBT.available()) {
    t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    temp = String(t);
    Serial.print(temp);
    SerialBT.println(temp);

    //SerialBT.write(t);
    Serial.println();
     delay(5000);

  }
}
