

char bigLED[8][8]; // Represents the LED state as a 2D array

// Moves for various pieces
const int kingMoves[9][2] = {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {0,-1}, {-1,1},{-1,0}};
const int knightMoves[8][2] = {{2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {-1,2}, {1,-2}, {-1,-2}};
const int pawnMoves[3][2] = {{1,0}, {1,1}, {1,-1}};

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
    case 'P': // Pawn
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


      break;
    case 'R': // Rook
      for (int direction = -1; direction <= 1; direction += 2) {
        // Vertical movement
        int rowShift = direction;
        while (inBounds(inSquare.row + rowShift)) {
          int newRow = inSquare.row + rowShift;
          int newCol = inSquare.col;
          board[newRow][newCol].otherLight(inPiece);
          if (board[newRow][newCol].piece.type != 'V') break; // Stop if blocked
          rowShift += direction;
        }
        // Horizontal movement
        int colShift = direction;
        while (inBounds(inSquare.col + colShift)) {
          int newRow = inSquare.row;
          int newCol = inSquare.col + colShift;
          board[newRow][newCol].otherLight(inPiece);
          if (board[newRow][newCol].piece.type != 'V') break; // Stop if blocked
          colShift += direction;
        }
      }
      break;

    case 'B': // Bishop
      for (int rowDir = -1; rowDir <= 1; rowDir += 2) {
        for (int colDir = -1; colDir <= 1; colDir += 2) {
          int rowShift = rowDir;
          int colShift = colDir;
          while (inBounds(inSquare.row + rowShift) && inBounds(inSquare.col + colShift)) {
            int newRow = inSquare.row + rowShift;
            int newCol = inSquare.col + colShift;
            board[newRow][newCol].otherLight(inPiece);
            if (board[newRow][newCol].piece.type != 'V') break; // Stop if blocked
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

  }
}

void setup() {
  Serial.begin(9600);
  setupChessBoard();
  blackout();
}

void loop() {


blackout();

int row = 1;
int col = 1;
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


/*
  // "Go over the whole board" type beat.
  for (int row = 0; row < 8; row++){
    for (int col = 0; col < 8; col++){
      blackout();
      bigLED[row][col] = 'P';
        for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Serial.print(bigLED[i][j]);
      if (j < 7) Serial.print(", ");
    }
    Serial.println();
  }
  Serial.println("---");
  delay(10);
    }
  }
  */
  // Print the LED board

}
