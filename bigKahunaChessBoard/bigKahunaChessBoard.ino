

// I caved and used a library. God bless FastLED. 
/*
#include <FastLED.h>


CRGB bigLED[NUM_LEDS];
const int ledPin = 6;
*/
char bigLED[8][8];
// this is an implementation inspired by looking up other people's way of coding chess, and I think I accidentally solved a leetcode problem on the way?
// bit of fascinating reading in the field of coding chess, if anyone ever wants to research
const int kingMoves[9][2] = {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {0,-1}, {-1,1},{-1,0}};
const int knightMoves[8][2] = {{2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {-1,2}, {1,-2}, {-1,-2}};
const int pawnMoves[3][2] = {{1,0}, {1,1}, {1,-1}};
class Piece;
class Square;


bool inBounds(int num){
  return (num < 8 && num > 0);
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
    // current plan is that A1 is going to be lights 0-3, with each square taking four LEDs, and we're going to go left to right
    int row;
    int col;
    Piece piece;
    Square(Piece pieceIn, int inRow, int inCol ){
      row = inRow;
      col = inCol;
      piece = pieceIn;
    }
    Square(){ // making a default constructor just because piece was so upset when it didn't exist
      Piece fresh;
      piece = fresh;
      row = 0;
      col = 0;

    }
    void light(int red, int green, int blue){
      char color = figureColor(red,green,blue);
      for (int i = 0; i < 5; i++){
        
        bigLED[row][col] = color;

      }
    }
    int magnet(){
      // blatant code magic, I don't know how reading is going to work yet.
    }
    // I've gone mad with method-based power, and I'm writing this code just for me, so nobody can stop me. 
    void homeLight(){
      light(0,255,0);
    }
    char figureColor(int red, int green, int blue){
      if (green = 255){
        return 'G';
      }
      
      else if (red = 255){
        return 'R';
      }
      
      else if (blue = 255){
        return 'B';
      }
      else{
        return 'P';
      }
    }
    // Lights up the given square, given a piece as input - if they don't match, red, else, green.
    void otherLight(Piece inPiece){
      if (piece.color != inPiece.color){
        light(255,0,0);
      }
      else if (piece.color == inPiece.color) {
        // do nothing, actually. my bad.
      }
      else{
        light(255,0,0);
      }
    }
    
    
};

Square board[8][8];
void setupChessBoard() {
    // Define the initial piece placements
    char backRow[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}; // Back row pieces
    char pawnRow[8] = {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}; // Pawns
    
    // Initialize board with standard setup
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == 0) {
                // Black back row
                board[i][j] = Square( Piece('B', backRow[j]), i, j);
            } else if (i == 1) {
                // Black pawns
                board[i][j] = Square( Piece('B', pawnRow[j]), i, j);
            } else if (i == 6) {
                // White pawns
                board[i][j] = Square(Piece('W', pawnRow[j]), i, j);
            } else if (i == 7) {
                // White back row
                board[i][j] = Square(Piece('W', backRow[j]), i, j);
            } else {
                // Empty squares
                board[i][j] = Square();
                board[i][j].row = i;
                board[i][j].col = j;
            }
        }
    }
}
void figureMoves(Piece inPiece, Square inSquare){ // this is probably 

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
      inSquare.homeLight();
      switch(inPiece.type){
        case 'K':
          for (int i = 0; i < 9; i++){
            int newRow = inSquare.row +  kingMoves[i][0];
            int newCol  = inSquare.col + kingMoves[i][1];
            if (!(inBounds(newRow) && inBounds(newCol) )){
              continue;
            }
            else{
              board[newRow][newCol].otherLight(inPiece);
            }
            
          }
          break;
        case 'N':
         for (int i = 0; i < 8; i++){
            int newRow = inSquare.row +  knightMoves[i][0];
            int newCol  = inSquare.col + knightMoves[i][1];
            if (!(inBounds(newRow) && inBounds(newCol) )){
              continue;
            }
            else{
              board[newRow][newCol].otherLight(inPiece);
            }
            
          }
         
          break;
        case 'P':
          // pawn movement

          if (inSquare.piece.color == 'B'){
            // somehow invert the entire array 
          }
          for (int i = 0; i < 3; i++){
            int newRow = inSquare.row + pawnMoves[i][0];
            int newCol = inSquare.col + pawnMoves[i][1];
            if (inBounds(newRow) && inBounds(newCol)){
              if (i == 0){
                if (board[newRow][newCol].piece.type == 'V'){
                  board[newRow][newCol].otherLight(inPiece);
                }
              }
              else{
                if (board[newRow][newCol].piece.type != 'V'){
                  board[newRow][newCol].otherLight(inPiece);
                }
              }
            }
          }
          break;
        case 'R':
          // I'm going to do this as... a series of while loops? I guess?
          int rowShift = 0;
          int colShift = 0;
          while (inBounds(inSquare.row+rowShift)){
            board[rowShift + inSquare.row][inSquare.col].otherLight(inPiece);
            if (board[rowShift+inSquare.row][inSquare.col].piece.type != 'V'){
              break;
            }
            rowShift ++;
          }
          rowShift = 0;
          while (inBounds(inSquare.row-rowShift)){
            board[rowShift - inSquare.row][inSquare.col].otherLight(inPiece);
            if (board[rowShift-inSquare.row][inSquare.col].piece.type != 'V'){
              break;
            }
            rowShift ++;
          }
          while (inBounds(inSquare.col+colShift)){
            board[inSquare.row][inSquare.col+colShift].otherLight(inPiece);
            if (board[inSquare.row][inSquare.col+colShift].piece.type != 'V'){
              break;
            }
          }
          colShift = 0;
          while (inBounds(inSquare.col-colShift)){
            board[inSquare.row][inSquare.col-colShift].otherLight(inPiece);
            if (board[inSquare.row][inSquare.col-colShift].piece.type != 'V'){
              break;
            }
          }
          break;
        case 'B':
          rowShift = 0;
          colShift = 0;
          while (inBounds(inSquare.row+rowShift) && inBounds(inSquare.col+colShift)){
            board[rowShift + inSquare.row][inSquare.col+colShift].otherLight(inPiece);
            if (board[rowShift+inSquare.row][inSquare.col+colShift].piece.type != 'V'){
              break;
            }
            rowShift ++;
            colShift ++;
          }
          rowShift = 0;
          colShift = 0;
          while (inBounds(inSquare.row-rowShift) && inBounds(inSquare.col-colShift)){
            board[rowShift - inSquare.row][inSquare.col-colShift].otherLight(inPiece);
            if (board[rowShift-inSquare.row][inSquare.col-colShift].piece.type != 'V'){
              break;
            }
            rowShift ++;
            colShift ++;
          }
          rowShift = 0;
          colShift = 0;
          while (inBounds(inSquare.row+rowShift) && inBounds(inSquare.col-colShift)){
            board[rowShift + inSquare.row][inSquare.col-colShift].otherLight(inPiece);
            if (board[rowShift+inSquare.row][inSquare.col-colShift].piece.type != 'V'){
              break;
            }
            rowShift ++;
            colShift ++;
          }
          rowShift = 0;
          colShift = 0;
          while (inBounds(inSquare.row-rowShift) && inBounds(inSquare.col+colShift)){
            board[rowShift - inSquare.row][inSquare.col+colShift].otherLight(inPiece);
            if (board[rowShift-inSquare.row][inSquare.col+colShift].piece.type != 'V'){
              break;
            }
            rowShift ++;
            colShift ++;
          }
          // wow that was kinda gross
          break;
        case 'Q':
          Piece dummyBishop(inPiece.color,'B');
          Piece dummyRook(inPiece.color,'R');
          figureMoves(dummyBishop,inSquare);
          figureMoves(dummyRook,inSquare);
          break;
        
      }
    
}

// alright need to rewrite all of figuremoves

void blackout(){ // fairly self explanatory, but this loops over the entire strip and sets everything to off (black)
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      bigLED[i][j] = 'N';
    }
  }
}

int magOldArray[8][8];
void setup() {
  //FastLED.addLeds<WS2812B, ledPin, GRB>(bigLED, 300); // this is adding all the LEDs on the strip into existing digitally.
  // FILL THE BOARD IN SOMEHOW.
  Serial.begin(9600);

  blackout();
  for (int i = 0; i < 8; i++){
  for (int j = 0; j < 8; j++){
    Piece dummyPiece();
    magOldArray[i][j] = board[i][j].magnet();
  }

}

}







//char updateArray[8][8];

void loop() {
  Piece dummyPiece('W','K');

  figureMoves(board[1][0].piece,board[1][0]);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Serial.print(bigLED[i][j]);
      if (j < 8 - 1) Serial.print(","); // Add comma between values
    }
    Serial.println(); // Newline at the end of each row
  }
  Serial.println("---"); // Separator for arrays
  delay(500);


  



  /*
  blackout();
  for (int row = 0; row < 8; row++){
    for (int col = 0; col < 8; col++){
      int curState = board[row][col].magnet();
      if( curState - magOldArray[row][col] == -1){
        Square cur = board[row][col];
        figureMoves(cur.piece,cur);
      }
      else if (curState - magOldArray[row][col]== 1){
        blackout();
      }
      magOldArray[row][col] = curState;
    }
  }
  */

}
