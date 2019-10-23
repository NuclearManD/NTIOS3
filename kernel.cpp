#include "kernel.hpp"

void stdo(char* data){
  open(0,0)->print(data);
}
