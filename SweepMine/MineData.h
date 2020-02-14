/***********************************************\
*  MineData.h                                   *
*  (c) Mingkai Yuan, 2013-2                     *
*  Benyuan620@gmail.com                         *
*  this file defines data structures and        *
*and algorithm related to MineSweeper game.     *
\***********************************************/


#pragma once


#include <vector>

using std::vector;

class CMineItem
{
public:
	enum ITEM_STATE
	{
		STATE_UNDEFINED = 0,
		STATE_NORMAL,
		STATE_FLAG,
		STATE_QUESTION,
		STATE_CHECKED,
		STATE_MOUSE_HOVER
	};

public:
	CMineItem();
	CMineItem(bool m_bMine, ITEM_STATE iItemState, int nMineNeighbor);
public:
	bool         m_bMine;
	ITEM_STATE   m_iItemState;
	int          m_nMineNeighbor;
};



class CMineData
{
public:
	CMineData(void);
	~CMineData(void);

public:
	inline void SetItemState(int x, int y, CMineItem::ITEM_STATE iItemState)
	{
		m_vMineData[y][x].m_iItemState = iItemState;
	}
	inline const CMineItem& GetItemState(int x, int y) const
	{
		return m_vMineData[y][x];
	}

public:
	void SetGameDifficulty(int nWidth, int nHeight, int nMine);
	int  GetWidth(void)const{return m_nWidth;}
	int  GetHeight(void) const{return m_nHeight;}
	void GenerateMine(void);
	void ComputeNeighbor(void);
	void FindSpace(int x, int y);
	bool GameWin(void) const;
	void ShowMines(void);
	void NewGame(int nWidth, int nHeight, int nMine);
	void NewGame(void);
	void RetryGame(void);
	void CleanToZero(void);
	
	int ClearNeighbor(int x, int y);
	inline bool RangeCheck(int x, int y)
	{
		return x >= 0 && x < m_nWidth && y >= 0 && y < m_nHeight;
	}
	inline bool Flag(int x, int y)
	{
		return CMineItem::STATE_FLAG == m_vMineData[y][x].m_iItemState;
	}
	static inline bool CheckedOrFlag(const CMineItem& m)
	{
		return (CMineItem::STATE_CHECKED == m.m_iItemState || CMineItem::STATE_FLAG == m.m_iItemState);
	}
	static inline bool NormalOrQuestion(const CMineItem& m)
	{
		return (CMineItem::STATE_NORMAL == m.m_iItemState || CMineItem::STATE_QUESTION == m.m_iItemState);
	}
	inline bool ClearItem(int x, int y);
	inline int GetTotalMine(void) const{return m_nMineCount;}

private:

private:
	int                          m_nWidth;
	int                          m_nHeight;
	int                          m_nMineCount;
	vector<vector<CMineItem> >   m_vMineData;
};



inline bool CMineData::ClearItem(int x, int y)
{
		if (NormalOrQuestion(m_vMineData[y][x]))//game over
		{
			if (m_vMineData[y][x].m_bMine)
			{
				return 1;
			}
			else
			{
				m_vMineData[y][x].m_iItemState = CMineItem::STATE_CHECKED;
				FindSpace(x, y);
				FindSpace(x-1, y);
				FindSpace(x+1, y);
				FindSpace(x, y-1);
				FindSpace(x, y+1);
			}
		}
		return 0;
	}
