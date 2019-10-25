#include <SD.h>
#include <SPI.h>
#include "kernel.hpp"
#include "task.hpp"

void setup() {
  Serial.begin(115200);
  delay(800);
  Serial.println("Setting up kernel...");
  fs_setup();
  setup_taskengine();
  FileHandle* root = open("/", MODE_RD);
  _printf("Root* = %p\n%s:\n", root, root->name());
  root->rewind();
  while(true){
    FileHandle* file = root->openNextFile();
    if (file)
      _printf("\t%s\n", file->name());
    else
      break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  _printf("%c:", _getchar());
}
