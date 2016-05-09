#include <Button.h>
#include <VirtualWire.h>

#define DATASPEED 4000 // Bits per sec
#define TX_PIN 12      // Radio pin
#define IN1_PIN 7
#define IN2_PIN 8

Button upButton = Button(IN1_PIN, PULLUP);
Button downButton = Button(IN2_PIN, PULLUP);

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

int val1 = 0;
int val2 = 0;

void loop(){
  val1 = digitalRead(IN1_PIN);
  val2 = digitalRead(IN2_PIN);
  
  if (upButton.isPressed()) {
    send_instr("UPP");
    digitalWrite(13, HIGH);
  } else if (downButton.isPressed()) {
    send_instr("NER");
    digitalWrite(13, HIGH);
  } else {
    send_instr("STP");
    digitalWrite(13, LOW);
  }
  delay(100);
}
