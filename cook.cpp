#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "header.h"
using namespace std;
sem_t sem1,sem2;
int idx=2;
void* cook(void* args)
{
    sem_wait(&sem2);
    cout<<"Cook number "<<idx<<" is working on the order \n"; 
    idx=1;
    sleep(8);
    idx=2;
    sem_post(&sem2);

}

int main()
{
    orderSeq *ord=new orderSeq();
    
    while(1)
    {
        int cf=open("cpipe",O_RDONLY);
        read(cf,ord,sizeof(orderSeq));
        cout<<"Order receiverd by cook of Customer "<<ord->obj.name<<" with ID = "<<ord->obj.id<<endl;
        cout<<"Your order is as follows : \n";
        for(int i=0;i<3;i++)
        {
            cout<<ord->obj2[i].name_dish<<"\t"<<ord->obj1.quantity[i]<<endl;
        }
        close(cf);
        int sum=0;
        for(int i=0;i<3;i++)
         sum+=ord->obj1.quantity[i];
        pthread_t *t=new pthread_t[sum]();
        sem_init(&sem2,0,idx);
        for(int i=0;i<sum;i++)
        {
            
            idx=2;
            pthread_create(&t[i],NULL,&cook,NULL);

        }
        cout<<"No cook is free at the moment\nPlease Wait!\n";
    }
}
