#ifndef TASK_HPP
#define TASK_HPP

#define TASK_STATUS_RUNNING 0
#define TASK_STATUS_WAITING 1
#define TASK_STATUS_EXITED 2
#define TASK_STATUS_KILLED 3
#define TASK_STATUS_ERRORED 4

#define TASK_PRIORITY_LOW 0
#define TASK_PRIORITY_MED 1
#define TASK_PRIORITY_HIGH 2

#include "fs.hpp"
#include "kernel.hpp"

class Task{
public:
  Task(int (*entry)(int, char**), int argc, char** argv);
  FileHandle* getFileHandle(int id, int mode);
  int taskStatus();
  int exitCode();
  int kill();
  void join();
  void start();

  FileHandle* _stdin;
  FileHandle* _stdout;
  FileHandle* _stderr;
private:
  int exit_code;
  int (*entry)(int, char**);
  int argc;
  char** argv;
};

void setup_taskengine();

int createTask(int (*entry)(int, char**), int argc, char** argv, int priority);
int current_task_id();
Task* get_task_by_id(int id);
int get_num_tasks();

#endif
