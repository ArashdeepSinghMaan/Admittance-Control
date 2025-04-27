// X-axis motor
#define X_STEP_PIN 2    // Connected to X PUL+
#define X_DIR_PIN 3     // Connected to X DIR+

// Y-axis motor
#define Y_STEP_PIN 4    // Connected to Y PUL+
#define Y_DIR_PIN 5     // Connected to Y DIR+

// Joystick pins
#define Xaxis_pin A0    // Joystick X-axis
#define Yaxis_pin A1    // Joystick Y-axis
#define SW_pin A2       // Joystick button

void setup() {
  // Setup motor control pins
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  
  pinMode(SW_pin, INPUT_PULLUP); // Joystick button
  
  // Default directions
  digitalWrite(X_DIR_PIN, LOW);
  digitalWrite(Y_DIR_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  int Xval = analogRead(Xaxis_pin);
  int Yval = analogRead(Yaxis_pin);
  int SWval = digitalRead(SW_pin);

  Serial.print("X: ");
  Serial.print(Xval);
  Serial.print(" | Y: ");
  Serial.print(Yval);
  Serial.print(" | Switch: ");
  Serial.println(SWval);

  if (SWval == LOW) {
    // Stop both motors when switch is pressed
    return;
  }

  int X_stepDelay = 0;
  int Y_stepDelay = 0;
  bool X_movement = false;
  bool Y_movement = false;

  // X-axis motor control
  if (Xval < 300) {
    digitalWrite(X_DIR_PIN, LOW);  // CCW
    X_stepDelay = 75;              // Fast
    X_movement = true;
  } 
  else if (Xval < 450) {
    digitalWrite(X_DIR_PIN, LOW);  // CCW
    X_stepDelay = 500;             // Slow
    X_movement = true;
  }
  else if (Xval > 723) {
    digitalWrite(X_DIR_PIN, HIGH); // CW
    X_stepDelay = 75;              // Fast
    X_movement = true;
  }
  else if (Xval > 573) {
    digitalWrite(X_DIR_PIN, HIGH); // CW
    X_stepDelay = 500;             // Slow
    X_movement = true;
  }

  // Y-axis motor control
  if (Yval < 300) {
    digitalWrite(Y_DIR_PIN, LOW);  // CCW
    Y_stepDelay = 75;              // Fast
    Y_movement = true;
  }
  else if (Yval < 450) {
    digitalWrite(Y_DIR_PIN, LOW);  // CCW
    Y_stepDelay = 500;             // Slow
    Y_movement = true;
  }
  else if (Yval > 723) {
    digitalWrite(Y_DIR_PIN, HIGH); // CW
    Y_stepDelay = 75;              // Fast
    Y_movement = true;
  }
  else if (Yval > 573) {
    digitalWrite(Y_DIR_PIN, HIGH); // CW
    Y_stepDelay = 500;             // Slow
    Y_movement = true;
  }

  // Pulse for X-axis motor
  if (X_movement) {
    digitalWrite(X_STEP_PIN, HIGH);
    delayMicroseconds(X_stepDelay);
    digitalWrite(X_STEP_PIN, LOW);
    delayMicroseconds(X_stepDelay);
  }

  // Pulse for Y-axis motor
  if (Y_movement) {
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(Y_stepDelay);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(Y_stepDelay);
  }
}
