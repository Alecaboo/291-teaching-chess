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

char pieceArray[3][3] {{'N','N','N'},{'N','N','N'},{'N','P','N'}};

int stateArray[3][3];


void setup() {
  // I'm using pullup because, in the testing, it made things more reliable. Arguably, we should also be using a capacitor, but I really kind of don't want to?
  // like it would probably help, and I can pretty easily swap it over to input if it doesn't work.
  

for (int curRow = 0; curRow < 4; curRow++){
  for (int curCol = 0; curCol < 4; curCol++){
    pinMode(magArray[curRow][curCol],INPUT_PULLUP);
    stateArray[curRow][curCol] = digitalRead(magArray[curRow][curCol]);
    pinMode(ledArray[curRow,curCol],OUTPUT);
  }
}

}

char curPiece = 'P';

bool inBounds(int num){ // checking if a given location is in bounds.
  return (num > -1 && num < 4);
}

void light(int row, int col){ // this function does not need to exist. I'm just really lazy.
  digitalWrite(ledArray[row][col],HIGH);
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
    }

}



bool changed = false; 

void loop() {
   int oldState[3][3]; // toDo: make this actually copy the array (it has to be element by element)

  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      oldState[i][j] = stateArray[i][j];
    }
  }


  for (int curRow = 0; curRow < 4; curRow ++){
    if (changed){
      break;
    }
    for (int curCol = 0; curCol < 4; curCol ++){
      stateArray[curRow][curCol] = digitalRead(magArray[curRow][curCol]);
      int change = stateArray[curRow][curCol] - oldState[curRow][curCol];
      int place[2] = {curRow,curCol};
      if (change != 0){
        changed = true;
      }
      if ( change == 1){ // piece removed
        figureMoves(place); // if a piece is removed, call the lightboard function, because I don't want to nest all that in here
        changed = true;
      }
      else if (change == -1){ // piece placed
        for( int ledRow = 0; ledRow < 4; ledRow++){ // if we put a piece down, knock all the lights out.
          for (int ledCol = 0; ledCol < 4; ledCol++){
            digitalWrite(ledArray[ledRow][ledCol],LOW);
          }
        }
      }
    }
  }
  changed = false;
  }
