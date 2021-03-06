
// DootBlockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DootBlock.h"
#include "DootBlockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDootBlockDlg dialog



CDootBlockDlg::CDootBlockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DOOTBLOCK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDootBlockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDootBlockDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_COMMAND(ID_TRAY_EXIT, OnMenuExit)
	ON_COMMAND(ID_TRAY_LOCK, OnMenuLock)
	ON_COMMAND(ID_TRAY_OPTIONS, OnMenuOptions)
	ON_COMMAND_RANGE(ID_PROFILES_START, ID_PROFILES_END, OnMenuProfileChange)
	ON_BN_CLICKED(IDOK, &CDootBlockDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDootBlockDlg message handlers

void CDootBlockDlg::CustomizeTrayMenu(CMenu& Menu_in_out)
{
	CMenu *pSubMenu = Menu_in_out.GetSubMenu(0);

	if (pSubMenu != nullptr)
	{
		CMenu *pProfilesMenu = pSubMenu->GetSubMenu(2);

		if (pProfilesMenu != nullptr)
		{
			int itemCount = pProfilesMenu->GetMenuItemCount();

			for (int i = 0; i < itemCount; ++i)
			{
				pProfilesMenu->DeleteMenu(i, MF_BYPOSITION);
			}
		}

		pSubMenu->EnableMenuItem(ID_TRAY_LOCK, m_bLocked);
	}
}

BOOL CDootBlockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, true);			// Set big icon
	SetIcon(m_hIcon, false);		// Set small icon

	SetWindowPos(NULL, -1000, -1000, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
		
	m_TrayIcon.Create(this, WM_ICON_NOTIFY, _T("Doot Block"), m_hIcon, IDR_TRAY_MENU);
	m_TrayIcon.SetCustomizeMenuCallback(std::bind(&CDootBlockDlg::CustomizeTrayMenu, this, std::placeholders::_1));

	return true;  // return true  unless you set the focus to a control
}

void CDootBlockDlg::OnDestroy()
{
	CDialog::OnDestroy();
	CSystemTray::MinimiseToTray(this);
}

void CDootBlockDlg::OnMenuLock()
{
	m_bLocked = true;

	m_TrayIcon.SetIcon(IDI_SAD);
}

void CDootBlockDlg::OnMenuExit()
{
	m_bClosing = true;
	PostQuitMessage(0);
}

void CDootBlockDlg::OnMenuProfileChange(UINT commandID)
{
	m_SelectedProfile = commandID - ID_PROFILES_START;
}

void CDootBlockDlg::OnMenuOptions()
{
	CenterWindow();
	ShowWindow(SW_SHOW);
	CSystemTray::MaximiseFromTray(this);
}

void CDootBlockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	static bool Minimized = false;
	bool previous = Minimized;

	if (nID == SC_MINIMIZE)
		Minimized = true;
	else if (nID == SC_RESTORE)
		Minimized = false;

	CDialog::OnSysCommand(nID, lParam);

	if (previous != Minimized) 
	{
		if (Minimized)
			CSystemTray::MinimiseToTray(this);
		else
			CSystemTray::MaximiseFromTray(this);
	}

	CDialog::OnSysCommand(nID, lParam);
}

LRESULT CDootBlockDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(lParam) == WM_LBUTTONDBLCLK)
	{
		OnMenuLock();

		return 0L;
	}
	else
	{
		// Delegate all the work back to the default 
		// implementation in CSystemTray.
		return m_TrayIcon.OnTrayNotification(wParam, lParam);
	}
}

BOOL CDootBlockDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
		case WM_QUIT:
		case WM_CLOSE:
		case WM_DESTROY:
			if (m_bClosing == false)
			{
				CSystemTray::MinimiseToTray(this);

				return TRUE;
			}
			else
			{
				m_TrayIcon.RemoveIcon();
			}
		break;
	}

	return CWnd::PreTranslateMessage(pMsg);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDootBlockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDootBlockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDootBlockDlg::OnBnClickedOk()
{
	ShowWindow(SW_HIDE);
}
