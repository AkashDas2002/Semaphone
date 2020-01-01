#include "control.h"

int main(int argc, char *argv[]) {
  arg.val = 1;
  sb.sem_num = 0;
  sb.sem_op = -1;
  char command[3];

  strcpy(command, argv[1]);

  if (strcmp(command, "-c") == 0) {
    create();
  }
  else if (strcmp(command, "-v") == 0) {
    view();
  }
  else if (strcmp(command, "-r") == 0) {
    removal();
  }
  else {
    return 0;
  }
}

int create(){
  semid = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  semctl(semid, 0, SETVAL, arg);
  printf("semaphore created\n");

  shmid = shmget(SHKEY, 1000, IPC_CREAT | IPC_EXCL | 0644);
  printf("shared memory created\n");

  file = open("story.txt",  O_CREAT | O_TRUNC | O_RDWR, 0644);
  close(file);
  printf("file created\n");
  return 1;
}

int view(){
  int file = open("story.txt", O_RDONLY);
  char text[1000];
  read(file, text, 1000);
  printf("The story so far:\n%s\n", text);
  close(file);
  return 1;
}

int removal(){
  printf("trying to get in\n");

  shmid = shmget(SHKEY, 1000, 0);
  shmctl(shmid, IPC_RMID, 0);
  printf("shared memory removed\n");

  remove("story.txt");
  printf("file removed\n");

  semid = semget(SEMKEY, 1, 0);
  semop(semid, &sb, 1);
  semctl(semid, IPC_RMID, 0);
  printf("semaphore removed\n");

  return 1;
}
