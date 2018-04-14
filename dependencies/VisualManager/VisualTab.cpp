/**************************************************************************
	created		:	2011-07-08
	filename	: 	VisualTab.cpp
	author		:	Xebeth`
	copyright	:	North Edge (2012)
	purpose		:	Container class for Visual tabs (TabHeader + TabPage)
**************************************************************************/
#include "stdafx.h"
#include "VisualTab.h"

#include "TabHeader.h"
#include "TabPage.h"

/*! \brief VisualTab constructor
	\param[in] TabIndex_in : the index of the tab
	\param[in] TabHeaderID_in : the resource ID of the tab header
	\param[in] TabPageID_in : the resource ID of the tab page
*/
VisualTab::VisualTab(UINT TabIndex_in, UINT TabHeaderID_in, UINT TabPageID_in)
	: m_HeaderResID(TabHeaderID_in), m_PageResID(TabPageID_in),
	  m_TabIndex(TabIndex_in), m_pTabHeader(nullptr), m_pTabPage(nullptr) {}

//! \brief VisualTab destructor
VisualTab::~VisualTab()
{
	if (m_pTabPage != nullptr)
	{
		delete m_pTabPage;
		m_pTabPage = nullptr;
	}

	if (m_pTabHeader != nullptr)
	{
		delete m_pTabHeader;
		m_pTabHeader = nullptr;
	}
}

//! \brief Updates the size of the header and page
void VisualTab::UpdateSize(void)
{
	CRect HeaderRect;

	if (m_pTabHeader != nullptr && ::IsWindow(m_pTabHeader->GetSafeHwnd())
	 && m_pTabPage != nullptr && ::IsWindow(m_pTabPage->GetSafeHwnd()))
	{
		m_pTabHeader->GetClientRect(HeaderRect);
		m_pTabPage->SetHeaderHeight(HeaderRect.Height() + 1);
		m_pTabPage->RecalcActiveTabBorder();
	}
}