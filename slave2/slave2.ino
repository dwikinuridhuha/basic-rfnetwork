#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include "printf.h"
#include <string.h>

RF24 radio(10, 9);
RF24Network network(radio);

const uint16_t kordinator = 00;
const uint16_t this_node = 02;

char text[25] = "ok slave 2";

void setup() {
  Serial.begin(9600);
  printf_begin();
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);
  radio.printDetails();
}

void loop() {
  network.update();
  delay(2000);
  Serial.println("mengirim ke node kordinator");
  RF24NetworkHeader header(kordinator);
  bool ok = network.write(header, &text, sizeof(text));
  Serial.print("status pengiriman: ");
  Serial.println(ok);
}
