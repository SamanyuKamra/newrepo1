#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<math.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <semaphore.h>

#define num 50
#define index 8
#define file "sem"
struct timespec a1;
struct timespec a2;

int min(int x, int y)
{
    if(x>y)
    {
        return y;
    }
    else{
        return x;
    }
}
void leave(char** s)
{
    strcpy(*s,"waiting");
}
void capture(char** s)
{
    while(strcmp(*s,"waiting")==0){}
}

int main()
{
    char* temp = (char*)malloc((index)*sizeof(char));
    key_t passwd = ftok("SharedMemory",50);
    int id = shmget(passwd,1024,0666|IPC_CREAT);
    temp = (char*)shmat(id,NULL,0);
    int var = 0;
    while(var<50){
        int b = var;
        for(;b<min(var+5,num);b++){
            capture(&temp);
            printf("received by p2 : %s\n",temp);
            leave(&temp);

        }
        var+=5;
    }
    clock_gettime(CLOCK_REALTIME,&a2);
    printf("Exexution time = %f\n",fabs(((a2.tv_sec - a1.tv_sec)+(a2.tv_nsec - a1.tv_nsec))/1e9));
    return 0;
}
