#include <VirtualWire.h>

#define DATASPEED 4000 // Bits per sec
#define TX_PIN 12      // Radio pin

void setup() {
  pinMode(13, OUTPUT);

  // Setup Radio Transmitter
  vw_set_tx_pin(TX_PIN);
  vw_setup(DATASPEED);
}

void send_instr(const char * controller){
  vw_send( (uint8_t *) controller, strlen(controller) );
  vw_wait_tx();
}

void loop(){
  send_instr("U");// Up

  digitalWrite(13, HIGH);
  delay(1000);

  send_instr("0"); // Stop

  digitalWrite(13, LOW);
  delay(1000);

  send_instr("D"); // Down

  // BlinkyBlinky
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
}
