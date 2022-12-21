#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <semaphore.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>


#define num 50
struct timespec a1;
#define index 9

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
    strcpy(*s,"");
}
void capture(char** s)
{
    while(strcmp(*s,"waiting")!=0){}
}

int main()
{
    
    clock_gettime(CLOCK_REALTIME,&a1);
    char* arr[50];
    int i;
    for(i = 0;i<num;i++)
    {
        arr[i] = (char*)malloc((index)*sizeof(char));
    }

    for(int j = 0;j<num;j++)
    {
        int k;
        if(j>=10)
        {
            arr[j][0] = '0'+j/10;
            arr[j][1] = '0'+j%10;
            arr[j][2] =' ';
            k = 3;
        }
        else
        {
            arr[j][0] = '0' + j;
            arr[j][1] = ' ';
            k = 2;
        }
        while(k < index-2)
        {
            arr[j][k] = rand()%26 + 65;
            k++;
        }
        arr[j][index-1] = '\0';
    }
    char* temp = (char*)malloc(sizeof(arr[0]));
    key_t passwd = ftok("SharedMemory",50);
    int id = shmget(passwd,1024,0666|IPC_CREAT);

    temp = (char*) shmat(id,NULL,0);
    
    for(int a=0;a<num;)
    {
        int d = a;
        while(d<min(a+5,num))
        {
            strcpy(temp,arr[d]);
            capture(&temp);
            d++;
        }
        a=d
        printf("MAX ID received by p1: %d\n",a-1);
    }
    return 0;
}
