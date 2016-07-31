// IOCPClient.h: interface for the IOCPClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOCPCLIENT_H__C96F42A4_1868_48DF_842F_BF831653E8F9__INCLUDED_)
#define AFX_IOCPCLIENT_H__C96F42A4_1868_48DF_842F_BF831653E8F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <WinSock2.h>
#include <Windows.h>
#include <MSTcpIP.h>
#include "Buffer.h"
#include "Manager.h"
#pragma comment(lib,"ws2_32.lib")

#define MAX_RECV_BUFFER  1024*8
#define MAX_SEND_BUFFER  1024*8 
#define FLAG_LENGTH    5
#define HDR_LENGTH     13
class IOCPClient  
{
public:
	IOCPClient();
	virtual ~IOCPClient();
	SOCKET   m_sClientSocket;

	HANDLE   m_hWorkThread;
	
	BOOL IOCPClient::ConnectServer(char* szServerIP, unsigned short uPort);
	static DWORD WINAPI WorkThreadProc(LPVOID lParam);


	VOID IOCPClient::OnServerReceiving(char* szBuffer, ULONG ulReceivedLength);
	int IOCPClient::OnServerSending(char* szBuffer, ULONG ulOriginalLength);
	BOOL IOCPClient::SendWithSplit(char* szBuffer, ULONG ulLength, ULONG ulSplitLength);

	BOOL IOCPClient::IsRunning()
	{
		return m_bIsRunning;
	}
	BOOL m_bIsRunning;

	CBuffer m_WriteBuffer;
	CBuffer m_CompressedBuffer;
	CBuffer m_DeCompressedBuffer;

	char    m_szPacketFlag[FLAG_LENGTH];

	VOID IOCPClient::setManagerCallBack(class CManager* Manager);
	HANDLE m_hEvent;

	VOID IOCPClient::Disconnect();
	void IOCPClient::RunEventLoop();

public:	
	class CManager* m_Manager; 

};

#endif // !defined(AFX_IOCPCLIENT_H__C96F42A4_1868_48DF_842F_BF831653E8F9__INCLUDED_)
