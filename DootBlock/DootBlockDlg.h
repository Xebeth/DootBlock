
// DootBlockDlg.h : header file
//
#pragma once

#define	WM_ICON_NOTIFY			WM_APP+10

// CDootBlockDlg dialog
class CDootBlockDlg : public CDialogEx
{
// Construction
public:
	CDootBlockDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOOTBLOCK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CSystemTray m_TrayIcon;
	bool m_bClosing = false;
	bool m_bLocked = false;
	UINT m_SelectedProfile = 0;

	void CustomizeTrayMenu(CMenu& Menu_in_out);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnMenuLock();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuProfileChange(UINT commandID);
	afx_msg void OnMenuOptions();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
