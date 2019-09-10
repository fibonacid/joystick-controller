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
int led_increment = 10;

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

  // Get sensor data
  int x = analogRead(X_pin);
  int y = analogRead(Y_pin);
  int sw = !digitalRead(SW_pin);

  // Apply transformations
  int tx = 512 - y;
  int ty = 512 - x;

  // Fix precision
  //tx -= y_at_rest;
  //ty -= x_at_rest;

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
    // Calculate distance from center,
    int dist = sqrt( pow(tx,2) + pow(ty, 2) );
    // Set led blink speed based on that value.
    led_increment = 5 + 175 * (dist / 512.0);
  }

  // If switch is being clicked
  if (sw == 1) {
    // Set led brightness to 0.
    led_brightness = 0;
  } 
  // Else: if switch is not being clicked
  else {
    // Let led blink.
    led_counter += led_increment;
    led_brightness =  20 + 235 * (0.5 + 0.5 * sin(radians(led_counter))); 
  }
  // Set led pwm value
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
