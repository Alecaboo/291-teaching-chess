// time to declare all of our pins! this is going off the tinkercad diagram at (https://www.tinkercad.com/things/2hayu8VoFnV-3x3-chess-grid?sharecode=CSrqqlocQqnvlNf2s-Q7EwOXBIaHyHPHCmI_gLgrOvU)

int magOne = 2;
int magTwo = 3;
int magThree = 4;

int magFour = 5;
int magFive = 6;
int magSix = 7;

int magSeven = 8;
int magEight = 9;
int magNine = 10;

int magArray[3][3] = {{magOne,magTwo,magThree}, {magFour,magFive,magSix}, {magSeven,magEight,magNine}};

// LEDs. That's crazy.
//A0 = 14, just as a little note here for myself
int ledOne = 16;
int ledTwo = 15;
int ledThree = 14;

int ledFour = 11;
int ledFive = 12;
int ledSix = 13;

int ledSeven = 19;
int ledEight = 18;
int ledNine = 17;

int ledArray[3][3] = {{ledOne,ledTwo,ledThree}, {ledFour,ledFive,ledSix}, {ledSeven,ledEight,ledNine}};

void light(int row, int col){ // this function does not need to exist. I'm just really lazy.
  digitalWrite(ledArray[row][col],HIGH);
}

void blackout(){
  for (int row = 0; row < 3; row++){
    for (int col = 0; col < 3; col++){
      digitalWrite(ledArray[row][col],LOW);
    }
  }
}

void setup() {
  for (int curRow = 0; curRow < 3; curRow++){
  for (int curCol = 0; curCol < 3; curCol++){
    pinMode(magArray[curRow][curCol],INPUT_PULLUP);
    //stateArray[curRow][curCol] = digitalRead(magArray[curRow][curCol]);
    pinMode(ledArray[curRow][curCol],OUTPUT);
  }

}
}

int magState;
void loop() {
  for (int curRow = 0; curRow < 3; curRow++){
    for(int curCol = 0; curCol < 3; curCol ++){
      
      light(curRow,curCol);
      delay(250);
      //digitalWrite(ledArray[curRow][curCol],LOW);
      
      /*
      if (digitalRead(magArray[curRow][curCol])== 0){
        light(curRow,curCol);
      }
      else{
        digitalWrite(ledArray[curRow][curCol],LOW);
      }
      */
    }
  }
  blackout();


}
