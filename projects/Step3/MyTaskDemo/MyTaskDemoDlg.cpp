// MyTaskDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyTaskDemo.h"
#include "MyTaskDemoDlg.h"
#include "CTask.h"
#include <shlobj.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTaskDemoDlg dialog

CMyTaskDemoDlg::CMyTaskDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyTaskDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyTaskDemoDlg)
	m_sUserName = _T("");
	m_sTaskName = _T("");
	m_dStartTime = 0;
	m_dStartDate = 0;
	m_bReplace = FALSE;
	m_sProgram = _T("");
	m_sPath = _T("");
	m_sPassword = _T("");
	m_sParameters = _T("");
	m_iFreq = -1;
	m_dEndDate = 0;
	m_sComment = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyTaskDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyTaskDemoDlg)
	DDX_Text(pDX, IDC_USERNAME, m_sUserName);
	DDX_Text(pDX, IDC_TASKNAME, m_sTaskName);
	DDX_DateTimeCtrl(pDX, IDC_STARTTIME, m_dStartTime);
	DDX_DateTimeCtrl(pDX, IDC_STARTDATE, m_dStartDate);
	DDX_Check(pDX, IDC_REPLACETASK, m_bReplace);
	DDX_Text(pDX, IDC_PROGRAM, m_sProgram);
	DDX_Text(pDX, IDC_PATH, m_sPath);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_PARAMETERS, m_sParameters);
	DDX_Radio(pDX, IDC_ONCE, m_iFreq);
	DDX_DateTimeCtrl(pDX, IDC_ENDDATE, m_dEndDate);
	DDX_Text(pDX, IDC_COMMENT, m_sComment);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyTaskDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CMyTaskDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_TASK, OnAddTask)
	ON_BN_CLICKED(IDC_DELETE_TASK, OnDeleteTask)
	ON_BN_CLICKED(IDC_BROWSE_PROGRAM, OnBrowseProgram)
	ON_BN_CLICKED(IDC_BROWSE_PATH, OnBrowsePath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTaskDemoDlg message handlers

BOOL CMyTaskDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// ustaw kontrolki czasowe na biezacy czas i date

CTime timeCurr = CTime::GetCurrentTime();	

    m_dEndDate = timeCurr;
    m_dStartDate = timeCurr;
    m_dStartTime = timeCurr;

    m_iFreq = 0;                        // domyslnie na zero

    UpdateData ( FALSE );

    // pod windowsem 9x pola u¿ytkownik i haslo nie maja znaczenia
    if ( 0 != (GetVersion() & 0x80000000) )
        {
        GetDlgItem ( IDC_USERNAME )->EnableWindow ( FALSE );
        GetDlgItem ( IDC_PASSWORD )->EnableWindow ( FALSE );
        }

TCHAR   szBuf[64];
CString sTimeFormat;
CString sSearch;
int     nIndex;

//sprawdzamy format wyswietlania daty
    VERIFY ( ::GetLocaleInfo ( LOCALE_USER_DEFAULT, LOCALE_STIMEFORMAT,
                               szBuf, 64 ));

    sTimeFormat = szBuf;

    VERIFY ( ::GetLocaleInfo ( LOCALE_USER_DEFAULT, LOCALE_STIME, 
                               szBuf, 64 ));

	// szukamy sekund i usuwamy je
    sSearch = szBuf;
    sSearch += _T("ss");

    nIndex = sTimeFormat.Find ( sSearch );

    if ( -1 != nIndex )
        {
        sTimeFormat.Delete ( nIndex, sSearch.GetLength() );
        }
    else
        {
        sSearch = szBuf;
        sSearch += 's';

        nIndex = sTimeFormat.Find ( sSearch );
    
        if ( -1 != nIndex )
            {
            sTimeFormat.Delete ( nIndex, sSearch.GetLength() );
            }
        }

// ustaw format czasu
CDateTimeCtrl* pTimeCtl;

    pTimeCtl = static_cast<CDateTimeCtrl*>(GetDlgItem ( IDC_STARTTIME ));

    pTimeCtl->SetFormat ( sTimeFormat );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyTaskDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyTaskDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyTaskDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyTaskDemoDlg::OnAddTask() 
{
CTask task;
CDateTimeCtrl* pEndDateCtrl;
SYSTEMTIME     stBegin;
SYSTEMTIME     stEnd;

    UpdateData();

//ustawiamy parametry
    task.SetProgram     ( m_sProgram );
    task.SetParameters  ( m_sParameters );
    task.SetStartingDir ( m_sPath );
    task.SetAccountName ( m_sUserName );
    task.SetPassword    ( m_sPassword );
    task.SetComment     ( m_sComment );

    m_dStartDate.GetAsSystemTime ( stBegin );

    stBegin.wHour   = m_dStartTime.GetHour();
    stBegin.wMinute = m_dStartTime.GetMinute();

    task.SetStartDateTime ( stBegin );

    // sprawdzamy, czy checkbox w koncowej dacie jest zaznaczony jest checkbox
    pEndDateCtrl = static_cast<CDateTimeCtrl*>( GetDlgItem ( IDC_ENDDATE ));

    if ( GDT_NONE != pEndDateCtrl->GetTime ( &stEnd ) )
        {
        task.SetEndDate ( m_dEndDate );
        }


    switch ( m_iFreq )
        {
        case 0: task.SetFrequency ( CTask::freqOnce ); break;
        case 1: task.SetFrequency ( CTask::freqDaily ); break;
        case 2: task.SetFrequency ( CTask::freqWeekly ); break;
        case 3: task.SetFrequency ( CTask::freqMonthly ); break;
        
        DEFAULT_UNREACHABLE;
        }

    if ( S_OK == task.SaveTask ( m_sTaskName, !m_bReplace ))
        {
        AfxMessageBox ( _T("Success!!") );
        }
    else
        {
        AfxMessageBox ( _T("Failed - see the debug output for error messages."), MB_ICONEXCLAMATION );
        }
	
}

void CMyTaskDemoDlg::OnDeleteTask() 
{
UpdateData();

//probujemy usunac zadanie
    if ( S_OK == CTask::DeleteTask ( m_sTaskName ) )
        {
        AfxMessageBox ( _T("Success!!") );
        }
    else
        {
        AfxMessageBox ( _T("Failed - see the debug output for error messages."), MB_ICONEXCLAMATION );
        }
	
}

void CMyTaskDemoDlg::OnBrowseProgram() 
{
CFileDialog dlg ( TRUE, _T("exe"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                  _T("Programs (*.exe,*.com,*.bat)|*.exe;*.com;*.bat|All Files (*.*)|*.*|"),
                  this );

    if ( IDOK == dlg.DoModal() )
        {
        UpdateData();
        m_sProgram = dlg.GetPathName();
        UpdateData ( FALSE );
        }
	
}

void CMyTaskDemoDlg::OnBrowsePath() 
{
BROWSEINFO   bi;
TCHAR        szName [MAX_PATH];
LPITEMIDLIST pidl;

    ZeroMemory ( &bi, sizeof(BROWSEINFO) );

    bi.hwndOwner = GetSafeHwnd();
    bi.lpszTitle = _T("Select the starting directory.");
    bi.pszDisplayName = szName;
    bi.ulFlags = BIF_RETURNONLYFSDIRS;

    pidl = SHBrowseForFolder ( &bi );

    if ( NULL != pidl )
        {
        VERIFY ( SHGetPathFromIDList ( pidl, szName ));

        UpdateData();
        m_sPath = szName;
        UpdateData ( FALSE );
        }
	
}
