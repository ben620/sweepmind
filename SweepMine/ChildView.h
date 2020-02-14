
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "MineData.h"
#include "SettingsDlg.h"

#define UM_UPDATE_MINE (WM_USER+1)
#define UM_UPDATE_TIME (WM_USER+2)

// CChildView window

class CChildView : public CWnd
{
	enum GAME_SATE
	{
		STATE_NORMAL = 1,
		STATE_WIN,
		STATE_FAIL
	};
public:
	CChildView();
	void GameOver(void);
	void GameWin(void);
private:
	CMineData  m_data;
	CBitmap    m_bmpMine;
	CBitmap    m_bmpFlag;
	CBitmap    m_bmpQuestion;
	COLORREF   m_arrDigitColor[8];
	CRect      m_rcPaintArea;
	GAME_SATE  m_iGameState;
	int        m_nMineCount;
	int        m_nTimer;
	bool       m_bTimerOn;
	CSettingsDlg::DIFFICULTY m_iDifficulty;

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void PaintGame(CDC *pDC);
	void PaintGameOver(CDC *pDC);
	void PaintGameWin(CDC *pDC);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileNewgame();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL DestroyWindow();
	afx_msg void OnFileSettings();
};

