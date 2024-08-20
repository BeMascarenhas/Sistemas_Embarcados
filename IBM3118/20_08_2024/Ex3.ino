#include <Ultrasonic.h>
#define pino_trigger 2
#define pino_echo 3

Ultrasonic ultrasonic (pino_trigger, pino_echo);

void setup() {
  Serial.begin(9600);
  Serial.println("Lendo sensor");
}

void loop() {
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  Serial.print ("Distancia em cm: ");
  Serial.println (cmMsec);
  Serial.print("Distancia em polegadas: ");
  Serial.println(inMsec);
  delay(1000);


}
