#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial BTSerial;

int buttonPin = 22;
int lastButtonState = HIGH;      
unsigned long pressStartTime = 0; 
bool longPressSent = false;     
const long LONG_PRESS_TIME = 2000; 

uint8_t slaveAddress[] = {0xF4, 0x65, 0x0B, 0x54, 0xA3, 0x86};

void setupMaster(){
    Serial.begin(9600);
    Serial.setTimeout(5000);

    pinMode(buttonPin, INPUT_PULLUP);

    if (BTSerial.begin("webvinicDevice", true))
    {
        Serial.println("Bluetooth (Master) iniciado com sucesso");
    } else
    {
        Serial.println("Erro ao iniciar o bluetooth");
    }

    Serial.println("Tentando conectar ao Slave...");
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

    int buttonState = digitalRead(buttonPin);

    if (buttonState == LOW && lastButtonState == HIGH) {
        pressStartTime = millis(); 
        longPressSent = false; 
        Serial.println("Botão pressionado...");
    }

    if (buttonState == HIGH && lastButtonState == LOW) {
        if (!longPressSent) {
            Serial.println("Enviando: CLICK");
            BTSerial.println("CLICK");
        }
    }

    if (buttonState == LOW && lastButtonState == LOW) {
        if (!longPressSent && (millis() - pressStartTime > LONG_PRESS_TIME)) {
            Serial.println("Enviando: LONG_PRESS");
            BTSerial.println("LONG_PRESS");
            longPressSent = true; 
        }
    }

    lastButtonState = buttonState;
}