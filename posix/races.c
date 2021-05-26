#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define REGISTRATION 100

typedef struct
{
  long mtype;
} message;


void runner(unsigned int runner_num, int queue_identifier)
{
  message mes;
  mes.mtype = REGISTRATION;
  msgsnd(queue_identifier, &mes, 0, 0);

  printf("runner %d sended registartion request\n", runner_num);

  if (runner_num != 0)
  {
    printf("runner %d waiting for stick\n", runner_num);
    msgrcv(queue_identifier, &mes, 0, runner_num, 0);
    printf("runner %d recieved stick\n", runner_num);
  }

  mes.mtype = runner_num + 1;
  msgsnd(queue_identifier, &mes, 0, 0);
  printf("runner %d sended stick\n", runner_num);
}

void judge(unsigned int runners_value, int queue_identifier)
{
  int i;

  for(i = 0; i < runners_value; ++i)
  {
    message mes;
    msgrcv(queue_identifier, &mes, 0, REGISTRATION, 0);
    printf("runner %d registered\n", i);
  }
  message mes;
  msgrcv(queue_identifier, &mes, 0, runners_value, 0);
  printf("judge recieved stick\n");
}


int main(int argc, char* argv[])
{
  int i = 0;
  int pid = 1;
  int n = 0;
  int me = 0;
  int runner_num;

  if (argc > 1)
    n = atoi(argv[1]);
  else
  {
    printf("no runners\n");
    return 0;
  }

  int qid = msgget(IPC_PRIVATE, IPC_CREAT | 0777);

  pid = fork();
  if (pid == 0)
  {
    judge(n, qid);
    return 0;
  }

  for(; i < n; ++i)
  {
    pid = fork();
    if (pid == 0)
    {
      runner(i, qid);
      return 0;
    }
  }

  return 0;
}
