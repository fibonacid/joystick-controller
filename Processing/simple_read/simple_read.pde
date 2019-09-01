import processing.serial.*;

Serial myPort;
int BAUD_RATE = 115200;
String portName = "/dev/cu.usbmodem14201";
int lf = 10;

float x = 0;
float y = 0;
int sw = 0;

void setup() 
{
  size(200, 200);
  myPort = new Serial(this, portName, BAUD_RATE);
  printArray(Serial.list());
  println();
  println();
  
  myPort.bufferUntil(lf);
}

void draw() { 
  background(sw == 0 ? 255 : 0);
  
  float mapX = map(x, 0, 1023, 0, width);
  float mapY = map(y, 0, 1023, 0, height);
  
  stroke(sw == 0 ? 0 : 255);
  strokeWeight(10);
  point(mapX, mapY);
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
