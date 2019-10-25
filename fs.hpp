#ifndef FS_HPP
#define FS_HPP

#include "stdbool.h"
#include "Arduino.h"
#include <SD.h>
#include <SPI.h>
#include "conf.h"

#define MODE_RD O_READ
#define MODE_WR O_WRITE
#define MODE_APPEND O_APPEND

#define FILE_ID_SERIAL 0
#define FILE_ID_SERIAL1 1
#define FILE_ID_SERIAL2 2

#define FILE_ID_STDIN 100
#define FILE_ID_STDOUT 101
#define FILE_ID_STDERR 102

bool fs_setup();

class FileHandle{
  public:
    virtual void close() = 0;
    virtual int tell() = 0;
    virtual void write(char c) = 0;
    virtual int write(char* buffer, int n) = 0;
    virtual int read(char* buffer, int n) = 0;
    virtual byte read() = 0;
    virtual int available() = 0;
    virtual int seek(int i) = 0;
    virtual bool flush() = 0;
    virtual char* name() = 0;
    virtual FileHandle* openNextFile() = 0;
    virtual int rewind() = 0;
    virtual bool is_dir() = 0;
    int print(char* buffer);
    int println(char* buffer);
    int printf(char* fmt, ...);
    int printfv(char* fmt, va_list args);
    
};

// This include has to be here for task to have access to FileHandle
#include "task.hpp"

class SDFile: FileHandle{
  public:
    SDFile(File f);
    void close();
    int tell();
    void write(char c);
    int write(char* buffer, int n);
    int read(char* buffer, int n);
    byte read();
    int seek(int i);
    bool flush();
    FileHandle* openNextFile() override;
    int rewind();
    bool is_dir();
    int available();
    char* name();
  private:
    File file;
};

class StreamFile: FileHandle{
  public:
    StreamFile(Stream* f);
    void close();
    int tell();
    void write(char c);
    int write(char* buffer, int n);
    int read(char* buffer, int n);
    byte read();
    int seek(int i);
    bool flush();
    FileHandle* openNextFile();
    int rewind();
    bool is_dir();
    int available();
    char* name();
  private:
    int loc;
    Stream* stream;
};

FileHandle* open(char* name, int mode);
FileHandle* open(int id, int mode);

#endif
