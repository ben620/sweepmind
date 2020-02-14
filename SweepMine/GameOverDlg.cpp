// GameOverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameOverDlg.h"
#include "afxdialogex.h"


// CGameOverDlg dialog

IMPLEMENT_DYNAMIC(CGameOverDlg, CDialog)

CGameOverDlg::CGameOverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameOverDlg::IDD, pParent)
{

}

CGameOverDlg::~CGameOverDlg()
{
}

void CGameOverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameOverDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CGameOverDlg::OnBnClickedBtnQuit)
	ON_BN_CLICKED(IDC_BTN_RETRY, &CGameOverDlg::OnBnClickedBtnRetry)
	ON_BN_CLICKED(IDC_BTN_NEW, &CGameOverDlg::OnBnClickedBtnNew)
END_MESSAGE_MAP()


// CGameOverDlg message handlers


void CGameOverDlg::OnBnClickedBtnQuit()
{
	m_iGameState = QUIT_GAME;
	OnOK();
}


void CGameOverDlg::OnBnClickedBtnRetry()
{
	m_iGameState = RETRY_GAME;
	OnOK();
}


void CGameOverDlg::OnBnClickedBtnNew()
{
	m_iGameState = NEW_GAME;
	OnOK();
}
