#pragma once


// CGameOverDlg dialog
#include "resource.h"

class CGameOverDlg : public CDialog
{
	DECLARE_DYNAMIC(CGameOverDlg)

public:
	CGameOverDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGameOverDlg();

// Dialog Data
	enum { IDD = IDD_GAMEOVERDLG };
	enum {NEW_GAME, RETRY_GAME, QUIT_GAME};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnQuit();
	afx_msg void OnBnClickedBtnRetry();
	afx_msg void OnBnClickedBtnNew();

	int m_iGameState;
};
