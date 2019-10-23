#include <SD.h>
#include <SPI.h>
#include "fs.hpp"

void setup() {
  Serial.begin(115200);
  delay(800);
  fs_setup();
  open(0,0)->write("Hello World!\n", 13);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
