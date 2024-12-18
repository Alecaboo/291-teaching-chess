

char bigLED[8][8]; // Represents the LED state as a 2D array

// Moves for various pieces
const int kingMoves[9][2] = {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {0,-1}, {-1,1},{-1,0}};
const int knightMoves[8][2] = {{2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {-1,2}, {1,-2}, {-1,-2}};
const int pawnMoves[3][2] = {{1,0}, {1,1}, {1,-1}};
const char pieceTypes[6] = {'P','B','R','Q','N','K'};
// All the pins - straight ripped from the test sketch.
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



bool inBounds(int num) {
  return num >= 0 && num < 8;
}

class Piece {
public:
  bool hasMoved;
  char color; // 'W', 'B', or 'N' (neutral)
  char type;  // 'P', 'R', 'N', 'B', 'Q', 'K', or 'V' (void)

  Piece(char colorIn, char typeIn) : hasMoved(false), color(colorIn), type(typeIn) {}

  // Default constructor
  Piece() : hasMoved(false), color('N'), type('V') {}
};
Piece dummyPiece('N','V');

class Square {

public:
  int row, col;
  Piece piece;

  // Constructor
  Square(Piece pieceIn, int inRow, int inCol)
      : row(inRow), col(inCol), piece(pieceIn) {}

  // Default constructor
  Square() : row(0), col(0), piece() {}

  // Light up the square with a given color
  void light(char color) {
    bigLED[row][col] = color;
  }

  // Light the square with "other" logic
  void otherLight(Piece inPiece) {
    if (piece.color == 'N'){
      light('B');
    }
    else if (piece.color != inPiece.color) {
      light('R'); // Red for opponent
    }
    else{
      light('P');
    }
  }
};

// The chess board
Square board[8][8];

// Function prototypes
void setupChessBoard();
void blackout();
void figureMoves(Piece inPiece, Square inSquare);

void setupChessBoard() {
  char backRow[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
  char pawnRow[8] = {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'};

  // Initialize the board with pieces
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (i == 0) {
        // Black back row
        board[i][j] = Square(Piece('B', backRow[j]), i, j);
      } else if (i == 1) {
        // Black pawns
        board[i][j] = Square(Piece('B', pawnRow[j]), i, j);
      } else if (i == 6) {
        // White pawns
        board[i][j] = Square(Piece('W', pawnRow[j]), i, j);
      } else if (i == 7) {
        // White back row
        board[i][j] = Square(Piece('W', backRow[j]), i, j);
      } else {
        // Empty square
        board[i][j] = Square(Piece('N','V'),i,j);
      }
    }
  }
}

void blackout() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      bigLED[i][j] = 'N'; // Neutral (off) state
    }
  }
}

void figureMoves(Piece inPiece, Square inSquare) {
  inSquare.light('G'); // Highlight current square
  if (inPiece.type == 'P'){
    //Serial.println("I'm in pawn, btdubs");
    int direction = (inPiece.color == 'B') ? 1 : -1; // Direction: +1 for black, -1 for white
    for (int i = 0; i < 3; i++) {
      int newRow = inSquare.row + direction * pawnMoves[i][0];
      int newCol = inSquare.col + pawnMoves[i][1]; // Column does not depend on color
      if (inBounds(newRow) && inBounds(newCol)) {
        if (i == 0) { // Forward move
          if (board[newRow][newCol].piece.type == 'V') {
            board[newRow][newCol].otherLight(inPiece);
            if (!inPiece.hasMoved) { // Check for double-move on first move
              int doubleRow = newRow + direction; // Two squares ahead
              if (inBounds(doubleRow) && board[doubleRow][newCol].piece.type == 'V') {
                board[doubleRow][newCol].otherLight(inPiece);
              }
            }
          }
        } else { // Diagonal capture
          if (board[newRow][newCol].piece.type != 'V' && board[newRow][newCol].piece.color != inPiece.color) {
            board[newRow][newCol].otherLight(inPiece);
          }
        }
      }
    }
  }
  // Handle moves based on the piece type
  switch (inPiece.type) {
    case 'K': // King
      for (int i = 0; i < 9; i++) {
        int newRow = inSquare.row + kingMoves[i][0];
        int newCol = inSquare.col + kingMoves[i][1];
        if (inBounds(newRow) && inBounds(newCol)) {
          board[newRow][newCol].otherLight(inPiece);
        }
      }
      break;
    case 'N': // Knight
      for (int i = 0; i < 8; i++) {
        int newRow = inSquare.row + knightMoves[i][0];
        int newCol = inSquare.col + knightMoves[i][1];
        if (inBounds(newRow) && inBounds(newCol)) {
          board[newRow][newCol].otherLight(inPiece);
        }
      }
      break;
  case 'R': // Rook
    //Serial.println("Father, I made it into Rook");
    for (int direction = -1; direction <= 1; direction += 2) {
      // Vertical movement
      int rowShift = direction;
      while (true) {
        int newRow = inSquare.row + rowShift;
        int newCol = inSquare.col;
        if (!inBounds(newRow) || board[newRow][newCol].piece.type != 'V') {
          if (inBounds(newRow)) board[newRow][newCol].otherLight(inPiece); // Stop on capture
          break;
        }
        board[newRow][newCol].otherLight(inPiece);
        rowShift += direction;
      }

      // Horizontal movement
      int colShift = direction;
      while (true) {
        int newRow = inSquare.row;
        int newCol = inSquare.col + colShift;
        if (!inBounds(newCol) || board[newRow][newCol].piece.type != 'V') {
          if (inBounds(newCol)) board[newRow][newCol].otherLight(inPiece); // Stop on capture
          break;
        }
        board[newRow][newCol].otherLight(inPiece);
        colShift += direction;
      }
    }
    break;


  case 'B': // Bishop
    //Serial.println("Father, I made it into Bishop");
    for (int rowDir = -1; rowDir <= 1; rowDir += 2) {
      for (int colDir = -1; colDir <= 1; colDir += 2) {
        int rowShift = rowDir;
        int colShift = colDir;
        while (true) {
          int newRow = inSquare.row + rowShift;
          int newCol = inSquare.col + colShift;
          if (!inBounds(newRow) || !inBounds(newCol) || board[newRow][newCol].piece.type != 'V') {
            if (inBounds(newRow) && inBounds(newCol)) board[newRow][newCol].otherLight(inPiece); // Stop on capture
            break;
          }
          board[newRow][newCol].otherLight(inPiece);
          rowShift += rowDir;
          colShift += colDir;
        }
      }
    }
    break;


  case 'Q': // Queen (combines Rook and Bishop logic)
    Piece dummyBishop(inPiece.color, 'B');
    Piece dummyRook(inPiece.color, 'R');
    figureMoves(dummyBishop, inSquare); // Handle diagonal moves
    figureMoves(dummyRook, inSquare);  // Handle straight-line moves
    break;

  case 'P': // Pawn
    //Serial.println("I'm in pawn, btdubs");
    int direction = (inPiece.color == 'B') ? 1 : -1; // Direction: +1 for black, -1 for white
    for (int i = 0; i < 3; i++) {
      int newRow = inSquare.row + direction * pawnMoves[i][0];
      int newCol = inSquare.col + pawnMoves[i][1]; // Column does not depend on color
      if (inBounds(newRow) && inBounds(newCol)) {
        if (i == 0) { // Forward move
          if (board[newRow][newCol].piece.type == 'V') {
            board[newRow][newCol].otherLight(inPiece);
            if (!inPiece.hasMoved) { // Check for double-move on first move
              int doubleRow = newRow + direction; // Two squares ahead
              if (inBounds(doubleRow) && board[doubleRow][newCol].piece.type == 'V') {
                board[doubleRow][newCol].otherLight(inPiece);
              }
            }
          }
        } else { // Diagonal capture
          if (board[newRow][newCol].piece.type != 'V' && board[newRow][newCol].piece.color != inPiece.color) {
            board[newRow][newCol].otherLight(inPiece);
          }
        }
      }
    }
    break;
  }
}

int rowState[8] = {2,2,2,2,2,2,2,2};
int colState[8] = {2,2,2,2,2,2,2,2};


int states[8][8];
int oldStates[8][8];

void setup() {
  Serial.begin(9600);
  setupChessBoard();
  blackout();
  pinMode(load, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);
  pinMode(clockTwo,OUTPUT);
  pinMode(dataTwo,INPUT);

  // going to initialize the old state array here. I think? probably?

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

}


Piece pickedPiece;
int pickedRow;
int pickedCol;
/*
void loop() {

  for (int i = 0; i < 6; i++){
    Piece testPiece('W',pieceTypes[i]);
    board[4][4].piece = testPiece;
    figureMoves(testPiece,board[4][4]);
      for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Serial.print(bigLED[i][j]);
        if (j < 7) Serial.print(", ");
      }
      Serial.println();
    }
    Serial.println("---");
    delay(500);
    blackout();
    delay(2000);
  }


// example code to iterate over the whole board and check moves, which seems to work perfectly fine
/*
  Piece testPiece('B','Q');
  //board[row][col].piece = testPiece;
  for (int row = 0; row < 8; row++){
    for (int col = 0; col < 8; col++){
      figureMoves(board[row][col].piece,board[row][col]);
      for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Serial.print(bigLED[i][j]);
        if (j < 7) Serial.print(", ");
      }
      Serial.println();
    }
    Serial.println("---");
    delay(500);
    blackout();
    }
  }
  */
// the fun part.
/*
// this whole part is just *reading* the damn array.
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

  for (int i = 0; i < 8; i++){ // setting the current read to be what's actually happening
    for (int j = 0; j < 8; j++){
      if (rowState[i] == 1 == colState[j]){
        states[i][j] = 1;
      }
      else{
        states[i][j] = 0;
      }
    }
  }
  int changeRow;
  int changeCol;
  for (int row = 0; row < 8; row++){
    for (int col = 0; col < 8; col++){
      if (states[row][col] != oldStates[row][col]){
        changeRow = row;
        changeCol = col;
        break;
      }
    }
  }

  if (oldStates[changeRow][changeCol] - states[changeRow][changeCol] == 1){
    figureMoves(board[changeRow][changeCol].piece,board[changeRow][changeCol]);
    pickedPiece = board[changeRow][changeCol].piece;
    pickedRow = changeRow;
    pickedCol = changeCol;
  }
  else if (oldStates[changeRow][changeCol] - states[changeRow][changeCol] == -1){
    blackout();
    board[changeRow][changeCol].piece = pickedPiece;
    board[pickedRow][pickedCol].piece = dummyPiece;
  }


  for (int i = 0; i < 8; i++){ // populating the old state with whatever the changes were
    for(int j = 0; j < 8; j++){
      oldStates[i][j] = states[i][j];
    }
  }
  }
*/

void loop() {
  // Rotate through all chess piece types and display their moves
  for (int i = 0; i < 6; i++) {
    Piece testPiece('W', pieceTypes[i]);   // Create a piece of type i
    //Serial.println(testPiece.type);
    board[4][4].piece = testPiece;        // Place it at the center square
    figureMoves(testPiece, board[4][4]);  // Calculate and display its moves
    
    
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        Serial.print(bigLED[row][col]);
        if (col < 7) Serial.print(", ");
      }
      Serial.println();
    }
    Serial.println("---");
    

    // Pause for clarity, then reset the board
    delay(500);
    blackout();
    delay(2000);
  }
}





