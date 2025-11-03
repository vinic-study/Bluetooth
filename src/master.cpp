#include <Arduino.h>
#include <BluetoothSerial.h>
#include "master.h"

BluetoothSerial BTSerial;

uint8_t slaveAddress[] = {0xF4, 0x65, 0x0B, 0x54, 0x58, 0xAE};

void setupMaster(){
    Serial.begin(9600);
    Serial.setTimeout(5000);

    if (BTSerial.begin("webvinicDevice", true))
    {
        Serial.println("Bluetooth iniciado com sucesso");
    } else
    {
        Serial.println("Erro ao iniciar o bluetooth");
    }

    if (BTSerial.connect(slaveAddress))
    {
        Serial.println("Conectado com sucesso");
    } else {
        Serial.println("Falha ao conectar");
    }
}

void loopMaster(){
    if (BTSerial.available())
    {
        String receivedMessage = BTSerial.readStringUntil('\n');
        receivedMessage.trim();
        Serial.printf("Mensagem recebida: %s\n", receivedMessage.c_str());
    }

    if (Serial.available())
    {
        String messageToSend = Serial.readStringUntil('\n');
        messageToSend.trim();
        BTSerial.println(messageToSend);
    }
}