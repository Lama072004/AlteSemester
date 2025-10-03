

//L298 eine der beiden Brücken wird zur Drehzahlsteuerung eines Gleichstrommotors verwendet
 

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  DDRK=B11111111;
}

// the loop function runs over and over again forever
void loop() {

  PORTK=B00000010;   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(250);                       // wait for a second
  PORTK=B00000011;    // turn the LED off by making the voltage LOW
  delayMicroseconds(50);                       // wait for a second
 
}
