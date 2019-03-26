#include <iostream>  //подключить файл iostream
#include <math.h>	 // подключить файл math.h
#include <stdlib.h>	 //подключить файл stdlib.h
#include <cstdlib>
#include <string.h>
#include <cstdio>
#include <cstring>



using namespace std;

struct worker 
{
	char fio[25];
	char init[4];
	char rank[25];
	int data[2],srok,pay;
}rab[9];


int main()
{
	system("color f0");
	int n;
	cout<<"Enter number of workers :"<<endl;
	cin>>n;
	for(int i=0;i<n;i++)
		{
			cout<<"Enter surname of the worker: ";
			cin>>rab[i].fio;
			
			cout<<"Enter initials of the worker: ";
			cin>>rab[i].init;
			cin.clear();
			cout<<"Enter rank of the worker: ";
			cin>>rab[i].rank;
			cout<<"Enter data of contract: ";
				for(int j=0;j<3;j++)
					{
						cin>>rab[i].data[j];					
					}			
			cout<<"Enter term of contract: ";
			cin>>rab[i].srok;
			cout<<"Enter payment of the worker: ";
			cin>>rab[i].pay;
		}	
		
for(int i=0;i<n;i++)
		{
			if(rab[i].data[1]<6 && rab[i].srok+rab[i].data[2]<20)
			{
				cout<<"Worker`s name is:"<<rab[i].fio<<' '<<rab[i].init<<endl;
				cout<<"Worker`s rank is:"<<rab[i].rank<<endl;
				cout<<"Worker`s data of signaturing the contract is:";
					for(int j=0;j<3;j++)
					{
						cout<<rab[i].data[j]<<'.';
					}
				cout<<endl<<"Worker`s term of contract is:"<<rab[i].srok<<endl;
				cout<<"Payment of the worker is:"<<rab[i].pay<<endl;
		
			}
		}
		system("pause");
		return 0;
}
