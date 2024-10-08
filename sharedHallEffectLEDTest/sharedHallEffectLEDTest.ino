int sharedPin = 4;
int state;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  pinMode(sharedPin,INPUT_PULLUP);
  int oldState = state;
  state = digitalRead(sharedPin);
  if (oldState != state){
    Serial.println("Change!");
  }
  pinMode(sharedPin,OUTPUT);
  if (state == 1){
    digitalWrite(sharedPin,HIGH);
  }
  else if (state == 0){
    digitalWrite(sharedPin,LOW);
  }
  Serial.println(state);

}
