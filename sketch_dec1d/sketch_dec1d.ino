const int rows = 8;
const int cols = rows;
int array[rows][cols];

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  // Fill the array with random values (example)
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      array[i][j] = random(0, 2); // Values between 0-255
    }
  }

  // Send the array as CSV
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Serial.print(array[i][j]);
      if (j < cols - 1) Serial.print(","); // Add comma between values
    }
    Serial.println(); // Newline at the end of each row
  }

  Serial.println("---"); // Separator for arrays
  delay(500); // Update rate
}