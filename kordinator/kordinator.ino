#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include "printf.h"
#include <string.h>

RF24 radio(10, 9); // nRF24L01 (CE,CSN)
RF24Network network(radio);

const uint16_t slave1 = 01;
const uint16_t slave2 = 02;
const uint16_t thisNode = 00; //kordinator atau master

bool ok;
char incomingData[25];
float Throughput_pengiriman;

void setup() {
  Serial.begin(9600);
  printf_begin();
  SPI.begin();
  radio.begin();
  network.begin(90, thisNode);
  radio.printDetails();
}

void loop() {
  network.update();
  while (network.available()) {
    RF24NetworkHeader header;
    network.read(header, &incomingData, sizeof(incomingData));

    if (header.from_node == slave1) {
      Serial.print("data dari slave 1: ");
      Serial.println(incomingData);
    }

    if (header.from_node == slave2) {
      Serial.print("data dari slave 2: ");
      Serial.println(incomingData);
    }
  }
}
