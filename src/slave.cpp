#include <Arduino.h>
#include <BluetoothSerial.h>
#include "led.h"
#include "slave.h"

int mainLedPin = 26;
bool isBlinking = false;

BluetoothSerial BTSlave;

void setupSlave() {
    setupLED(mainLedPin);
    Serial.begin(9600);
    Serial.setTimeout(5000);

    if (BTSlave.begin("webvinicDevice"))
    {
        Serial.println("Bluetooth iniciado com sucesso");
        Serial.print("ESP MAC Address: ");
        Serial.println(BTSlave.getBtAddressString());
    } else
    {
        Serial.println("Error para iniciar o Bluetooth");
    }
}

void loopSlave() {
    if (BTSlave.available())
    {
        String receivedMessage = BTSlave.readStringUntil('\n');
        receivedMessage.trim();
        Serial.printf("Mensagem Recebida: %s\n", receivedMessage.c_str());

        if (receivedMessage == "liga") {
            isBlinking = false;
            turnOnLED(mainLedPin);
            Serial.println("LED ligado");
        } else if (receivedMessage == "desliga") {
            isBlinking = false;
            turnOffLED(mainLedPin);
            Serial.println("LED desligado");
        } else if (receivedMessage == "pisca") {
            isBlinking = true;
            Serial.println("LED piscando");
        }
    }

    if (Serial.available())
    {
        String messageToSend = Serial.readStringUntil('\n');
        messageToSend.trim();
        BTSlave.println(messageToSend);
    }

    if (isBlinking) {
        blinkLed(mainLedPin);
    }
}