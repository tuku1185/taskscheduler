// MyTaskDemoDlg.h : header file
//

#if !defined(AFX_MYTASKDEMODLG_H__A9F4F01D_60BE_4BC2_A615_E618768ECD3F__INCLUDED_)
#define AFX_MYTASKDEMODLG_H__A9F4F01D_60BE_4BC2_A615_E618768ECD3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyTaskDemoDlg dialog

class CMyTaskDemoDlg : public CDialog
{
// Construction
public:
	CMyTaskDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyTaskDemoDlg)
	enum { IDD = IDD_MYTASKDEMO_DIALOG };
	CString	m_sUserName;
	CString	m_sTaskName;
	CTime	m_dStartTime;
	CTime	m_dStartDate;
	BOOL	m_bReplace;
	CString	m_sProgram;
	CString	m_sPath;
	CString	m_sPassword;
	CString	m_sParameters;
	int		m_iFreq;
	CTime	m_dEndDate;
	CString	m_sComment;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTaskDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyTaskDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddTask();
	afx_msg void OnDeleteTask();
	afx_msg void OnBrowseProgram();
	afx_msg void OnBrowsePath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTASKDEMODLG_H__A9F4F01D_60BE_4BC2_A615_E618768ECD3F__INCLUDED_)
