/*******************************************************************
Name : Rahul Krishna Dendukuri                          FALL 2015
Z-ID : Z1749863
Course : CSCI 580-02
Instructor : Harry Hutchins
TA : Sweta Thota
Program : Assignment 6
Desciption : A C++ program that simulates the FIFO and LRU page-replacement algorithms
Due Date : 11/16/2015
*********************************************************************/
#include "Assign6.h"
int notExist(int a,int* f,int size);
void printFrames(int* f,int size);
int getRepIndex(int* i,int size);
int notFull(int* f,int size);
/*
Function : Main
Paramenters : int argc - No. of command line arguments
              char **argv-Array of pointers for the the command line arguments
Returns : int
*********************************************************************/

int main(int argc,char** argv)
{

	int c=0;

  	if (argc!=2)//Checking if right number of command line arguments have been entered while executing the program
        {

        	        cerr<<"usage:_"<<argv[0]<<"_inputFile\n"; //Printing out the error message with correct usage of the Program
               		 return 0;
        }
	ifstream In;
	In.open(argv[1]);//Opening the file
	if(In==NULL)
	{//error message if not able to load the file
		cerr<<"File not found"<<endl;
		exit(0);
	}
	string trans;
	In>>trans;
	int a[20];
	int n;
	int k;
	int i=0;
	int j=0;
	int pf;
         while (trans != "?")
         {//Loading untill ? is reached in the file
		In>>n;//the number of pages in the process
		In>>k;//the frame size of the memory
		int b[k];//array to keep track of the page usage by the memory
		int f[k];
		cerr<<"Paging for a process begins"<<endl;
		if(trans=="F")
			cerr<<"The algorithm chosen for the process is FIFO"<<endl;
		else
			cerr<<"The algorithm choen is Least-Replacement"<<endl;
		cerr<<"The number of pages: "<<n<<endl;
		cerr<<"The size of frame stack: "<<k<<endl;
		for(i=0;i<20;i++)
	 		In>>a[i];//Loading the page numbers into an array
		for(i=0;i<k;i++)
                        f[i]=-1;//intializinf the frame array to -1 tom indicate emptiness
		i=0;//index for the page table
		j=0;//index for the reference string array
		pf=0;//page fault counter of a process
		if(trans=="F")
		{//FIFO algorithm
			
			do
			{
				
				if(!notExist(a[j],f,k))
				{//If the page already exists among the frames loaded into memory
					   cerr<<"Page :"<<a[j]<<endl;
					 cerr<<"Page Fault: No"<<endl;
                                        printFrames(f,k);
                                        
				}
				else if(notFull(f,k) && notExist(a[j],f,k))
				{//if the the page doesnt exist in the page table and there is still place to load a new page
					 cerr<<"Page :"<<a[j]<<endl;
					 cerr<<"Page Fault: Yes"<<endl;
					b[i]=j;//initializing the First-in order of the page in the page table
					f[i++]=a[j];
					printFrames(f,k);
					pf++;//incrementing page fault count
				}
				else if(notExist(a[j],f,k))
				{//if the page doesnt exist and a page-needs to be relaced fron the table
						
					 cerr<<"Page :"<<a[j]<<endl;
                       			 cerr<<"Page Fault: Yes"<<endl;
					
					i= getRepIndex(b,k);//getting the index of the page that needs to be replaced
					 b[i]=j;//reinitializing the order 
					f[i++]=a[j];//replacing the existing page number
                                        printFrames(f,k);
					pf++;
				}
			
			}while(a[++j]!=-1);   
		}
		else if(trans=="L")
		{//LRU algorithm
			int ts=0;//time stamp
			 do
                        {
  
                                if(!notExist(a[j],f,k))
                                {//if the page already exists in memory
                                           cerr<<"Page :"<<a[j]<<endl;
					 cerr<<"Page Fault: No"<<endl;
					int h=0;
					while(f[h]!=a[j])//looking up the index of the page
						h++;
					b[h]=ts;//loading the latest usage time stamp to the page
                                        printFrames(f,k);
                                        cerr<<"Page Fault: No"<<endl;
                                }
                                else if(notFull(f,k) && notExist(a[j],f,k))
                                {//the page table is not full and needs to be loaded
                                         cerr<<"Page :"<<a[j]<<endl;
					 cerr<<"Page Fault: Yes"<<endl;
                                        b[i]=ts;//loading the timestamp
                                        f[i++]=a[j];//loading the page
                                        printFrames(f,k);
					pf++;
                                }
                                else if(notExist(a[j],f,k))
                                {//when existing page needs to be replaced
                                        
                                         cerr<<"Page :"<<a[j]<<endl;
					 cerr<<"Page Fault: Yes"<<endl;
                                        i= getRepIndex(b,k);//getting the least recently used page index
                                         b[i]=ts;
                                        f[i++]=a[j];
                                        printFrames(f,k);
					pf++;
                                }
				ts++;//incementing the time
                        }while(a[++j]!=-1);//the termination the reference string

		}
		else
		{
			cerr<<"Wrong Algorithm being used";
			exit(0);
		}
		cerr<<"End of process"<<endl;
		 cerr<<"In "<<j<<" Steps,we had "<<pf<<" Page faults"<<endl<<endl;

		In>>trans;
		
         }
        In.close();//closing file
	

	
	return 0;	
}
/*
Function : notExist
Paramenters : int  a - The page number that needs to be checked 
	      int* f - Pointer to the array of frames in memory
	      int size - The sizr of the above array
Description: This function checks if a page exists in the page table              
Returns :int
*********************************************************************/

int notExist(int a,int* f,int size)
{
	int i;
	int j=1;
	for(i=0;i<size;i++)
	{
		if(f[i]==a)//matching the page
			j=0;
	}
	return j;
		
}
/*
Function : printFrames
Paramenters :
              int* f - Pointer to the array of frames in memory
              int size - The sizr of the above array
Description: This function prints the frames references by the array.
Returns :void
*********************************************************************/

void printFrames(int* f,int size)
{
	int l;
	for ( l=0;  l < size;  l++ )
		cerr<<"Frame["<<l<<"]"<<"\t";
	cerr<<endl;
	 for ( l=0;  l < size;  l++ )
                cerr<<f[l]<<" \t\t";
	cerr<<endl;
}

/*
Function : getRepIndex
Paramenters :
              int* b - Pointer to the array thst keeps track of the history of the pages in memory
              int size - The sizr of the above array
Description: This function returns the index of the page which is elibible for replacement.This function works with both the algorithms because of the way we use the histoory array.
Returns :int
*********************************************************************/

int getRepIndex(int* b,int size)
{
	 int smallest = b[0] ;
	int i;
	int j=0;//variable for the index with smallest element
    for ( i=1;  i < size;  ++i )//loop for finding the smallest element in the array
        if ( b[i] < smallest )
	{
	     j=i;//updating with the current smallest index
             smallest = b[i] ;
	}

	return j;
	

	
} 
/*
Function : notFull
Paramenters :
              int* f - Pointer to the array of frames in memory
              int size - The sizr of the above array
Description: This function checks whether the array is full and returns 1 if yesa and 0 otherwise
Returns :int
*********************************************************************/

int notFull(int* f,int k)
{
	int i;
	int j=0;
	for(i=0;i<k;i++)
		if(f[i]==-1)
			j=1;
	return j;


	
}

