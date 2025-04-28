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

#define MIN_PULSE_WIDTH 500   // Microseconds (adjust as per driver datasheet)



// Code for taking force data from the sensors
const int fsrPin0 = A4; // + x-axis
const int fsrPin1 = A5; // + y-axis
const int fsrPin2 = A6; // - x-axis
const int fsrPin3 = A7; // - y-axis
const int fsrPins[4] = {fsrPin0, fsrPin1, fsrPin2, fsrPin3 };
// const int fsrOutput[4] = {fsrOp0, fsrOp1, fsrOp2, fsrOp3 };
const int fsrOutput[4];

// Variables
// int fsrReading;
int fsrVoltage;
unsigned long fsrResistance;
unsigned long fsrConductance;
long fsrForce;

// const float R_FIXED = 10000.0; // Resistance value added in the circuit
// const float VCC = 5.0; // Vcc value
// const float AREA_M2 = 2.46e-5; //Area of cross section
// const float GRAMS_TO_NEWTONS = 0.00980665; // convertion of weight grams into force

// // Calibration constant
// const float K = 5000000.0; // Initial guess 

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

  // Code for the xaxis and yaxis move using joystick ( initialization )
  int Xval = analogRead(Xaxis_pin);
  int Yval = analogRead(Yaxis_pin);
  int SWval = digitalRead(SW_pin);
  
  int fsrReading0 = analogRead(fsrPin0);
  Serial.print("Sensor 1 ");
  Serial.print(" - Analog reading = ");
  Serial.println(fsrReading0);

  int fsrReading1 = analogRead(fsrPin1);
  Serial.print("Sensor 2 ");
  Serial.print(" - Analog reading = ");
  Serial.println(fsrReading1);

  int fsrReading2 = analogRead(fsrPin2);
  Serial.print("Sensor 3 ");
  Serial.print(" - Analog reading = ");
  Serial.println(fsrReading2);

  int fsrReading3 = analogRead(fsrPin3);
  Serial.print("Sensor 4 ");
  Serial.print(" - Analog reading = ");
  Serial.println(fsrReading3);

  int fsrVoltage0 = map(fsrReading0, 0, 1023, 0, 5000);
  // Serial.print("Voltage reading 1 in mV = ");
  // Serial.println(fsrVoltage0);  

  int fsrVoltage1 = map(fsrReading1, 0, 1023, 0, 5000);
  // Serial.print("Voltage reading 2 in mV = ");
  // Serial.println(fsrVoltage1);  

  int fsrVoltage2 = map(fsrReading2, 0, 1023, 0, 5000);
  // Serial.print("Voltage reading 3 in mV = ");
  // Serial.println(fsrVoltage2);  

  int fsrVoltage3 = map(fsrReading3, 0, 1023, 0, 5000);
  // Serial.print("Voltage reading 4 in mV = ");
  // Serial.println(fsrVoltage3);  

  // Calculate FSR resistance
  float fsrResistance0 = (5000.0 - fsrVoltage0) * 10000.0 / fsrVoltage0;
  float fsrResistance1 = (5000.0 - fsrVoltage1) * 10000.0 / fsrVoltage1;
  float fsrResistance2 = (5000.0 - fsrVoltage2) * 10000.0 / fsrVoltage2;
  float fsrResistance3 = (5000.0 - fsrVoltage3) * 10000.0 / fsrVoltage3;
  // Serial.print("FSR resistance (ohms): ");
  // Serial.println(fsrResistance);

  // Calculate FSR conductance
  float fsrConductance0 = 1000000.0 / fsrResistance0;
  float fsrConductance1 = 1000000.0 / fsrResistance1;
  float fsrConductance2 = 1000000.0 / fsrResistance2;
  float fsrConductance3 = 1000000.0 / fsrResistance3;
  // Serial.print("FSR conductance (microMhos): ");
  // Serial.println(fsrConductance);

  // Estimate force from conductance
  float fsrForce0;
  float fsrForce1;
  float fsrForce2;
  float fsrForce3;

  // Estimated force for the sensor 1
  if (fsrConductance0 <= 1000.0) {
  fsrForce0 = fsrConductance0 / 80.0;
  } else {
  fsrForce0 = (fsrConductance0 - 1000.0) / 30.0;
  }
  Serial.print("Estimated force sensor 1 (Newtons): ");
  Serial.println(fsrForce0);

  // Estimated force for the sensor 2
  if (fsrConductance1 <= 1000.0) {
  fsrForce1 = fsrConductance1 / 80.0;
  } else {
  fsrForce1 = (fsrConductance1 - 1000.0) / 30.0;
  }
  Serial.print("Estimated force sensor 2 (Newtons): ");
  Serial.println(fsrForce1);

  // Estimated force for the sensor 3
  if (fsrConductance2 <= 1000.0) {
  fsrForce2 = fsrConductance2 / 80.0;
  } else {
  fsrForce2 = (fsrConductance2 - 1000.0) / 30.0;
  }
  Serial.print("Estimated force sensor 3 (Newtons): ");
  Serial.println(fsrForce2);

  // Estimated force for the sensor 4
  if (fsrConductance3 <= 1000.0) {
  fsrForce3 = fsrConductance3 / 80.0;
  } else {
  fsrForce3 = (fsrConductance3 - 1000.0) / 30.0;
  }
  Serial.print("Estimated force sensor 4 (Newtons): ");
  Serial.println(fsrForce3);


  // Threshold of the force sensor
  float threshold1 = 3.0;  // you can adjust this
  float threshold2 = 5.0;  // you can adjust this

  //Values of the data from the joystick
  // Serial.print("X: ");
  // Serial.print(Xval);
  // Serial.print(" | Y: ");
  // Serial.print(Yval);
  // Serial.print(" | Switch: ");
  // Serial.println(SWval);


  delay(5);

  if (SWval == LOW) {
    // Stop both motors when switch is pressed
    return;
  }

  int pulse_count = 100;
  int X_stepDelay = 0;
  int Y_stepDelay = 0;
  bool X_movement = false;
  bool Y_movement = false;

  // X-axis motor control
  if (fsrForce0 > threshold1) {
    digitalWrite(X_DIR_PIN, LOW);  // CCW
    //X_stepDelay = 100;              // Fast
    X_movement = true;
  } 
  // else if (fsrForce0 > 1 && fsrForce0 < threshold1) {
  //   digitalWrite(X_DIR_PIN, LOW);  // CCW
  //   X_stepDelay = 100;             // Slow
  //   X_movement = true;
  // }
  else if (fsrForce2 > threshold1)  {
    digitalWrite(X_DIR_PIN, HIGH); // CW
    //X_stepDelay = 100;              // Fast
    X_movement = true;
  }
  // else if (fsrForce2 > 1 && fsrForce2 < threshold1) {
  //   digitalWrite(X_DIR_PIN, HIGH); // CW
  //   X_stepDelay = 100;             // Slow
  //   X_movement = true;
  // }

  // Y-axis motor control
  if (fsrForce3 > threshold1) {
    digitalWrite(Y_DIR_PIN, HIGH);  // CCW
    //Y_stepDelay = 100;              // Fast
    Y_movement = true;
  }
  // else if (fsrForce3 > 1 && fsrForce3 < threshold1) {
  //   digitalWrite(Y_DIR_PIN, HIGH);  // CCW
  //   Y_stepDelay = 100;             // Slow
  //   Y_movement = true;
  // }
  else if (fsrForce1 > threshold1) {
    digitalWrite(Y_DIR_PIN, LOW); // CW
    //Y_stepDelay = 100;              // Fast
    Y_movement = true;
  }
  // else if (fsrForce1 > 1 && fsrForce1 < threshold1) {
  //   digitalWrite(Y_DIR_PIN, LOW); // CW
  //   Y_stepDelay = 100;             // Slow
  //   Y_movement = true;
  // }

  // Pulse for X-axis motor
  if (X_movement) {

    // digitalWrite(X_STEP_PIN, HIGH);
    // delayMicroseconds(X_stepDelay);
    // digitalWrite(X_STEP_PIN, LOW);
    // delayMicroseconds(X_stepDelay);
    for (int i = 0; i < pulse_count; i++) {
      digitalWrite(X_STEP_PIN, HIGH);
      delayMicroseconds(MIN_PULSE_WIDTH);
      digitalWrite(X_STEP_PIN, LOW);
      delayMicroseconds(MIN_PULSE_WIDTH);
    }
  }

  // Pulse for Y-axis motor
  if (Y_movement) {
    // digitalWrite(Y_STEP_PIN, HIGH);
    // delayMicroseconds(Y_stepDelay);
    // digitalWrite(Y_STEP_PIN, LOW);
    // delayMicroseconds(Y_stepDelay);
    for (int i = 0; i < pulse_count; i++) {
      digitalWrite(Y_STEP_PIN, HIGH);
      delayMicroseconds(MIN_PULSE_WIDTH);
      digitalWrite(Y_STEP_PIN, LOW);
      delayMicroseconds(MIN_PULSE_WIDTH);
    }

  }
}
