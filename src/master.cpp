// Master
#include "MasterBluetooth.h" 
#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial Bluetooth_Master;
u_int8_t slaveMacAddress[] = {0xF4, 0x65, 0x0B, 0x47, 0x1D, 0x6A};

void setupMasterBluetooth() {
	Serial.begin(9600);
	Serial.setTimeout(5000);
	
	if (Bluetooth_Master.begin("União Soviética ESP", true)) {
		Serial.println("O Bluetooth foi iniciado corretamente | :)");
		Serial.print(Bluetooth_Master.getBtAddressString());
	} else {
		Serial.print("O Bluetooth não foi iniciado corretamente | :(");
	}

	if (Bluetooth_Master.connect(slaveMacAddress)) {
		Serial.print("Conectado");
	} else {
		Serial.println("O Bluetooth não foi conectado corretamente. | >:(");
	}
}

void loopMasterBluetooth() {
	if (Bluetooth_Master.available()) {
		String receivedMessage = Bluetooth_Master.readStringUntil('\n');
		receivedMessage.trim();
		printf("Mensagem recebida: %s", receivedMessage);
	}

	if (Bluetooth_Master.available()) {
		String toSendMessage = Bluetooth_Master.readStringUntil('\n');
		toSendMessage.trim();
		printf("Mensagem recebida: %s", toSendMessage);
	}
}