#include <VirtualWire.h>
#include <Timer.h>

#define CH1 8          // Move trailer tilt upwards
#define CH2 7          // Move trailer tilt downwards
#define RX_PIN 12      // Radio pin
#define DATASPEED 4000 // Bits per sec

Timer t;
int count = 0;

void setup() {
  Serial.begin(9600);
  // Setup Relay
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);

  // Turn off power to relays
  digitalWrite(CH1, LOW);
  digitalWrite(CH2, LOW);

  // Setup Radio Receiver
  vw_set_rx_pin(RX_PIN);
  vw_setup(DATASPEED);
  pinMode(13, OUTPUT);

  // Start the receiver PLL running
  vw_rx_start();

  int tickEvent = t.every(1000, tick_counter, NULL);
}

void parse_instr(uint8_t * buf){
    if(buf[0]=='U'){
      digitalWrite(CH1, HIGH);
      digitalWrite(CH2, LOW);
    }
    if(buf[0]=='0'){
      digitalWrite(CH1, LOW);
      digitalWrite(CH2, LOW);
    }
    if(buf[0]=='D'){
      digitalWrite(CH1, LOW);
      digitalWrite(CH2, HIGH);
    }
    count = 0;
}

void handle_loneliness(){
  digitalWrite(CH1, LOW);
  digitalWrite(CH2, LOW);
  Serial.println("Lonley as fuck");
}

void tick_counter(void *context){s
  count += 1;
  Serial.println(count);
}

void loop() {
  t.update();
  if(count > 5){
    handle_loneliness();
    count = 0;
  }
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    parse_instr(buf);
  }
}
