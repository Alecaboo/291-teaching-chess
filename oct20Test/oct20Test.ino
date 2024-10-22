// time to declare all of our pins! this is going off the tinkercad diagram at (https://www.tinkercad.com/things/2hayu8VoFnV-3x3-chess-grid?sharecode=CSrqqlocQqnvlNf2s-Q7EwOXBIaHyHPHCmI_gLgrOvU)

int magOne = 8;
int magTwo = 9;
int magThree = 10;

int magFour = 5;
int magFive = 6;
int magSix = 7;

int magSeven = 2;
int magEight = 3;
int magNine = 4;




int magArray[3][3] = {{magOne,magTwo,magThree}, {magFour,magFive,magSix}, {magSeven,magEight,magNine}};

// LEDs. That's crazy.
//A0 = 14, just as a little note here for myself
int ledOne = 16;
int ledTwo = 15;
int ledThree = 14;


int ledFour = 19;
int ledFive = 18;
int ledSix = 17;

int ledSeven = 11;
int ledEight = 12;
int ledNine = 13;


int ledArray[3][3] = {{ledOne,ledTwo,ledThree}, {ledFour,ledFive,ledSix}, {ledSeven,ledEight,ledNine}};
int ledStateArray[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

char pieceArray[3][3] {{'V','V','V'},{'V','V','V'},{'V','R','V'}}; // blank piece array


int stateArray[3][3];




bool inBounds(int num){ // checking if a given location is in bounds.
  return (num > -1 && num < 3);
}

void light(int row, int col){ // this function does not need to exist. I'm just really lazy.
  digitalWrite(ledArray[row][col],HIGH);
  ledStateArray[row][col]= 1;
}

void blackout(){
  for (int row = 0; row < 3; row++){
    for (int col = 0; col < 3; col++){
      digitalWrite(ledArray[row][col],LOW);
      ledStateArray[row][col] = 0;
    }
  }
}

void figureMoves(int loc[2]){
  // plan here is based on the piece type and location fed in, update the light array. We'll see how that goes.

  light(loc[0],loc[1]); // lighting up the home square
  char pieceType = pieceArray[loc[0]][loc[1]];
  switch(pieceType) { // I originally did this using just a bunch of if statements, and then I started thinking for two seconds and switched it up (ba dum tiss)
    case 'P':
      
      if (pieceArray[loc[0]-1][loc[1]] == 'V' && inBounds(loc[0]-1)){ // if the space in front is empty, you can go forward 
        light(loc[0]-1,loc[1]); 
      }
        
      
      // these are the attacking ones - not mutually exclusive.
      if (pieceArray[loc[0]-1][loc[1]+1]!= 'V' && inBounds(loc[0]-1) && inBounds(loc[1]+1) ){
        light(loc[0]-1,loc[1]+1);
      }
      if (pieceArray[loc[0]-1][loc[1]-1] != 'V' && inBounds(loc[0]-1) && inBounds(loc[1]-1)){
        light(loc[0]-1,loc[1]-1);
      }
      break;
    case 'N': // knight, they're N in chess notation, but just in case I forget.
      //four central cases: +2 in each cardinal direction
      // this is very far from elegant but by golly it should work. 
      if (inBounds(loc[0]+2)){
        if (inBounds(loc[1]+1)){
          light(loc[0]+2,loc[1]+1);
        }
        if (inBounds(loc[1]-1)){
          light(loc[0]+2,loc[1]-1);
        }
      }


      if (inBounds(loc[0]-2)){
        if (inBounds(loc[1]+1)){
          light(loc[0]-2,loc[1]+1);
        }
        if (inBounds(loc[1]-1)){
          light(loc[0]-2,loc[1]-1);
        }

      }

      if (inBounds(loc[1]+2)){
        if (inBounds(loc[0]+1)){
          light(loc[0]+1,loc[1]+2);
        }
        if (inBounds(loc[0]-1)){
          light(loc[0]-1,loc[1]+2);
        }
      }


      if (inBounds(loc[1]-2)){
        if (inBounds(loc[0]+1)){
          light(loc[0]+1,loc[1]-2);
        }
        if (inBounds(loc[0]-1)){
          light(loc[0]-1,loc[1]-2);
        }
      }
      


      break;

    case 'R':
      for (int i = 0; i < 3; i++){
        light(loc[0],i);
        light(i,loc[1]);
      }

      break;
    case 'B':
      for (int i = 1; i < 3; i++){
        if (inBounds(loc[0]+i)){
          if (inBounds(loc[1]+i)){
            light(loc[0]+i,loc[1]+i);
          }
        }
        if (inBounds(loc[0]-i)){
          if (inBounds(loc[1]+i)){
            light(loc[0]-i,loc[1]+i);
          }
        }
        if (inBounds(loc[0]+i)){
          if (inBounds(loc[1]-i)){
            light(loc[0]+i,loc[1]-i);
          }
        }
        if (inBounds(loc[0]-i)){
          if (inBounds(loc[1]-i)){
            light(loc[0]-i,loc[1]-i);
          }
        }




      }


      break;
    case 'Q':
      // we're essentially acting as if we're a rook, figuring out the moves, then as if a bishop and figured out the moves, then going back and putting the queen hat back on.
      pieceArray[loc[0]][loc[1]] = 'R';
      figureMoves(loc);
      pieceArray[loc[0]][loc[1]] = 'B';
      figureMoves(loc);
      pieceArray[loc[0]][loc[1]] = 'Q';

      
      
      break;
    case 'K':
      if (inBounds(loc[0]+1)){
          if (inBounds(loc[1]+1)){
            light(loc[0]+1,loc[1]+1);
          }
        }
      if (inBounds(loc[0]+1)){
          if (inBounds(loc[1]+0)){
            light(loc[0]+1,loc[1]+0);
          }
        }
      if (inBounds(loc[0]+1)){
          if (inBounds(loc[1]-1)){
            light(loc[0]+1,loc[1]-1);
          }
        }
      if (inBounds(loc[0]+0)){
          if (inBounds(loc[1]-1)){
            light(loc[0]+0,loc[1]-1);
          }
        }
      if (inBounds(loc[0]-1)){
          if (inBounds(loc[1]-1)){
            light(loc[0]-1,loc[1]-1);
          }
        }
      if (inBounds(loc[0]-1)){
          if (inBounds(loc[1]+0)){
            light(loc[0]-1,loc[1]);
          }
        }
      if (inBounds(loc[0]-1)){
          if (inBounds(loc[1]+1)){
            light(loc[0]-1,loc[1]+1);
          }
        }
      if (inBounds(loc[0])){
          if (inBounds(loc[1]+1)){
            light(loc[0],loc[1]+1);
          }
        }

      break;
    case 'V':
      digitalWrite(ledArray[loc[0]][loc[1]],LOW);
      ledStateArray[loc[0]][loc[1]] = 0;
      return;
    }

}



void setup() {
  // I'm using pullup because, in the testing, it made things more reliable. Arguably, we should also be using a capacitor, but I really kind of don't want to?
  // like it would probably help, and I can pretty easily swap it over to input if it doesn't work.
Serial.begin(9600);

for (int curRow = 0; curRow < 3; curRow++){
  for (int curCol = 0; curCol < 3; curCol++){
    pinMode(magArray[curRow][curCol],INPUT_PULLUP);
    int state = digitalRead(magArray[curRow][curCol]);
    stateArray[curRow][curCol] = state;
    
    pinMode(ledArray[curRow][curCol],OUTPUT);
    if (pieceArray[curRow][curCol] != 'V'){
      light(curRow,curCol);
    }
  }

}


// I need to do this with user input, but for now testing because I'm traumatized, I'm just going to manually set these. Womp womp.
  
}


char curPiece = 'V';

void loop() {
  for (int curRow = 0; curRow < 3; curRow++){
    for (int curCol = 0; curCol < 3; curCol++){
      int swit = digitalRead(magArray[curRow][curCol]) - stateArray[curRow][curCol];
      if (swit != 0 && ledStateArray[curRow][curCol] == 1){
        blackout();
        int locChoice[2] = {curRow, curCol};
        if (pieceArray[curRow][curCol] != 'V' && curPiece == 'V'){
          curPiece = pieceArray[curRow][curCol];
          
        }

        else if (pieceArray[curRow][curCol] == 'V' && curPiece != 'V'){
          pieceArray[curRow][curCol] = curPiece;
          blackout();
          light(curRow,curCol);
          
          
        }
        figureMoves(locChoice);
        /*
        if (swit == 1){ // magnet placed on location

        }
        else if (swit == -1){ // magnet removed from location

        }
        */
      
      }
    }
  }




}
