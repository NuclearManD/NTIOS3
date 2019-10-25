#include "fs.hpp"

//FileHandle* root_dir;

FileHandle* sys_files[] = {
  (FileHandle*)(new StreamFile(&Serial))
};



bool fs_setup(){
  if(!SD.begin(SD_CARD_CS)){
    return false;
  }
  //root_dir = open("/", MODE_RD);
  return true;
}

/*
 * 
 * FileHandle Default Functions
 * 
 */

/*FileHandle* FileHandle::openNextFile(){
  return 0;
}
int FileHandle::rewind(){
  return -1;
}

bool FileHandle::is_dir(){
  return false;
}*/

int FileHandle::print(char* buffer){
  return write(buffer, strlen(buffer));
}

int FileHandle::println(char* buffer){
  int o = write(buffer, strlen(buffer))+1;
  write('\n');
  return o;
}

int FileHandle::printf(char* fmt, ...){
  va_list args;
  va_start(args, fmt);
  return this -> printfv(fmt, args);
}

int FileHandle::printfv(char* fmt, va_list args){
  int chars_written = 0;
  char* lsgood = fmt;

  while(*fmt){
    if((*fmt) == '%'){
      chars_written+=write(lsgood, fmt-lsgood);

      // TODO: Instead of buf[11] make and use a print(int n) function
      // TODO: Change write(char c) to return int and use it in this function
      char buf[11];
      switch(*(++fmt)){
        case 0:
          fmt--;
          break;
        case 'i':
          chars_written += print(itoa(va_arg(args, int), buf, 10));
          break;
        case 'p':
          chars_written += print("@0x");
        case 'h':
        case 'H':
          chars_written += print(itoa(va_arg(args, int), buf, 16));
          break;
        case 's':
          chars_written += print(va_arg(args, char*));
          break;
        case 'c':
          write(va_arg(args, char));
          chars_written++;
          break;
        default:
          chars_written += write(fmt-1, 2);
      }
      lsgood = fmt+1;
    }

    fmt++;
  }
  chars_written+=write(lsgood, fmt-lsgood);
  return chars_written;
}

/*
 * 
 * SDFile Functions
 * 
 */

SDFile::SDFile(File f){
  file = f;
}
void SDFile::close(){
  file.close();
}
int SDFile::tell(){
  return file.position();
}
void SDFile::write(char c){
  file.write(c);
}
int SDFile::write(char* buffer, int n){
  return file.write(buffer, n);
}
int SDFile::read(char* buffer, int n){
  return file.read(buffer, n);
}
byte SDFile::read(){
  return file.read();
}
int SDFile::available(){
  return file.available();
}
int SDFile::seek(int i){
  file.seek(i);
}
bool SDFile::flush(){
  file.flush();
  return true;
}
FileHandle* SDFile::openNextFile(){
  File f = file.openNextFile();
  if (f)
    return (FileHandle*)(new SDFile(f));
  else
    return 0;
}

int SDFile::rewind(){
  file.rewindDirectory();
  return 0;
}
bool SDFile::is_dir(){
  return file.isDirectory();
}
char* SDFile::name(){
  return file.name();
}

/*
 * 
 * StreamFile Functions
 * 
 */

StreamFile::StreamFile(Stream* f){
  stream = f;
}
void StreamFile::close(){
  loc = 0;
  flush(); // save state, as required by close()
  // DO NOT MODIFY THIS FUNCTION.
  // Closing a StreamFile object should not actually be possible, the stream should never be truely closed.
}
int StreamFile::tell(){
  return loc;
}
void StreamFile::write(char c){
  stream->write(c);
}
int StreamFile::write(char* buffer, int n){
  return stream->write(buffer, n);
}
int StreamFile::read(char* buffer, int n){
  int i;
  for(i=0;i<n;i++){
    if(available()){
      buffer[i] = read();
    }else break;
  }
  loc+=i;
  return i;
}
byte StreamFile::read(){
  if(available())loc++;
  return stream->read();
}

int StreamFile::available(){
  return stream->available();
}

int StreamFile::seek(int i){
  return loc;
}

bool StreamFile::flush(){
  stream->flush();
  return true;
}

char* StreamFile::name(){
  return "?";
}

FileHandle* StreamFile::openNextFile(){
  return 0;
}
int StreamFile::rewind(){
  return -1;
}

bool StreamFile::is_dir(){
  return false;
}

/*
 * 
 * Global functions for file operations
 * 
 */

FileHandle* open(char* name, int mode){
  File f = SD.open(name, mode);

  if(f)return (FileHandle*)(new SDFile(f));
  return 0;
}

FileHandle* open(int id, int mode){
  Task* task = get_task_by_id(current_task_id());

  if (id < 100)
    return sys_files[id];

  if (task)
    return task -> getFileHandle(id, mode);
  else{
    if (id<=102)
      return sys_files[0];
    else
      return 0;
  }
}
