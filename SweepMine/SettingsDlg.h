#pragma once


// CSettingsDlg dialog
#include "resource.h"
class CSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingsDlg)

public:
	enum DIFFICULTY
	{
		EASY = 0,
		MIDD,
		HARD,
		USER
	};
public:
	CSettingsDlg(int nWidth, int nHeight, int nMine, DIFFICULTY d, CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingsDlg();

// Dialog Data
	enum { IDD = IDD_SETTINGSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio40();
	afx_msg void OnBnClickedRadio99();
	afx_msg void OnBnClickedRadiox();
	virtual BOOL OnInitDialog();
public:
	int m_nDHeight;
	int m_nDWidth;
	int m_nDMine;
	DIFFICULTY m_iDifficulty;
	virtual void OnOK();
};
