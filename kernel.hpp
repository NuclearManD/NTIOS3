#ifndef KERNEL_HPP
#define KERNEL_HPP

#define EOF -1000

#include "fs.hpp"

void stdo(char* data);
int _printf(char* fmt, ...);
int printfv(char* fmt, va_list args);
int _getchar();

#endif
