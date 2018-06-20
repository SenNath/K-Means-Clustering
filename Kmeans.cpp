#include<iostream>
#include<fstream>
#include<cmath>
#include<stdio.h>
#include<cstring>
using namespace std;

int data(float ar[][10], int &np, int &nd,string str)
{
//To obtain data points from text file	
ifstream file;
file.open(str);

if (!file.is_open())
 return -1;

np=0,nd=0;
 
 while(!file.eof())
 { 
   for(int j=0;j<10 && !file.eof();j++)
     { 
      file>>ar[np][j];
      if(np==0)
       nd++;
      if(char(file.peek())=='\n')
         break;
      } 
   np++;
 }

file.close();
return 0;
}



 int dist(double eucdis[][50],float cent[][10],float ar[][10],int np,int nd,int nk)
{
//To find euclidean distace of all points from centroids of clusters.	
double d;
for(int k=0;k<nk;k++)
{
for(int i=0;i<np;i++)
{d=0;
 for(int j=0;j<nd;j++)
{
 	d+=pow((cent[k][j]-ar[i][j]),2);
}	
    eucdis[i][k] = sqrt(d);
}
}
return 0;
}	 


int cluster(double eucdis[][50],int clust[][50],int np,int nk)
{
//To find which point belongs to which cluster using 2d array(clust)	
double min;	
int k;
for(int i=0;i<np;i++)
{
	for(int j=0;j<nk;j++)
		clust[i][j]=0;

}
for(int i=0;i<np;i++)
{
k=0;
min=eucdis[i][0];

for(int j=0;j<nk;j++)
{
  if(eucdis[i][j]<min)
  	{
  		min=eucdis[i][j];
        k=j;
    }  
}
clust[i][k]=1;
}

return 0;
}


int newcent(float ar[][10],float cent[][10],int clust[][50],int np,int nd,int nk)
{   
//To find new centroid of the newly formed clusters.
	int s;
	for(int j=0;j<nk;j++)
	{ s=0;
		for(int i=0;i<np;i++)
		{

			if(clust[i][j]==1)
			{
			  s++;
			  for(int k=0;k<nd;k++)
			  {
			  	if(s==1)
			  	cent[j][k]=0;
			    cent[j][k]+=ar[i][k];

			  }
		    }

	    }
	    for(int k=0;k<nd;k++)
			  {
			  	cent[j][k]/=s;
			   }
     }return 0;
 }   


int kmeans(float ar[][10],int np,int nd,int nk,ofstream &file)
{
//Function that outputs k centroids of the final cluster in a text file.	
float cent[50][10];
double eucdis[1000][50];
int clust[1000][50];
int clust1[1000][50],maxitr=999;

for(int i=0;i<nk;i++)
{
 for(int j=0;j<nd;j++)
 {
 	cent[i][j]=ar[i][j];
  }
}

dist(eucdis,cent,ar,np,nd,nk);

cluster(eucdis,clust,np,nk);

for(int i = 0; i<np; i++)
{
  memcpy(&clust1[i], &clust[i], sizeof(clust[0]));
}

for(int i=0;i<maxitr;i++)
{
newcent(ar,cent,clust,np,nd,nk);
dist(eucdis,cent,ar,np,nd,nk);
cluster(eucdis,clust,np,nk);

if(memcmp(clust1, clust, sizeof(clust)) == 0)
	{
		for(int i=0;i<nk;i++)
       { 
         for(int j=0;j<nd;j++)
        {
 	     file<<cent[i][j]<<" ";
        }file<<endl;
       }
	break;
	}
for(int i = 0; i<np; i++)
{
    memcpy(&clust1[i], &clust[i], sizeof(clust[0]));
}

}return 0;
}		


int main()
{
float ar[1000][10];
string str;
int np=0,nd=0,nk;
//np- no of data points
//nd- dimension of points
//nk- no of clusters
cout<<endl<<"Enter filename";
cin>>str;
cout<<endl<<"Enter no of clusters";
cin>>nk;
ofstream file;
file.open ("clusters.txt");
data(ar,np,nd,str);
kmeans(ar,np,nd,nk,file);
file.close();
return 0;
}