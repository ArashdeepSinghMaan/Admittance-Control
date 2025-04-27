// Code for taking force data from the sensors
const int fsrPin0 = A0;
const int fsrPin1 = A1;
const int fsrPin2 = A2;
const int fsrPin3 = A3;

const float R_FIXED = 10000.0; // Resistance value added in the circuit
const float VCC = 5.0; // Vcc value
const float AREA_M2 = 2.46e-5; //Area of cross section
const float GRAMS_TO_NEWTONS = 0.00980665; // convertion of weight grams into force

// Calibration constant
const float K = 5000000.0; // Initial guess 

void setup() {
  Serial.begin(9600);
}

void loop() {
  int fsrReading0 = analogRead(fsrPin0);
  int fsrReading1 = analogRead(fsrPin1);
  int fsrReading2 = analogRead(fsrPin2);
  int fsrReading3 = analogRead(fsrPin3);
  float voltage0 = fsrReading0 * (VCC / 1023.0);
  float voltage1 = fsrReading1 * (VCC / 1023.0);
  float voltage2 = fsrReading2 * (VCC / 1023.0);
  float voltage3 = fsrReading3 * (VCC / 1023.0);

if (voltage0 < 0.001) voltage0 = 0.001;
if (voltage1 < 0.001) voltage1 = 0.001;
if (voltage2 < 0.001) voltage2 = 0.001;
if (voltage3 < 0.001) voltage3 = 0.001;


  float fsrResistance0 = (VCC - voltage0) * R_FIXED / voltage0;
  float fsrResistance1 = (VCC - voltage1) * R_FIXED / voltage1;
  float fsrResistance2 = (VCC - voltage2) * R_FIXED / voltage2;
  float fsrResistance3 = (VCC - voltage3) * R_FIXED / voltage3;
  // New calibration: Force proportional to 1 / Resistance
  float forceGrams0 = K / fsrResistance0;
  float forceGrams1 = K / fsrResistance1;
  float forceGrams2 = K / fsrResistance2;
  float forceGrams3 = K / fsrResistance3;

  // Clamp the range (optional)
  if (forceGrams0 < 0) forceGrams0 = 0;
  if (forceGrams0 > 1500.0) forceGrams0 = 1500.0;

    // Clamp the range (optional)
  if (forceGrams1 < 0) forceGrams1 = 0;
  if (forceGrams1 > 1500.0) forceGrams1 = 1500.0;
    // Clamp the range (optional)
  if (forceGrams2 < 0) forceGrams2 = 0;
  if (forceGrams2 > 1500.0) forceGrams2 = 1500.0;
    // Clamp the range (optional)
  if (forceGrams3 < 0) forceGrams3 = 0;
  if (forceGrams3 > 1500.0) forceGrams3 = 1500.0;

  float forceNewtons0 = forceGrams0 * GRAMS_TO_NEWTONS;
  float forceNewtons1 = forceGrams1 * GRAMS_TO_NEWTONS;
  float forceNewtons2 = forceGrams2 * GRAMS_TO_NEWTONS;
  float forceNewtons3 = forceGrams3 * GRAMS_TO_NEWTONS;


 
  Serial.print("Sensor 1 :");
  Serial.print(" Analog: ");
  Serial.print(fsrReading0);
  Serial.print(" | Force: ");
  Serial.print(forceNewtons0);
  Serial.println(" N ");

  Serial.print("Sensor 2 :");
  Serial.print(" Analog: ");
  Serial.print(fsrReading1);
  Serial.print(" | Force: ");
  Serial.print(forceNewtons1);
  Serial.println(" N ");

  Serial.print("Sensor 3 :");
  Serial.print(" Analog: ");
  Serial.print(fsrReading2);
  Serial.print(" | Force: ");
  Serial.print(forceNewtons2);
  Serial.println(" N ");

  Serial.print("Sensor 4 :");
  Serial.print(" Analog: ");
  Serial.print(fsrReading3);
  Serial.print(" | Force: ");
  Serial.print(forceNewtons3);
  Serial.println(" N ");
  Serial.println(" ----------------------------------------- ");

  delay(2000);
}