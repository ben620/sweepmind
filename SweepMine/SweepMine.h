
// SweepMine.h : main header file for the SweepMine application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSweepMineApp:
// See SweepMine.cpp for the implementation of this class
//

class CSweepMineApp : public CWinApp
{
public:
	CSweepMineApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSweepMineApp theApp;
