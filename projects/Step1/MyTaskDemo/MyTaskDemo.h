// MyTaskDemo.h : main header file for the MYTASKDEMO application
//

#if !defined(AFX_MYTASKDEMO_H__E9D25682_113A_48AE_ADD2_9A885C35BC06__INCLUDED_)
#define AFX_MYTASKDEMO_H__E9D25682_113A_48AE_ADD2_9A885C35BC06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyTaskDemoApp:
// See MyTaskDemo.cpp for the implementation of this class
//

class CMyTaskDemoApp : public CWinApp
{
public:
	CMyTaskDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTaskDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyTaskDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTASKDEMO_H__E9D25682_113A_48AE_ADD2_9A885C35BC06__INCLUDED_)
