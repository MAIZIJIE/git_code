
// MAIKE_ROBOT.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMAIKE_ROBOTApp:
// �йش����ʵ�֣������ MAIKE_ROBOT.cpp
//

class CMAIKE_ROBOTApp : public CWinApp
{
public:
	CMAIKE_ROBOTApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMAIKE_ROBOTApp theApp;