import processing.serial.*;

Serial myPort;
int BAUD_RATE = 115200;
String portName = "/dev/cu.usbmodem14201";

void setup() 
{
  size(200, 200);
  myPort = new Serial(this, portName, BAUD_RATE);
  printArray(Serial.list());
  println();
  println();
}

void draw() {
  if ( myPort.available() > 0) {  // If data is available,
    print(myPort.read());         // read it
  }
}
