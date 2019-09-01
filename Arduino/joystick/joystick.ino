/**
 * ============================================
 * title: Joystick Controller
 * author: Lorenzo Rivosecchi 
 * version: 0.0.1
 * data: 01/09/2019
 * ============================================
 * see https://www.youtube.com/watch?v=MlDi0vO9Evg
 */

// Arduino Pin numbers
const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
}

void loop() {
  Serial.print("Switch:\t");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis:\t");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis:\t");
  Serial.print(analogRead(Y_pin));
  Serial.print("\n\n");
  delay(500);
}
