// time to declare all of our pins! this is going off the tinkercad diagram at (https://www.tinkercad.com/things/2hayu8VoFnV-3x3-chess-grid?sharecode=CSrqqlocQqnvlNf2s-Q7EwOXBIaHyHPHCmI_gLgrOvU)


int magOne = 4;
int magTwo = 7;
int magThree = 10;

int magFour = 3;
int magFive = 6;
int magSix = 9;

int magSeven = 2;
int magEight = 5;
int magNine = 8;


int magArray[3][3] = {{magOne,magTwo,magThree}, {magFour,magFive,magSix}, {magSeven,magEight,magNine}};

// LEDs. That's crazy.
//A0 = 14, just as a little note here for myself
int ledOne = 13;
int ledTwo = 17;
int ledThree = 14;

int ledFour = 12;
int ledFive = 18;
int ledSix = 15;

int ledSeven = 11;
int ledEight = 19;
int ledNine = 16;

int ledArray[3][3] = {{ledOne,ledTwo,ledThree}, {ledFour,ledFive,ledSix}, {ledSeven,ledEight,ledNine}};

char pieceArray[3][3] {{"N","N","N"},{"N","N","N"},{"N","P","N"}};


void setup() {
  // I'm using pullup because, in the testing, it made things more reliable. Arguably, we should also be using a capacitor, but I really kind of don't want to?
  // like it would probably help, and I can pretty easily swap it over to input if it doesn't work.
  int stateArray[3][3];
  for (int curRow : magArray){
    for (int curCol: curRow){
      pinmode(magArray[curRow][curCol],INPUT_PULLUP);
      stateArray[curRow][curCol] = digitalRead(magArray[curRow][curCol]);
    }
    
  }

 for (int curRow : ledArray){
    for (int curCol: curRow){
      pinmode(ledArray[curRow,curCol],OUTPUT);
    }
    
  }

 


  // alright, now there's initial board state shenanigans? I think my first goal should just be assuming a standard setup. 
  // honestly if I can get a pawn to work that's a success in my book. Let's code a pawn.




}



char curPiece = "P";

void figureMoves(char pieceType,int loc[2]){
  // plan here is based on the piece type and location fed in, update the light array. We'll see how that goes.
  int retLoc[2] = [0,0];
  if (pieceType == "P"){
    light(loc[0]-1,loc[1]); // that's normal movement
    // we're uh, playing pacifist chess right now. We're not gonna worry about attacking.
  }
  
  light(loc[0],loc[1]);

}

void light(int row, int col){
  digitalWrite(ledArray[row][col],HIGH);
}

void loop() {
  int oldState[3][3] = state; // toDo: make this actually copy the array (it has to be element by element)
  for (int curRow: state){
    for (int curCol : curRow){
      state[curRow][curCol] = digitalRead(magArray[curRow][curCol]);
      int change = state[curRow][curCol] - oldState[curRow][curCol];
      int place[2] = {curRow,curCol};
      if ( change == -1){ // piece removed
        lightBoard(pieceArray[curRow][curCol],place);
      }
      else if ( change == 1){ // piece placed
        for( ledRow : ledArray){
          for (ledCol: ledRow){
            digitalWrite(ledArray[ledRow][ledCol],LOW);
          }
        }
      }
    }
  }
  changed: 

  }

  

}
