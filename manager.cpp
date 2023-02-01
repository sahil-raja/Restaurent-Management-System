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

int main()
{
    if ( mkfifo("cpipe",0666) < 0)
    {
        perror ("Could not create pipe");
    }
    cout<<"Pipe created successfully \n ";
    int f1 = open ("npipe",O_RDONLY);
    Customer *c=new Customer();
    string arr[5]={{"Zinger"},{"Broast"},{"Fries"},{"Tikka"},{"Drink"}};
    int p[5]={200,350,100,250,50};
    int d[5]={15,20,5,10,2};
    Menu *menu=new Menu[5]();
    order *o1=new order();
    for(int i=0;i<5;i++)
    {
        strcpy(menu[i].name_dish,arr[i].c_str());
        menu[i].price=p[i];
        menu[i].time=d[i];
    }
    
    int oi=0;
    orderSeq *Seq=new orderSeq();
    while(1)
    {
        total_bill=0;
        f1 = open ("npipe",O_RDONLY);
        read(f1, c,sizeof(Customer));
        cout<<"Welcome to FAST DHABBA \nMr/Mrs : "<< (*c).name<<endl;
        cout<<"Your ID is : "<< (*c).id<<endl;
        close(f1);
        f1 = open ("npipe",O_WRONLY);
        int num1=write(f1,menu,5*sizeof(Menu));
        close(f1);

        int of = open ("opipe",O_RDONLY);
        read(of, o1,sizeof(order));
        for(int i=0;i<5;i++)
        {
            total_bill+=(o1->quantity[i])*menu[i].price;
        }
        total_Sales+=total_bill;
        Seq->obj.id=c->id;
        strcpy(Seq->obj.name,c->name);
        for(int i=0;i<5;i++)
        {    
            Seq->obj1.quantity[i]=o1->quantity[i];
        }
        cout<<"Order has been placed ! \n";
        cout<<"Your order is as follows :\n";
        cout<<"Name\t\tPrice\t\tQuantity\n";
        for(int i=0;i<5;i++)
        {
            strcpy(Seq->obj2[i].name_dish,menu[i].name_dish);
            Seq->obj2[i].price=menu[i].price;
            Seq->obj2[i].time=menu[i].time;
            cout<<Seq->obj2[i].name_dish<<"\t\t"<<Seq->obj2[i].price<<"\t\t"<<Seq->obj1.quantity[i]<<endl;
        }
        cout<<"Your total bill for the order is = "<<total_bill<<endl;
        cout<<"Total Sales of the day = "<<total_Sales<<endl;
        close(of);
	
        int cf=open("cpipe",O_WRONLY);
        write(cf,Seq,sizeof(orderSeq));
        close(cf);
    }
        
       
       
    
    

}
