

// I caved and used a library. God bless FastLED. 
#include <FastLED.h>

const int NUM_LEDS = 300;
CRGB bigLED[NUM_LEDS];
const int ledPin = 6;
// this is an implementation inspired by looking up other people's way of coding chess, and I think I accidentally solved a leetcode problem on the way?
// bit of fascinating reading in the field of coding chess, if anyone ever wants to research
const int kingMoves[8][2] = {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {0,-1}, {-1,1}};
const int knightMoves[8][2] = {{2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {-1,2}, {1,-2}, {-1,-2}};
const int pawnMoves[3][2] = {{1,0}, {1,1}, {1,-1}};

bool inBounds(int num){
  return (num < 8);
}

class Piece{
  public:
  bool hasMoved;
  char color;
  char type;
  Piece(char colorIn, char typeIn){
    hasMoved = false;
    color = colorIn;
    type = typeIn;
  }
  Piece(){ // default case constructor because Square was throwing an absolute FIT that this didn't exist. So the default is a Void piece on the Neutral team.
    color = 'N'; // I am happy to report I have successfully introduced a third team to Chess. 
    type = 'V';
  }
};

class Square
{
  public:
    int magAdd;
    int leds[4]; 
    // current plan is that A1 is going to be lights 0-3, with each square taking four LEDs, and we're going to go left to right
    int row;
    int col;
    Piece piece;
    Square(int magIn, int ledsIn[4],Piece pieceIn, int inRow, int inCol ){
      magAdd = magIn;
      row = inRow;
      col = inCol;
      for (int i = 0; i < 5; i++){
        leds[i] = ledsIn[i];
      }
      piece = pieceIn;
    }
    Square(){ // making a default constructor just because piece was so upset when it didn't exist
      Piece new;
      piece = new;
      magAdd = 0;
      for (int i = 0; i < 5; i++){
        leds[i] = i;
      }

    }
    void light(int red, int green, int blue){
      CRGB color = CHSV(red,green,blue);
      for (int i = 0; i < 5; i++){
        
        bigLED[leds[i]] = color;

      }
    }
    int magnet(){
      // blatant code magic, I don't know how reading is going to work yet.
    }
    // I've gone mad with method-based power, and I'm writing this code just for me, so nobody can stop me. 
    void homeLight(){
      light(0,0,255);
    }
    // Lights up the given square, given a piece as input - if they don't match, red, else, green.
    void otherLight(Piece inPiece){
      if (piece.color == 'N'){
        light(0,255,0);
      }
      else if (piece.color == inPiece.color) {
        // do nothing, actually. my bad.
      }
      else{
        light(255,0,0);
      }
    }
    
    void figureMoves(){
      /* pseudocode implementation so I can figure out what the hell is happening
        I think I just do the big switch/case tree here again, so...
        check the piece in the square, and depending on what it is:
          - Pawns move one space forward, and check the diagonals to attack
          - Knights have their silly little flower shape, which some googling has given me the idea to make a list that I loop over! That makes sense.
          - Rooks move along a "vector" until they hit another piece, and depending on that piece, they either kill it or not
            - Castling is going to be fucked up.
          - Bishops move along a "vector" until they hit another piece, and depending on that piece, they either kill it or not
          - Kings move up to one space away, which we're going to do as a loop similar to knights
          - Queens are literally bishops + rooks. Same implementation as before.
      */
      homelight();
      switch(piece.type){
        case 'K':
          for (int i = 0; i < 8; i++){
            int newRow = row +  kingMoves[i][0];
            int newCol  = col + kingMoves[i][1];
            if (!(inBounds(newRow) && inBounds(newCol) ){
              continue;
            }
            else{
              board[rowChange + row][colChange + col].otherlight(piece);
            }
            
          }
          break;
        case 'N':
         for (int i = 0; i < 8; i++){
            int newRow = row +  knightMoves[i][0];
            int newCol  = col + knightMoves[i][1];
            if (!(inBounds(newRow) && inBounds(newCol) ){
              continue;
            }
            else{
              board[rowChange + row][colChange + col].otherlight(piece);
            }
            
          }
         
          break;
        case 'P':
          // pawn movement

          if (piece.color == 'B'){
            // somehow invert the entire array 
          }
          for (int i = 0; i < 3; i++){
            int newRow = row + pawnMoves[i][0];
            int newCol = col + pawnMoves[i][1];
            if (inBounds(newRow) && inBounds(newCol)){
              if (i == 0){
                if (board[newRow][newCol].piece == 'V'){
                  board[newRow][newCol].otherLight(piece);
                }
              }
              else{
                if (board[newRow][newCol].piece != 'V'){
                  board[newRow][newCol].otherLight(piece);
                }
              }
            }
          }
          break;
        case 'R':

          break;
        case 'B':
          break;
        case 'Q':
          break;
        
      }
    
    }
};

Square board[8][8];
void blackout(){ // fairly self explanatory, but this loops over the entire strip and sets everything to off (black)
  for (int i = 0; i <300; i++){
    bigLED[i] = CRGB::Black;
  }
}

void setup() {
  FastLED.addLeds<WS2812B, ledPin, GRB>(bigLED, 300); // this is adding all the LEDs on the strip into existing digitally.
  // FILL THE BOARD IN SOMEHOW.

}

void loop() {
  blackout();
  FastLED.show(); // this updates the board
}
