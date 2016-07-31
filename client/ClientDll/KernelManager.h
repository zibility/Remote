// KernelManager.h: interface for the CKernelManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KERNELMANAGER_H__B1186DC0_E4D7_4D1A_A8B8_08A01B87B89E__INCLUDED_)
#define AFX_KERNELMANAGER_H__B1186DC0_E4D7_4D1A_A8B8_08A01B87B89E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Manager.h"

class CKernelManager : public CManager  
{
public:
	CKernelManager::CKernelManager(IOCPClient* ClientObject);
	virtual ~CKernelManager();
	VOID CKernelManager::OnReceive(PBYTE szBuffer, ULONG ulLength);

	HANDLE  m_hThread[0x1000];
	ULONG   m_ulThreadCount;
};

#endif // !defined(AFX_KERNELMANAGER_H__B1186DC0_E4D7_4D1A_A8B8_08A01B87B89E__INCLUDED_)
