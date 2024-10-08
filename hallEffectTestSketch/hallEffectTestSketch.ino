int magnetPin = 3;
int ledPin = 4;


void setup() {
  Serial.begin(9600);
  // There's an argument to use the internal pullup resistor here, but I honestly need to futz with pullup stuff more.
  // also an argument to just physically build a noise filter, because I don't really trust this that much.
  pinMode(magnetPin,INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);

}

void loop() {
  // turns on an LED if there's a signal from the hall effect sensor. Look, it's nothing crazy, but we gotta do tests
  
  digitalWrite(ledPin,digitalRead(magnetPin));
  Serial.println(digitalRead(magnetPin));


}
