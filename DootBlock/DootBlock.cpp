
// DootBlock.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DootBlock.h"
#include "DootBlockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDootBlockApp

BEGIN_MESSAGE_MAP(CDootBlockApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDootBlockApp construction

CDootBlockApp::CDootBlockApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDootBlockApp object

CDootBlockApp theApp;


// CDootBlockApp initialization

BOOL CDootBlockApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("DootBlock"));

	CDootBlockDlg dlg;
	
	if (dlg.Create(IDD_DOOTBLOCK_DIALOG))
	{
		dlg.ShowWindow(SW_HIDE);
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.RunModalLoop();
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return false so that we exit the
	//  application, rather than start the application's message pump.
	return false;
}

