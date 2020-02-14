
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "SweepMine.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
	: m_iGameState(STATE_NORMAL)
	, m_bTimerOn(false)
	, m_iDifficulty(CSettingsDlg::MIDD)
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_NEWGAME, &CChildView::OnFileNewgame)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_SETTINGS, &CChildView::OnFileSettings)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);

	switch (m_iGameState)
	{
	case STATE_NORMAL:
		PaintGame(&dc);
		break;
	case STATE_WIN:
		PaintGameWin(&dc);
		break;
	case STATE_FAIL:
		PaintGameOver(&dc);
		break;
	}
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_bmpMine.LoadBitmap(IDB_BITMAP_MINE);
	m_bmpFlag.LoadBitmap(IDB_BITMAP_FLAG);
	m_bmpQuestion.LoadBitmap(IDB_BITMAP_QUESTION);

	m_arrDigitColor[0] = RGB(64,80,190);
	m_arrDigitColor[1] = RGB(31,104,1);
	m_arrDigitColor[2] = RGB(170,5,10);
	m_arrDigitColor[3] = RGB(17,18,139);
	m_arrDigitColor[4] = RGB(136,29,30);
	m_arrDigitColor[5] = RGB(5,123,125);
	m_arrDigitColor[6] = RGB(157,50,60);
	m_arrDigitColor[7] = RGB(171,8,11);

	OnFileNewgame();

	return 0;
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	RECT rc;
	GetClientRect(&rc);
	int x = point.x * m_data.GetWidth() / (rc.right - rc.left);
	int y = point.y * m_data.GetHeight() / (rc.bottom - rc.top);
	CMineItem item = m_data.GetItemState(x, y);

	if (CMineItem::STATE_CHECKED != item.m_iItemState
		&& CMineItem::STATE_FLAG != item.m_iItemState)
	{
		if (item.m_bMine)
		{
			GameOver();
		}
		else if (0 == item.m_nMineNeighbor)
		{
			m_data.FindSpace(x, y);
			if (m_data.GameWin())
			{
				GameWin();
			}
			else
			{
				Invalidate(false);
			}
		}
		else if (0 < item.m_nMineNeighbor)
		{
			m_data.SetItemState(x, y, CMineItem::STATE_CHECKED);
			if (m_data.GameWin())
			{
				GameWin();
			}
			else
			{
				Invalidate(false);
			}
		}
	}
	CWnd::OnLButtonUp(nFlags, point);
}

#include "GameOverDlg.h"

void CChildView::GameOver(void)
{
	if (m_bTimerOn)
	{
		m_bTimerOn = false;
		KillTimer(1);
	}
	m_data.ShowMines();
	Invalidate(false);

	CGameOverDlg dlg;
	dlg.DoModal();
	switch (dlg.m_iGameState)
	{
	case CGameOverDlg::NEW_GAME:
		OnFileNewgame();
		break;
	case CGameOverDlg::RETRY_GAME:
		m_data.RetryGame();
		SetTimer(1, 1000, NULL);
		m_bTimerOn = true;
		Invalidate(false);
		break;
	case CGameOverDlg::QUIT_GAME:
		PostQuitMessage(0);
		break;
	}
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	RECT rc;
	GetClientRect(&rc);
	int x = point.x * m_data.GetWidth() / (rc.right - rc.left);
	int y = point.y * m_data.GetHeight() / (rc.bottom - rc.top);
	CMineItem item = m_data.GetItemState(x, y);

	switch (item.m_iItemState)
	{
	case CMineItem::STATE_NORMAL:
		m_data.SetItemState(x, y, CMineItem::STATE_FLAG);
		m_nMineCount--;
		m_nMineCount = m_nMineCount < 0 ? 0 : m_nMineCount;
		AfxGetMainWnd()->PostMessage(UM_UPDATE_MINE, 0, m_nMineCount);
		Invalidate(false);
		break;
	case CMineItem::STATE_FLAG:
		m_data.SetItemState(x, y, CMineItem::STATE_QUESTION);
		m_nMineCount++;
		AfxGetMainWnd()->PostMessage(UM_UPDATE_MINE, 0, m_nMineCount);
		Invalidate(false);
		break;
	case CMineItem::STATE_QUESTION:
		m_data.SetItemState(x, y, CMineItem::STATE_NORMAL);
		Invalidate(false);
		break;
	default:
		break;
	}

	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	RECT rc;
	GetClientRect(&rc);
	int x = point.x * m_data.GetWidth() / (rc.right - rc.left);
	int y = point.y * m_data.GetHeight() / (rc.bottom - rc.top);
	CMineItem item = m_data.GetItemState(x, y);
	switch (item.m_iItemState)
	{
	case CMineItem::STATE_CHECKED:
		if (0 == m_data.ClearNeighbor(x, y))
		{
			if (m_data.GameWin())
			{
				GameWin();
			}
			else
			{
				Invalidate(false);
			}
			Invalidate(false);
		}
		else
		{
			GameOver();
		}
	default:
		break;
	}
	CWnd::OnLButtonDblClk(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

	//return CWnd::OnEraseBkgnd(pDC);
}


void CChildView::GameWin()
{
	if (m_bTimerOn)
	{
		m_bTimerOn = false;
		KillTimer(1);
	}
	AfxMessageBox(TEXT("you win"));
	
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	int nWidth  = m_data.GetWidth();
	int nHeight = m_data.GetHeight();
	if (cx*nHeight > cy*nWidth)
	{
		m_rcPaintArea.top    = 0;
		m_rcPaintArea.bottom = cy;
		m_rcPaintArea.left   = (cx-cy*nWidth/nHeight)/2;
		m_rcPaintArea.right  = cx - (cx-cy*nWidth/nHeight)/2;
	}
	else
	{
		m_rcPaintArea.top    = (cy - cx*nHeight/nWidth)/2;
		m_rcPaintArea.bottom = cy - (cy - cx*nHeight/nWidth)/2;
		m_rcPaintArea.left   = 0;
		m_rcPaintArea.right  = cx;
	}
}


void CChildView::PaintGame(CDC *pDC)
{
	CRect rc;
	GetClientRect(&rc);

	int nWidth  = m_data.GetWidth();
	int nHeight = m_data.GetHeight();
	int nItemWidth  = rc.Width()/nWidth;
	int nItemHeight = rc.Height()/nHeight;

	for (int ii = 0; ii < nWidth; ++ii)
	{
		for (int jj = 0; jj < nHeight; ++jj)
		{
			CMineItem item = m_data.GetItemState(ii, jj);


			switch (item.m_iItemState)
			{
			case CMineItem::STATE_NORMAL:
				{
					CBrush brush;
					brush.CreateSolidBrush(RGB(0, 0, 255));
					CBrush *pOldBrush = pDC->SelectObject(&brush);
					pDC->Rectangle(ii*nItemWidth, jj*nItemHeight, (ii+1)*nItemWidth, (jj+1)*nItemHeight);
					//pDC->FillSolidRect(ii*nItemWidth, jj*nItemHeight, nItemWidth, nItemHeight, RGB(0, 0, 255));
					pDC->SelectObject(pOldBrush);
					brush.DeleteObject();
				}
				break;
			case CMineItem::STATE_FLAG:
				{
					POINT pt;
					pt.x = ii*nItemWidth;
					pt.y = jj*nItemHeight;
					BITMAP bmp;
					m_bmpFlag.GetBitmap(&bmp);
					CDC memDC;
					memDC.CreateCompatibleDC(pDC);
					int oldMode = pDC->SetStretchBltMode(HALFTONE);
					CBitmap* pOldBitmap = memDC.SelectObject(&m_bmpFlag);
					pDC->StretchBlt(pt.x, pt.y, nItemWidth, nItemHeight, &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, MERGECOPY);
					pDC->SetStretchBltMode(oldMode);
					memDC.SelectObject(pOldBitmap);
					memDC.DeleteDC();
				}
				break;

			case CMineItem::STATE_QUESTION:
				{
					POINT pt;
					pt.x = ii*nItemWidth;
					pt.y = jj*nItemHeight;
					BITMAP bmp;
					m_bmpQuestion.GetBitmap(&bmp);
					CDC memDC;
					memDC.CreateCompatibleDC(pDC);
					CBitmap* pOldBitmap = memDC.SelectObject(&m_bmpQuestion);
					pDC->StretchBlt(pt.x, pt.y, nItemWidth, nItemHeight, &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, MERGECOPY);			
					memDC.SelectObject(pOldBitmap);
					memDC.DeleteDC();
				}
				break;

			case CMineItem::STATE_CHECKED:
				if (item.m_bMine)
				{
					POINT pt;
					pt.x = ii*nItemWidth;
					pt.y = jj*nItemHeight;
					BITMAP bmp;
					m_bmpMine.GetBitmap(&bmp);
					CDC memDC;
					memDC.CreateCompatibleDC(pDC);
					CBitmap* pOldBitmap = memDC.SelectObject(&m_bmpMine);
					pDC->StretchBlt(pt.x, pt.y, nItemWidth, nItemHeight, &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
					memDC.SelectObject(pOldBitmap);
					memDC.DeleteDC();
				}
				else
				{
					//if (0 == item.m_nMineNeighbor)//space
					//{
					CBrush brush;
					brush.CreateSolidBrush(RGB(255, 255, 255));
					CBrush *pOldBrush = pDC->SelectObject(&brush);
					pDC->Rectangle(ii*nItemWidth, jj*nItemHeight, (ii+1)*nItemWidth, (jj+1)*nItemHeight);
					pDC->SelectObject(pOldBrush);
					brush.DeleteObject();
					//}
					if (0 < item.m_nMineNeighbor)
					{
						RECT rt;
						rt.left   = ii*nItemWidth;
						rt.right  = rt.left + nItemWidth;
						rt.top    = jj*nItemHeight;
						rt.bottom = rt.top + nItemHeight;

						CString str;
						str.Format(TEXT("%d"), item.m_nMineNeighbor);
						CFont fnt;
						fnt.CreatePointFont(160, TEXT("Arial"));
						CFont *pOldFont = pDC->SelectObject(&fnt);
						COLORREF oldColor = pDC->SetTextColor(m_arrDigitColor[item.m_nMineNeighbor-1]);

						pDC->DrawText(str, &rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

						pDC->SetTextColor(oldColor);
						pDC->SelectObject(pOldFont);
						fnt.DeleteObject();
					}
				}
				break;
			}
		}
	}
}


void CChildView::PaintGameWin(CDC *pDC)
{

}


void CChildView::PaintGameOver(CDC *pDC)
{
	
}

void CChildView::OnFileNewgame()
{
	if (m_bTimerOn)
	{
		KillTimer(1);
		m_bTimerOn = false;
	}
	m_data.NewGame();
	m_nMineCount = m_data.GetTotalMine();
	AfxGetMainWnd()->PostMessage(UM_UPDATE_MINE, 0, m_nMineCount);
	SetTimer(1, 1000, NULL);
	m_bTimerOn = true;
	m_nTimer = 0;
	AfxGetMainWnd()->PostMessage(UM_UPDATE_TIME, 0, m_nTimer);
	Invalidate(false);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		++m_nTimer;
		if (m_nTimer > 999)
		{
			if (m_bTimerOn)
			{
				KillTimer(1);
				m_bTimerOn = false;
			}
		}
		AfxGetMainWnd()->PostMessage(UM_UPDATE_TIME, 0, m_nTimer);
	}
	CWnd::OnTimer(nIDEvent);
}


BOOL CChildView::DestroyWindow()
{
	if (m_bTimerOn)
	{
		KillTimer(1);
		m_bTimerOn = false;
	}

	return CWnd::DestroyWindow();
}


void CChildView::OnFileSettings()
{
	int nWidth   = m_data.GetWidth();
	int nHeight  = m_data.GetHeight();
	int nMine    = m_data.GetTotalMine();
	CSettingsDlg dlg(nWidth, nHeight, nMine, m_iDifficulty);
	if (IDOK == dlg.DoModal())
	{
		m_iDifficulty = dlg.m_iDifficulty;
		m_data.NewGame(dlg.m_nDWidth, dlg.m_nDHeight, dlg.m_nDMine);
		if (m_bTimerOn)
		{
			KillTimer(1);
			m_bTimerOn = false;
		}
		m_nMineCount = m_data.GetTotalMine();
		AfxGetMainWnd()->PostMessage(UM_UPDATE_MINE, 0, m_nMineCount);
		SetTimer(1, 1000, NULL);
		m_bTimerOn = true;
		m_nTimer = 0;
		AfxGetMainWnd()->PostMessage(UM_UPDATE_TIME, 0, m_nTimer);
		Invalidate(false);
	}
}
