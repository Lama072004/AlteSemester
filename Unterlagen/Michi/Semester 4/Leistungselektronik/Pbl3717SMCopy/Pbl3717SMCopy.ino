

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  DDRK=B11111111;
}

// the loop function runs over and over again forever
//portK is numbered up continously so we use this one (pin 8, 9.. see pinout-picture of ArduinoMega)
void loop() {

  PORTK=B01010000;   // turn the LED on (HIGH is the voltage level)
  delay(10);                       // wait
  PORTK=B00000101;    // turn the LED off by making the voltage LOW
  delay(10);                       // wait
  PORTK=B01010010;   // turn the LED on (HIGH is the voltage level)
  delay(10);                       // wait for a second
  PORTK=B00100101;    // turn the LED off by making the voltage LOW
  delay(10);                       // wait for a second
}
