
#include "pitches.h"
#include <ArduinoBLE.h>

BLEService speakerService("19B10000-E8F2-537E-4F6C-D104768A1214");  // Bluetooth® Low Energy LED Service

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic playNote("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);


void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("start");

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1)
      ;
  }

  pinMode(6, OUTPUT);

  // set advertised local name and service UUID:
  BLE.setLocalName("Speaker");
  BLE.setAdvertisedService(speakerService);

  // add the characteristic to the service
  speakerService.addCharacteristic(playNote);

  // add service
  BLE.addService(speakerService);

  // set the initial value for the characteristic:
  playNote.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("BLE Speaker Peripheral");

  // tone(13, NOTE_C4);
}

void loop() {

  // digitalWrite(13, HIGH);

  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      // if (switchCharacteristic.written()) {
      //   if (switchCharacteristic.value()) {   // any value other than 0
      //     Serial.println("LED on");
      //     digitalWrite(ledPin, HIGH);         // will turn the LED on
      //   } else {                              // a 0 value
      //     Serial.println(F("LED off"));
      //     digitalWrite(ledPin, LOW);          // will turn the LED off
      //   }
      // }

      if (playNote.written()) {
        if (playNote.value()) {

          Serial.println("written");
          tone(6, NOTE_A4);

        }

        else {
          Serial.println(F("not working"));
          noTone(6);
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
