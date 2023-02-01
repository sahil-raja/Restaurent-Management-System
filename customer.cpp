#include<pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "header.h"

using namespace std;

Customer *c=new Customer();
Menu *menu=new Menu[5]();
order *O1=new order();

void* customerEntry(void* args)
{
    cin.ignore();
    int f1 = open ("npipe",O_WRONLY);
    if (f1 < 0)
        cout <<"Could not create pipe\n";
    else
        cout <<"Pipe created successfully \n";
        f1 = open ("npipe",O_WRONLY);
      cout<<"Welcome to FAST DHABBA \nEnter your NAME and ID to proceed with the Menu:\n";
      cout<<"Name: ";
      cin.getline(c->name,20);
      cout<<"ID: ";
      cin >> c->id;
      cin.ignore();
      cout<<"\t\tMenu \n";
      int num=write(f1,c,sizeof(Customer));
      close(f1);
      f1 = open ("npipe",O_RDONLY);
      int num1=read(f1,menu,5*sizeof(Menu));
      close(f1);
      for(int i=0;i<5;i++)
      {
          cout<<menu[i].name_dish<<"\t\t"<<menu[i].price<<"\t\t"<<menu[i].time<<"minutes"<<endl;
          
      }
      int of=open("opipe",O_WRONLY);
      for(int i=0;i<5;i++)
      {
          cout<<"Enter the quantity for : "<<menu[i].name_dish<<" = ";
          cin>>O1->quantity[i];

      }
      write(of,O1,sizeof(order));
      cin.ignore();
      close(of);
      pthread_exit(NULL);
}


int main()
{
    int num_customer=0;
    cout<<"Enter the number of customers :\n";
    cin>>num_customer;
    
    if ( mkfifo("npipe",0666) < 0)
    {
        perror ("Could not create pipe");
    }
    if ( mkfifo("opipe",0666) < 0)
    {
        perror ("Could not create pipe");
    }
    pthread_t *c=new pthread_t[num_customer]();
    

    for(int i=0;i<num_customer;i++)
    {
        pthread_create(&c[i],NULL,&customerEntry,NULL);
        pthread_join(c[i],NULL);
    }
      
  
}
