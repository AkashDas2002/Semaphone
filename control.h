#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


union semun arg;

struct sembuf sb;

#define SHKEY 24601
#define SEMKEY 24602

int semid;
int shmid;
int file;

int create();
int view();
int removal();
