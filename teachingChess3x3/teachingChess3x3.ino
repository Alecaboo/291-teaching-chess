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
int ledOne = 11;
int ledTwo = 12;
int ledThree = 13;
int ledFour = 14;
int ledFive = 15;
int ledSix = 16;
int ledSeven = 17;
int ledEight = 18;
int ledNine = 19;
int ledArray[3][3] = {{ledOne,ledTwo,ledThree}, {ledFour,ledFive,ledSix}, {ledSeven,ledEight,ledNine}};


void setup() {
  // I'm using pullup because, in the testing, it made things more reliable. Arguably, we should also be using a capacitor, but I really kind of don't want to?
  // like it would probably help, and I can pretty easily swap it over to input if it doesn't work.
  for (int curRow : magArray){
    for (int curCol: curRow){
      pinmode(magArray[curRow,curCol],INPUT_PULLUP);
    }
    
  }

 for (int curRow : ledArray){
    for (int curCol: curRow){
      pinmode(ledArray[curRow,curCol],OUTPUT);
    }
    
  }


  // alright, now there's initial board state shenanigans? I think my first goal should just be assuming a standard setup. 
  // honestly if I can get a knight to work that's a success in my book. Let's code a knight.




}

char curPiece = "K";

void lightBoard(char pieceType,int loc){
  // plan here is based on the piece type and location fed in, update the light array. We'll see how that goes.
}

void loop() {


  }

  

}
