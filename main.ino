void setup() {
  Serial.begin(9600);
}

void doThing1() {
  Serial.println("Thing1");
}

void doThing2() {
  Serial.println("Thing2");
}

void loop() {

}

void serialEvent() {
  while (Serial.available()) {
    const char inChar = (char)Serial.read();

    switch (inChar)
    {
      case 'A':
        doThing1();
        break;
      case 'B':
        doThing2();
        break;
      default:
        break;
    }
  }
}