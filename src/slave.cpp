// Slave
#include "SlaveBluetooth.h" 
#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial Bluetooth;
// Address -> 14:33:5C:0B:2B:76

void setupSlaveBluetooth() {
	Serial.begin(9600);
	Serial.setTimeout(5000);
	
	if (Bluetooth.begin("União Soviética ESP")) {
		Serial.println("O Bluetooth foi iniciado corretamente | :)");
		Serial.println(Bluetooth.getBtAddressString());
	} else {
		Serial.println("O Bluetooth não foi iniciado corretamente | :(");
	}
}

void loopSlaveBluetooth() {
    if (Bluetooth.available())
    {
        String receivedMessage = Bluetooth.readStringUntil('\n');
        receivedMessage.trim();
		Serial.print('\n');
        Serial.printf("Mensagem recebida: %s", receivedMessage);
    }

    if (Serial.available())
    {
		Serial.print("Mensagem a enviar: ");
        String toSendMessage = Serial.readStringUntil('\n');
        toSendMessage.trim();
        Bluetooth.println(toSendMessage);
    }
}