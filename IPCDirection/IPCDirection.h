
// IPCDirection.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPCDirectionApp:
// �йش����ʵ�֣������ IPCDirection.cpp
//

class CIPCDirectionApp : public CWinAppEx
{
public:
	CIPCDirectionApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPCDirectionApp theApp;