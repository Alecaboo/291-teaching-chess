/* 
  74HC165 Shift Register Demonstration 1
  74hc165-demo.ino
  Read from 8 switches and display values on serial monitor
 
  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/
 
// Define Connections to 74HC165
 
// PL pin 1
int load = 7;
// CE pin 15
int clockEnablePin = 4;
int clockTwo = 3;
// Q7 pin 7
int dataIn = 5;
int dataTwo = 8;

// CP pin 2
int clockIn = 6;
 
void setup()
{
 
  // Setup Serial Monitor
  Serial.begin(9600);
 
  // Setup 74HC165 connections
  pinMode(load, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);
  pinMode(clockTwo,OUTPUT);
  pinMode(dataTwo,INPUT);
}

int rowState[8] = {2,2,2,2,2,2,2,2};
int colState[8] = {2,2,2,2,2,2,2,2};


int states[8][8];

void loop()
{
 
  // Write pulse to load pin
  digitalWrite(load, LOW);
  delayMicroseconds(5);
  digitalWrite(load, HIGH);
  delayMicroseconds(5);
 
  // Get data from 74HC165
  digitalWrite(clockEnablePin, LOW);
  for(int i = 0; i < 8; i++){
    digitalWrite(clockEnablePin,HIGH);
    rowState[i] = digitalRead(dataIn);
    digitalWrite(clockEnablePin,LOW);
  }
  

  for(int i = 0; i < 8; i++){
    digitalWrite(clockTwo,HIGH);
    colState[i] = digitalRead(dataIn);
    digitalWrite(clockEnablePin,LOW);
  }
  digitalWrite(clockTwo,HIGH);

  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      if (rowState[i] == 1 == colState[j]){
        states[i][j] = 1;
      }
      else{
        states[i][j] = 0;
      }
    }
  }

// outputting to the serial, so I can test visualizing.
for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Serial.print(bigLED[i][j]);
        if (j < 7) Serial.print(", ");
      }
      Serial.println();
    }
    Serial.println("---");
    delay(500);

  // Print to serial monitor
  delay(200);
}
