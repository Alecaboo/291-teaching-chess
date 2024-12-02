// Define pins
const int ROW_PL_PIN = 8;    // Parallel load for row shift register
const int ROW_CP_PIN = 9;    // Clock for row shift register
const int ROW_DS_PIN = 10;   // Data serial input for row shift register
const int COL_PL_PIN = 11;   // Parallel load for column shift register
const int COL_CP_PIN = 12;   // Clock for column shift register
const int COL_Q7_PIN = 13;   // Serial output for column shift register

// Number of rows and columns
const int ROWS = 8;          // Adjust for your configuration
const int COLS = ROWS;          // Adjust for your configuration

int magnetState[ROWS][COLS]; 

void setup() {
  pinMode(ROW_PL_PIN, OUTPUT);
  pinMode(ROW_CP_PIN, OUTPUT);
  pinMode(ROW_DS_PIN, OUTPUT);
  pinMode(COL_PL_PIN, OUTPUT);
  pinMode(COL_CP_PIN, OUTPUT);
  pinMode(COL_Q7_PIN, INPUT);

  digitalWrite(ROW_PL_PIN, HIGH);
  digitalWrite(ROW_CP_PIN, LOW);
  digitalWrite(ROW_DS_PIN, LOW);
  digitalWrite(COL_PL_PIN, HIGH);
  digitalWrite(COL_CP_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  for (int row = 0; row < ROWS; row++) {
    // Activate the current row
    writeShiftRegister(row);

    // Read the columns
    uint8_t columnStates = readShiftRegister();

    // Process each column
    for (int col = 0; col < COLS; col++) {
      int sensorValue = (columnStates >> col) & 0x01;
      Serial.print("Sensor[");
      Serial.print(row);
      Serial.print("][");
      Serial.print(col);
      Serial.print("]: ");
      Serial.println(sensorValue);
      magnetState[row][col] = sensorValue;
      }
    }
  }
  delay(500); // Adjust as needed
}

// Function to activate one row at a time
void writeShiftRegister(int row) {
  uint8_t rowState = (1 << row); // Activate one row (set one bit high)
  
  // Load row state into the shift register
  shiftOut(ROW_DS_PIN, ROW_CP_PIN, MSBFIRST, rowState);
}

// Function to read columns via the shift register
uint8_t readShiftRegister() {
  uint8_t data = 0;

  // Load column states into the shift register
  digitalWrite(COL_PL_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(COL_PL_PIN, HIGH);

  // Read 8 bits (1 byte) from the column shift register
  for (int i = 0; i < 8; i++) {
    data <<= 1;
    if (digitalRead(COL_Q7_PIN)) {
      data |= 1;
    }
    digitalWrite(COL_CP_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(COL_CP_PIN, LOW);
  }

  return data;
}
