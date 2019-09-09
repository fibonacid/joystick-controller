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
const int LED_pin = 3;

// Register
int last_sw;
int last_x;
int last_y;
int x_at_rest;
int y_at_rest;

// Led stuff
int led_brightness;
int led_counter = 0;

// Program flow
boolean first_loop = true;

/**
 * SETUP 
 * =====
 */
void setup() {
  // Initialize pins
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  pinMode(LED_pin, OUTPUT);

  // Calculate rest values for sensor 
  x_at_rest = 512 - analogRead(X_pin);
  y_at_rest = 512 - analogRead(Y_pin);

  // Start serial comunication
  Serial.begin(115200);
}

/**
 * LOOP
 * ====
 */
void loop() {

  int current_time = millis();
  
  // Get sensor data
  int x = analogRead(X_pin);
  int y = analogRead(Y_pin);
  int sw = !digitalRead(SW_pin);

  // Apply transformations
  int tx = 512 - y;
  int ty = 512 - x;

  // Fix precision
  tx -= y_at_rest;
  ty -= x_at_rest;

  // Protect from exceeding the nominal bounds.
  tx = constrain(tx, -512, 512);
  ty = constrain(ty, -512, 512);

  // If values have changed significantly:
  if (values_changed(tx, ty, sw) || first_loop) { 
    // Override memorized values
    last_x = tx;
    last_y = ty;
    last_sw = sw;
    // Send data
    Serial.print(tx);
    Serial.print(",");
    Serial.print(ty);
    Serial.print(",");
    Serial.print(sw);
    Serial.print("\n");
    // Calculate distance from center
    int dist = sqrt(tx^2 + ty^2);
    // Normalize it
    int ndist = dist / 512;
  }

  led_counter+= 20;
  led_brightness = 40 + (0.5 + 0.5 * sin(radians(led_counter))) * 205;
  analogWrite(LED_pin, led_brightness);

  first_loop = false;
  delay(100);
}

/**
 * VALUES CHANGED
 * ==============
 * This function returns true if the given x or y values
 * have changed significally from their recorded values
 */
boolean values_changed(int x, int y, int sw) {
  int minimum = 2; 
  return abs(x - last_x) >= minimum ||
         abs(y - last_y) >= minimum || 
         sw != last_sw;
}  
