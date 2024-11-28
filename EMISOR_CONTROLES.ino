//EMISOR - ARDUINO NANO - CONTROL1 ARMADO - AMARILLO

#include <SPI.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
const uint64_t canal = 0x6E6E6ELL;

struct JoystickData {
  int x;
  int y;
  bool button;
};

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP); // Configura D3 como entrada con resistencia pull-up
  radio.begin();
  radio.openWritingPipe(canal);
  radio.stopListening();
}

void loop() {
  JoystickData data;
  data.x = analogRead(A2);
  data.y = analogRead(A4);
  data.button = digitalRead(3)== LOW; // Leer el estado del botón

  radio.write(&data, sizeof(data));
  Serial.print("X: "); Serial.print(data.x);
  Serial.print(", Y: "); Serial.print(data.y);
  Serial.print(", Button: "); Serial.println(data.button);

  delay(100);
}