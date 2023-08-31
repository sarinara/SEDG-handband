/*
 * Bluetooth Low Energy Peripheral (also called Slave, Server) demo application for Arduino Nano 33 IoT
 * 1. Advertises one service with 3 characteristics:
 *    - characteristic which supports read (BLE Central can only read)
 *    - characteristic which supports write (BLE Central can only write, with response)
 *    - characteristic which supports indication (BLE Central can only subscribe and listen for indications)
 */

#include <ArduinoBLE.h>
#include <string>

// --------
// Constants
// --------
#define SERVICE_UUID        "25AE1441-05D3-4C5B-8281-93D4E07420CF"
#define CHAR_READ_UUID      "25AE1442-05D3-4C5B-8281-93D4E07420CF"
#define CHAR_WRITE_UUID     "25AE1443-05D3-4C5B-8281-93D4E07420CF"
#define CHAR_INDICATE_UUID  "25AE1444-05D3-4C5B-8281-93D4E07420CF"

// --------
// Global variables
// --------
static BLEService g_service(SERVICE_UUID);
static BLEStringCharacteristic g_charRead(CHAR_READ_UUID, BLERead, 512);
static BLEStringCharacteristic g_charWrite(CHAR_WRITE_UUID, BLEWrite, 512);
static BLEStringCharacteristic g_charIndicate(CHAR_INDICATE_UUID, BLEIndicate, 512);
static bool g_isCentralConnected = false;

int sensorPin = A0;   // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int outputValue;

// --------
// Application lifecycle: setup & loop
// --------
void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(9600);
    while (!Serial);

    if (!BLE.begin())
    {
    }
    BLE.setLocalName("SEDG_Sarah");
    BLE.setAdvertisedService(g_service);

    BLE.setEventHandler(BLEConnected, [](BLEDevice central)
    {
        g_isCentralConnected = true;
        Serial.println("Event: central connected");
    });

    BLE.setEventHandler(BLEDisconnected, [](BLEDevice central)
    {
        g_isCentralConnected = false;
        Serial.println("Event: central disconnected");
    });

    // characteristic for read
    {
        g_service.addCharacteristic(g_charRead);
        g_charRead.writeValue("NANO33 for read");
        g_charRead.setEventHandler(BLERead, [](BLEDevice central, BLECharacteristic characteristic)
        {
            Serial.print("Event: characteristic read, value='");
            Serial.print(g_charRead.value());
            Serial.println("'");
        });
    }

    // characteristic for write
    {
        g_service.addCharacteristic(g_charWrite);
        g_charWrite.setEventHandler(BLEWritten, [](BLEDevice central, BLECharacteristic characteristic)
        {
            Serial.print("Event: characteristic write, value='");
            Serial.print(g_charWrite.value());
            Serial.println("'");
        });
    }

    // characteristic for indicate
    {
        g_service.addCharacteristic(g_charIndicate);
        g_charIndicate.setEventHandler(BLESubscribed, [](BLEDevice central, BLECharacteristic characteristic)
        {
            Serial.println("Event: central subscribed to characteristic");
        });
        g_charIndicate.setEventHandler(BLEUnsubscribed, [](BLEDevice central, BLECharacteristic characteristic)
        {
            Serial.println("Event: central unsubscribed from characteristic");
        });
    }

    BLE.addService(g_service);
    BLE.advertise();

    Serial.println("BLE setup done, advertising...");
    Serial.println("");
}


int counter = 0;
void loop()
{

    sensorValue = analogRead(sensorPin);
    outputValue = map(sensorValue, 0, 1023, 0, 255);
    Serial.println(outputValue);
    delay(50);
    if (outputValue < 150) {
      counter++;
    }
    if (outputValue > 225) {
      counter = 0;
    }

    if (counter >= 5) {
      Serial.println("HERERRERER");
      g_charIndicate.writeValue("yes");
    }
    if (counter == 0) {
      g_charIndicate.writeValue("no");
    }

    BLE.poll();
    if (!Serial.available())
    {
        return;
    }
}