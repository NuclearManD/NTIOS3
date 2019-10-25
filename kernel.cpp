#include "kernel.hpp"
#include "task.hpp"

void stdo(char* data){
  open(FILE_ID_STDOUT, MODE_WR) -> print(data);
}

int _printf(char* fmt, ...){
  va_list args;
  va_start(args, fmt);
  return printfv(fmt, args);
}

int printfv(char* fmt, va_list args){
  return open(FILE_ID_STDOUT, MODE_WR) -> printfv(fmt, args);
}

int _getchar(){
  FileHandle* file = open(FILE_ID_STDIN, MODE_RD);

  while(!(file -> available()));
  return file -> read();
}
