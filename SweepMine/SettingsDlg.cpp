// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SettingsDlg.h"
#include "afxdialogex.h"


// CSettingsDlg dialog

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialogEx)

CSettingsDlg::CSettingsDlg(int nWidth, int nHeight, int nMine, DIFFICULTY d, CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingsDlg::IDD, pParent)
	, m_nDHeight(nWidth)
	, m_nDWidth(nHeight)
	, m_nDMine(nMine)
	, m_iDifficulty(d)
{

}

CSettingsDlg::~CSettingsDlg()
{
}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HEIGHT, m_nDHeight);
	DDV_MinMaxInt(pDX, m_nDHeight, 9, 24);
	DDX_Text(pDX, IDC_WIDTH, m_nDWidth);
	DDV_MinMaxInt(pDX, m_nDWidth, 9, 30);
	DDX_Text(pDX, IDC_EDIT_MINE, m_nDMine);
	DDV_MinMaxInt(pDX, m_nDMine, 10, 668);
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_10, &CSettingsDlg::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO_40, &CSettingsDlg::OnBnClickedRadio40)
	ON_BN_CLICKED(IDC_RADIO_99, &CSettingsDlg::OnBnClickedRadio99)
	ON_BN_CLICKED(IDC_RADIO_x, &CSettingsDlg::OnBnClickedRadiox)
END_MESSAGE_MAP()


// CSettingsDlg message handlers


void CSettingsDlg::OnBnClickedRadio10()
{
	((CEdit*)GetDlgItem(IDC_WIDTH))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_HEIGHT))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_MINE))->EnableWindow(false);
	m_iDifficulty = EASY;
}


void CSettingsDlg::OnBnClickedRadio40()
{
	((CEdit*)GetDlgItem(IDC_WIDTH))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_HEIGHT))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_MINE))->EnableWindow(false);
	m_iDifficulty = MIDD;
}


void CSettingsDlg::OnBnClickedRadio99()
{
	((CEdit*)GetDlgItem(IDC_WIDTH))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_HEIGHT))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_MINE))->EnableWindow(false);
	m_iDifficulty = HARD;
}


void CSettingsDlg::OnBnClickedRadiox()
{
	((CEdit*)GetDlgItem(IDC_WIDTH))->EnableWindow();
	((CEdit*)GetDlgItem(IDC_HEIGHT))->EnableWindow();
	((CEdit*)GetDlgItem(IDC_EDIT_MINE))->EnableWindow();
	m_iDifficulty = USER;
}


BOOL CSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CButton*)GetDlgItem(IDC_RADIO_40))->SetCheck(BST_CHECKED);
	((CEdit*)GetDlgItem(IDC_WIDTH))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_HEIGHT))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT_MINE))->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSettingsDlg::OnOK()
{
	CDialogEx::OnOK();
	if (m_iDifficulty == EASY)
	{
		m_nDHeight = 9;
		m_nDWidth  = 9;
		m_nDMine   = 10;
	}
	else if (m_iDifficulty == MIDD)
	{
		m_nDHeight = 16;
		m_nDWidth  = 16;
		m_nDMine   = 40;
	}
	else if (m_iDifficulty == HARD)
	{
		m_nDHeight = 16;
		m_nDWidth  = 30;
		m_nDMine   = 99;
	}
}
