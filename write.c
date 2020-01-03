#include "control.h"

int main(){
  char * data;
  sb.sem_num = 0;
  sb.sem_op = -1;
  file = open("story.txt", O_WRONLY | O_APPEND);

  semid = semget(SEMKEY, 1, 0);
  printf("trying to get in\n");
  semop(semid, &sb, 1);


  shmid = shmget(SHKEY, 1000, IPC_CREAT | 0644);
  data = shmat(shmid, 0, 0);

  printf("Last addition: %s\n", data);

  printf("Your addition: ");
  fgets(data, 1000, stdin);

  write(file, data, strlen(data));
  close(file);

  //printf("Your addition: %s\n", nextline);

  shmdt(data);

  sb.sem_op = 1;
  semop(semid, &sb, 1);
  return 0;
}
