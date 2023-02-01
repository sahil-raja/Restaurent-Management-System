#ifndef HEADER_H
#define HEADER_H
#include<string.h>
using namespace std;
int total_bill=0;
int total_Sales=0;
struct Customer
{
    int id;
    char name[50];
};

struct Menu
{
    char name_dish[20];
    int price;
    int time; 

};

struct order
{

    int quantity[5];
};

struct orderSeq
{
    Customer obj;
    order obj1;
    Menu obj2[5];
};


#endif
