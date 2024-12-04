/*
  Code partially sourced from DroneBotWorkShop, chatGPT, and potential divine intervention. Wish I knew what I wrote at 3am.

*/
 
// Define Connections to 74HC165
int states[8][8]; 

void blackout() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      states[i][j] = '0'; // Neutral (off) state
    }
  }
}


// PL pin 1
int load = 7;
// CE pin 15
int clockEnablePin = 4;
// Q7 pin 7
int dataIn = 5;
int dataTwo = 8;
int clockTwo = 3;

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
  blackout();
}

int rowState[8] = {2,2,2,2,2,2,2,2};
int colState[8] = {2,2,2,2,2,2,2,2};




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
    digitalWrite(clockIn,HIGH);
    delay(5);
    rowState[i] = digitalRead(dataIn);
    //Serial.print(digitalRead(dataIn));
    digitalWrite(clockIn,LOW);
  }
  //Serial.print("\n");
  digitalWrite(load, LOW);
  delayMicroseconds(5);
  digitalWrite(load, HIGH);
  delayMicroseconds(5);

  for(int i = 0; i < 8; i++){
    digitalWrite(clockIn,HIGH);
    delay(5);
    colState[i] = digitalRead(dataTwo);
    //Serial.print(digitalRead(dataTwo));
    digitalWrite(clockIn,LOW);
  }
  //Serial.println(colState);
  digitalWrite(clockEnablePin,HIGH);
  /*
  for (int i = 0; i <8 ; i++){
    for (int j = 0; j < 8; j++){
      //Serial.print
      if (rowState[i] == 1 == colState[j]){
        states[i][j] = 1;
      }
      else{
        states[i][j] = 0;
      }
    }
  }
  */
  int foundRow = 9;
  int foundCol = 9;
  for (int i = 0; i < 8; i++){
    if (rowState[i] == 1){
      foundRow = i;
    }
    if (colState[i] == 1){
      foundCol = i;
    }
  }
  delay(200);
  if (foundRow != 9 && foundCol != 9){
      states[foundRow][foundCol] = 1;
  }

  /*
  Serial.print(foundRow);
  Serial.print(foundCol);
  Serial.println();
  */
  

// outputting to the serial, so I can test visualizing.
for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Serial.print(states[i][j]);
        if (j < 7) Serial.print(", ");
        //states[foundRow][foundCol] = 0;
      }
      Serial.println();
    }
    Serial.println("---");

  // Print to serial monitor
  delay(200);
  
  delay(200);
  blackout();
}

