#include "demoNetwork.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <deque>
using namespace std;
void Thread( void* pParams );
CRITICAL_SECTION cs;

float *values=new float();
bool isStarted = true; 
int iResult;

//----------------------------Create the network--------------------------
DemoNet::DemoNet(){
	

	InitializeCriticalSection( &cs );
	_beginthread(Thread,0,NULL);
}


//----- Added a thread to receive data infinitely --------------------------
void Thread( void* pParams ){

	 
	float val[20];

	char INBUFFER[500];
	char SAVEBUFFER[50];
	int inbuffercount,savebuffercount;

    char OUTBUFFER[20];

    DWORD        bytes_read    = 50;    // Number of bytes read from port
    DWORD        bytes_written = 0;    // Number of bytes written to the port
    HANDLE       comport      = NULL;  // Handle COM port
 int   bStatus;
    DCB          comSettings;          // Contains various port settings
    COMMTIMEOUTS CommTimeouts;
    strcpy(&OUTBUFFER[0], "The quick brown fox jumped over the lazy dog. \n\r\0");
    // Open COM port
    if ((comport = 
         CreateFile("\\\\.\\COM1",                // open com5:
                    GENERIC_READ | GENERIC_WRITE, // for reading and writing
                    0,                            // exclusive access
                    NULL,                         // no security attributes
                    OPEN_EXISTING,              
                    FILE_ATTRIBUTE_NORMAL,
                    NULL)) == INVALID_HANDLE_VALUE)
    {
        // error processing code goes here
    }
    // Set timeouts in milliseconds
    CommTimeouts.ReadIntervalTimeout         = 0; 
    CommTimeouts.ReadTotalTimeoutMultiplier  = 0; 
    CommTimeouts.ReadTotalTimeoutConstant    = 100;
    CommTimeouts.WriteTotalTimeoutMultiplier = 0;
    CommTimeouts.WriteTotalTimeoutConstant   = 100;
    bStatus = SetCommTimeouts(comport,&CommTimeouts);
    if (bStatus != 0)
    {
        // error processing code goes here
    }

    GetCommState(comport, &comSettings);
    comSettings.BaudRate = 9600;
    comSettings.StopBits = ONESTOPBIT;
    comSettings.ByteSize = 8;
    comSettings.Parity   = NOPARITY;
    comSettings.fParity  = FALSE;
    bStatus = SetCommState(comport, &comSettings);
    if (bStatus == 0)
    {
        // error processing code goes here
    }
	while(true){

        if (bStatus != 0)
        {
            // error processing code here
        }
        bStatus = ReadFile(comport,   // Handle
                &INBUFFER,            // Incoming data
                500,                  // Number of bytes to read
                &bytes_read,          // Number of bytes read
                NULL);
        if (bStatus != 0)
        {
            // error processing code goes here
        }
	
	 /*deque<char> mydeque;
	 mydeque.push_back ('c');
	 mydeque.push_back ('h');
     mydeque.push_back ('a');

	 cout << "kkkkkk:";
	  while (!mydeque.empty())
    {
    std::cout << ' ' << mydeque.front();
    mydeque.pop_front();
	cout << "\nooooooo" << char(mydeque.size()) << '\n';
    }

  cout << "Popping out the elements in mydeque:";
  cout << "\nThe final size of mydeque is " << char(mydeque.size()) << '\n';
  */
/*deque<char> qD;
	qD.push_back('a');
	qD.push_back('o');
	qD.push_back('s');
	qD.push_back('d');
	qD.push_back('f');
	qD.push_back('g');
	qD.push_back('h');
	qD.push_back('i');

	// Output the entries after push_back()
	deque<char>::iterator qIter;
	for (qIter = qD.begin(); qIter != qD.end(); ++qIter) {
		//cout << *qIter;
	}
*/	
	static float ShipK,ShipI,ShipL,ShipJ,GunUpT,GunDownG,GunRightH,GunLeftB,GunShot1;                //k=GunShot1
	
	//printf("!!!!!!!! I'm in thread \n");
	//cout<<".................."<<bytes_read<<"......"<<INBUFFER[1]<<endl;

inbuffercount=0;

	do{
	inbuffercount++;
	if(inbuffercount>bytes_read){break;}
	}while(INBUFFER[inbuffercount]!='$');


if(INBUFFER[inbuffercount]=='$'){
savebuffercount=0;

	 do{
		 SAVEBUFFER[savebuffercount]=INBUFFER[inbuffercount];
		 savebuffercount++;
		 inbuffercount++;
		 if(inbuffercount>bytes_read){break;}
	 }while(INBUFFER[inbuffercount]!='\n');


if(INBUFFER[inbuffercount]=='\n'){
SAVEBUFFER[savebuffercount]='\0';
}
}
int i=0;
//cout<<"%%%%%%%%%%%%%%%%%.........."<<SAVEBUFFER<<endl;
char *pch;
pch=strtok(SAVEBUFFER,"$,");
//cout<<"%%%%%%%%%%%%%%%%%.........."<<pch<<endl;
val[i]=atof(pch);
    pch=strtok(NULL,",");
	//cout<<"%%%%%%%%%%%%%%%%%.........."<<pch<<endl;
	val[i+1]=atof(pch);
	pch=strtok(NULL,",");
	//cout<<"%%%%%%%%%%%%%%%%%.........."<<pch<<endl;
val[i+2]=atof(pch);
	pch=strtok(NULL,",");
	//cout<<"%%%%%%%%%%%%%%%%%.........."<<pch<<endl;
	val[i+3]=atof(pch);
	pch=strtok(NULL,",");
	//cout<<"%%%%%%%%%%%%%%%%%.........."<<pch<<endl;
	val[i+4]=atof(pch);

/*for(int i=0;i<=3;i++){
	if(pch='\0')break;
	pch=strtok(NULL,",");
	cout<<"%%%%%%%%%%%%%%%%%.........."<<pch<<endl;
	GunShot1=atof(pch);

}*/


EnterCriticalSection( &cs );
			isStarted = true; 
			//float a=val;
			values = val;
LeaveCriticalSection( &cs );

	
	//ShipK = ShipI = ShipL = ShipJ = GunUpT = GunDownG = GunRightH = GunLeftB = GunShot1 =  0.0;
	//GunShot1=10;
	}
    } 
	
	//myfile.close();

//------------------------------------------------------------------------
void DemoNet::endNetwork(){
	
}

//------------------------------------------------------------------------
void DemoNet::sendData(){
	
}
//------------------------------------------------------------------------
DemoNet::~DemoNet(){
	
	
	Ogre::LogManager::getSingleton().logMessage("Closing connectiion");
	Ogre::LogManager::getSingleton().logMessage(" *********************************************");
}
float* DemoNet::getSocketValue(){
	if(isStarted != true){
		printf("Switching to another thread\n");
		SwitchToThread();} 
	//else{
		//sleep(3);
	 EnterCriticalSection( &cs );
	 float* a = values;
	 //printf("Get value\n");
	 LeaveCriticalSection( &cs );//}
	return a;
}