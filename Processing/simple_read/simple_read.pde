 import processing.serial.*;

Serial port;
int BAUD_RATE = 115200;
String portName = "/dev/cu.usbmodem14201";
int lf = 10;

float x = 0;
float y = 0;
int sw = 0;

void setup() {
  size(200, 200);
  port = new Serial(this, portName, BAUD_RATE);
  printArray(Serial.list());
  println();
  println();
}

void draw() { 
  background(sw == 0 ? 255 : 0);
   
  stroke(sw == 0 ? 0 : 255);
  strokeWeight(20);
  
  float mapX = (x / 512.0) * width * 0.5;
  float mapY = (-y / 512.0) * height * 0.5;
  
  pushMatrix();
  translate(width/2.0, height/2.0);
  point(mapX, mapY);
  popMatrix();
}

void serialEvent(Serial p) {
    String input = p.readStringUntil(lf);
    if (input != null) {
      String[] blocks = input.split(","); 
      x = int(blocks[0]);
      y = int(blocks[1]);
      sw = int(blocks[2]);
      print(input);  
    }
}
