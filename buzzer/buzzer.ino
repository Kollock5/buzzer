#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  mySwitch.enableTransmit(10);
  pinMode(LED_BUILTIN, OUTPUT);
}

int delayTimer = 0;
int delayFactor = 0;

void loop() {


  if (mySwitch.available()) {
    digitalWrite(LED_BUILTIN, HIGH); 


    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );

    mySwitch.resetAvailable();
  }

  delayFactor = delayFactor + 1;
  if (delayFactor > 100) {
    delayFactor = 0;
    delayTimer = delayTimer + 1;
  }

  if (delayTimer > 30000) {
    delayTimer = 0;

    digitalWrite(LED_BUILTIN, LOW);    
    Serial.println("Sending");
    mySwitch.send(2222, 24);
  }

}
