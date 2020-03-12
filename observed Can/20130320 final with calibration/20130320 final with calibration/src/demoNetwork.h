#include <Ogre.h>
#include <winsock2.h>
#include <process.h>
#include <windows.h>
#include <ws2tcpip.h>
extern float *values;
extern CRITICAL_SECTION cs;
extern bool isStarted;

class DemoNet{
	public:
		
		DemoNet();
		~DemoNet(void);		
		float* getSocketValue();
		void endNetwork();
		void sendData();		
		
};