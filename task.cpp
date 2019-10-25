#include "task.hpp"

Task** tasklist;
int n_tasks;
int current_task = -1;

void setup_taskengine(){
  tasklist = (Task**)malloc(0);
  n_tasks = 0;
}

FileHandle* Task::getFileHandle(int id, int mode){
  switch(id){
    case 100:
      return _stdin;
    case 101:
      return _stdout;
    case 102:
      return _stderr;
    default:
      return 0;
  }
}
int Task::taskStatus(){
  return -1;
}
int Task::exitCode(){
  return exit_code;
}
int Task::kill(){
  return -1;
}
void Task::join(){
  ;
}
void Task::start(){
  entry(argc, argv);
}
Task::Task(int (*entry)(int, char**), int argc, char** argv){
  this -> entry = entry;
  this -> argc = argc;
  this -> argv = argv;
}

int createTask(void (*entry)(int, char**), int argc, char** argv, int priority){
  tasklist = (Task**)realloc(tasklist, (++n_tasks)*sizeof(Task*));
  tasklist[n_tasks-1] = new Task(entry, argc, argv);
  return n_tasks-1;
}

int current_task_id(){
  return current_task;
}
Task* get_task_by_id(int id){
  if(id<0)return 0;
  if(id>=n_tasks)return 0;
  return tasklist[id];
}
int get_num_tasks(){
  return n_tasks;
}
