/////////////////////////////////////////////////////////////////////////////
// SystemTray.h : header file
//
// Written by Chris Maunder (cmaunder@mail.com)
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// This file is provided "as is" with no expressed or implied warranty.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 

#ifndef _INCLUDED_SYSTEMTRAY_H_
#define _INCLUDED_SYSTEMTRAY_H_

#ifdef NOTIFYICONDATA_V1_SIZE   // If NOTIFYICONDATA_V1_SIZE, then we can use fun stuff
#define SYSTEMTRAY_USEW2K
#else
#define NIIF_NONE 0
#endif

// #include <afxwin.h>
#include <afxtempl.h>
#include <afxdisp.h>    // COleDateTime

/////////////////////////////////////////////////////////////////////////////
// CSystemTray window

typedef std::function<void(CMenu&)> fnCustomizeMenuCallback_t;

class CSystemTray : public CWnd
{
// Construction/destruction
public:
    CSystemTray();
    CSystemTray(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID, 
                bool bhidden = false,
                LPCTSTR szBalloonTip = nullptr, LPCTSTR szBalloonTitle = nullptr, 
                DWORD dwBalloonIcon = NIIF_NONE, UINT uBalloonTimeout = 10);
    virtual ~CSystemTray();

    DECLARE_DYNAMIC(CSystemTray)

// Operations
public:
    bool Enabled() { return m_bEnabled; }
    bool Visible() { return !m_bHidden; }

    // Create the tray icon
    bool Create(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID,
                bool bHidden = false,
                LPCTSTR szBalloonTip = nullptr, LPCTSTR szBalloonTitle = nullptr, 
                DWORD dwBalloonIcon = NIIF_NONE, UINT uBalloonTimeout = 10);

    // Change or retrieve the Tooltip text
    bool    SetTooltipText(LPCTSTR pszTooltipText);
    bool    SetTooltipText(UINT nID);
    CString GetTooltipText() const;

    // Change or retrieve the icon displayed
    bool  SetIcon(HICON hIcon);
    bool  SetIcon(LPCTSTR lpszIconName);
    bool  SetIcon(UINT nIDResource);
    bool  SetStandardIcon(LPCTSTR lpIconName);
    bool  SetStandardIcon(UINT nIDResource);
    HICON GetIcon() const;

    void  SetFocus();
    bool  HideIcon();
    bool  ShowIcon();
    bool  AddIcon();
    bool  RemoveIcon();
    bool  MoveToRight();

    bool ShowBalloon(LPCTSTR szText, LPCTSTR szTitle = nullptr,
                     DWORD dwIcon = NIIF_NONE, UINT uTimeout = 10);

    // For icon animation
    bool  SetIconList(UINT uFirstIconID, UINT uLastIconID); 
    bool  SetIconList(HICON* pHIconList, UINT nNumIcons); 
    bool  Animate(UINT nDelayMilliSeconds, int nNumSeconds = -1);
    bool  StepAnimation();
    bool  StopAnimation();

	// menu customization callback
	void SetCustomizeMenuCallback(fnCustomizeMenuCallback_t callback);

    // Change menu default item
    void GetMenuDefaultItem(UINT& uItem, bool& bByPos);
    bool SetMenuDefaultItem(UINT uItem, bool bByPos);

    // Change or retrieve the window to send notification messages to
    bool  SetNotificationWnd(CWnd* pNotifyWnd);
    CWnd* GetNotificationWnd() const;

    // Change or retrieve the window to send menu commands to
    bool  SetTargetWnd(CWnd* pTargetWnd);
    CWnd* GetTargetWnd() const;

    // Change or retrieve  notification messages sent to the window
    bool  SetCallbackMessage(UINT uCallbackMessage);
    UINT  GetCallbackMessage() const;

    UINT_PTR GetTimerID() const   { return m_nTimerID; }

// Static functions
public:
    static void MinimiseToTray(CWnd* pWnd, bool bForceAnimation = false);
    static void MaximiseFromTray(CWnd* pWnd, bool bForceAnimation = false);

public:
    // Default handler for tray notification message
    virtual LRESULT OnTrayNotification(WPARAM uID, LPARAM lParam);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSystemTray)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
    void Initialise();
    void InstallIconPending();

	virtual void CustomizeMenu(CMenu&);	// Used for customizing the menu

// Implementation
protected:
    NOTIFYICONDATA  m_tnd;
    bool            m_bEnabled;         // does O/S support tray icon?
    bool            m_bHidden;          // Has the icon been hidden?
    bool            m_bRemoved;         // Has the icon been removed?
    bool            m_bShowIconPending; // Show the icon once tha taskbar has been created
    bool            m_bWin2K;           // Use new W2K features?
	CWnd*           m_pTargetWnd;       // Window that menu commands are sent

    CArray<HICON, HICON> m_IconList;
    UINT_PTR     m_uIDTimer;
    INT_PTR      m_nCurrentIcon;
    COleDateTime m_StartTime;
    UINT         m_nAnimationPeriod;
    HICON        m_hSavedIcon;
    UINT         m_DefaultMenuItemID;
    bool         m_DefaultMenuItemByPos;
	UINT         m_uCreationFlags;

	fnCustomizeMenuCallback_t m_fnCustomizeMenuCallback = nullptr;

// Static data
protected:
    static bool RemoveTaskbarIcon(CWnd* pWnd);

    static const UINT m_nTimerID;
    static UINT  m_nMaxTooltipLength;
    static const UINT m_nTaskbarCreatedMsg;
    static CWnd  m_wndInvisible;

    static bool GetW2K();
#ifndef _WIN32_WCE
    static void GetTrayWndRect(LPRECT lprect);
    static bool GetDoWndAnimation();
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CSystemTray)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
#ifndef _WIN32_WCE
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
#endif
    LRESULT OnTaskbarCreated(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
};


#endif

/////////////////////////////////////////////////////////////////////////////
