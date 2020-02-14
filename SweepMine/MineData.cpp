#include "StdAfx.h"
#include "MineData.h"


CMineItem::CMineItem()
	: m_bMine(false)
	, m_iItemState(STATE_NORMAL)
	, m_nMineNeighbor(0)
{

}


CMineItem::CMineItem(bool bMine, ITEM_STATE iItemState, int nMineNeighbor)
	: m_bMine(bMine)
	, m_iItemState(iItemState)
	, m_nMineNeighbor(nMineNeighbor)
{

}



CMineData::CMineData(void)
	: m_nWidth(16)
	, m_nHeight(16)
	, m_nMineCount(40)
{
	m_vMineData.resize(m_nHeight);
	for (int i = 0; i < m_nHeight; ++i)
	{
		m_vMineData[i].resize(m_nWidth);
	}

	srand(GetTickCount());
}


CMineData::~CMineData(void)
{
}


void CMineData::SetGameDifficulty(int nWidth, int nHeight, int nMine)
{
	
	if (nWidth == m_nWidth && nHeight == m_nHeight)
	{
		return;
	}
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_vMineData.resize(m_nHeight);
	for (int i = 0; i < m_nHeight; ++i)
	{
		m_vMineData[i].resize(m_nWidth);
	}
	m_nMineCount = nMine;
}

void CMineData::NewGame(int nWidth, int nHeight, int nMine)
{
	SetGameDifficulty(nWidth, nHeight, nMine);
	CleanToZero();
	GenerateMine();
	ComputeNeighbor();
}


void CMineData::NewGame(void)
{
	CleanToZero();
	GenerateMine();
	ComputeNeighbor();
}

void CMineData::CleanToZero()
{
	for (int ii = 0; ii < m_nHeight; ++ii)
	{
		for (int jj = 0; jj < m_nWidth; ++jj)
		{
			m_vMineData[ii][jj].m_bMine       = false;
			m_vMineData[ii][jj].m_iItemState  = CMineItem::STATE_NORMAL;
			m_vMineData[ii][jj].m_bMine       = 0;
		}
	}
}


void CMineData::GenerateMine(void)
{
	int nMineCount = 0;
	int x = 0;
	int y = 0;
	while (nMineCount != m_nMineCount)
	{
		int r = rand();
		x = r % m_nWidth;
		y = (r / m_nWidth)%m_nHeight;
		if (!m_vMineData[y][x].m_bMine)
		{
			m_vMineData[y][x].m_bMine = true;
			nMineCount++;
		}
	}
}


void CMineData::ComputeNeighbor()
{
	//top-left
	m_vMineData[0][0].m_nMineNeighbor = m_vMineData[0][1].m_bMine + m_vMineData[1][0].m_bMine + m_vMineData[1][1].m_bMine;

	//bottom-left
	m_vMineData[m_nHeight-1][0].m_nMineNeighbor = m_vMineData[m_nHeight-2][0].m_bMine + m_vMineData[m_nHeight-1][1].m_bMine + m_vMineData[m_nHeight-2][1].m_bMine;

	//top-right
	m_vMineData[0][m_nWidth-1].m_nMineNeighbor = m_vMineData[0][m_nWidth-2].m_bMine + m_vMineData[1][m_nWidth-2].m_bMine + m_vMineData[1][m_nWidth-1].m_bMine;

	//bottom-right
	m_vMineData[m_nHeight-1][m_nWidth-1].m_nMineNeighbor = m_vMineData[m_nHeight-1][m_nWidth-2].m_bMine + m_vMineData[m_nHeight-2][m_nWidth-2].m_bMine + m_vMineData[m_nHeight-2][m_nWidth-1].m_bMine;

	//horizontal
	for (int i = 1; i < m_nWidth-1; ++i)
	{
		m_vMineData[0][i].m_nMineNeighbor = m_vMineData[0][i-1].m_bMine + m_vMineData[0][i+1].m_bMine
			+ m_vMineData[1][i-1].m_bMine + m_vMineData[1][i].m_bMine+m_vMineData[1][i+1].m_bMine;
		m_vMineData[m_nHeight-1][i].m_nMineNeighbor = m_vMineData[m_nHeight-1][i-1].m_bMine + m_vMineData[m_nHeight-1][i+1].m_bMine
			+ m_vMineData[m_nHeight-2][i-1].m_bMine + m_vMineData[m_nHeight-2][i].m_bMine+m_vMineData[m_nHeight-2][i+1].m_bMine;
	}

	//vertical
	for (int i = 1; i < m_nHeight-1; ++i)
	{
		m_vMineData[i][0].m_nMineNeighbor = m_vMineData[i-1][0].m_bMine + m_vMineData[i+1][0].m_bMine
			+ m_vMineData[i-1][1].m_bMine + m_vMineData[i][1].m_bMine+m_vMineData[i+1][1].m_bMine;
		m_vMineData[i][m_nWidth-1].m_nMineNeighbor = m_vMineData[i-1][m_nWidth-1].m_bMine + m_vMineData[i+1][m_nWidth-1].m_bMine
			+ m_vMineData[i-1][m_nWidth-2].m_bMine + m_vMineData[i][m_nWidth-2].m_bMine+m_vMineData[i+1][m_nWidth-2].m_bMine;
	}

	//center
	for (int ii = 1; ii < m_nWidth-1; ++ii)
	{
		for (int jj = 1; jj < m_nHeight-1; ++jj)
		{
			m_vMineData[jj][ii].m_nMineNeighbor = m_vMineData[jj][ii-1].m_bMine + m_vMineData[jj][ii+1].m_bMine
				+m_vMineData[jj-1][ii-1].m_bMine + m_vMineData[jj-1][ii].m_bMine + m_vMineData[jj-1][ii+1].m_bMine
				+m_vMineData[jj+1][ii-1].m_bMine + m_vMineData[jj+1][ii].m_bMine + m_vMineData[jj+1][ii+1].m_bMine;
		}
	}
}



#include <stack>
using std::stack;

void CMineData::FindSpace(int x, int y)
{
	if (!RangeCheck(x, y))
	{
		return;
	}
	if (m_vMineData[y][x].m_nMineNeighbor != 0)
	{
		return;
	}

	POINT pt;
	stack<POINT> s;

	pt.x = x;
	pt.y = y;
	s.push(pt);

	while(!s.empty())
	{
		pt = s.top();
		s.pop();
		CMineItem &t_item = m_vMineData[pt.y][pt.x];
		if (CMineItem::STATE_NORMAL == t_item.m_iItemState
			|| CMineItem::STATE_QUESTION == t_item.m_iItemState)
		{
			//mine
			if (t_item.m_bMine)
			{
				continue;
			}

			//space
			if (0 == t_item.m_nMineNeighbor)
			{
				t_item.m_iItemState = CMineItem::STATE_CHECKED;

				//push for neighbors
				POINT t_pt;
				t_pt.x = pt.x+1;
				t_pt.y = pt.y;
				if (t_pt.x < m_nWidth)
				{
					if (CMineItem::STATE_NORMAL == m_vMineData[t_pt.y][t_pt.x].m_iItemState
						|| CMineItem::STATE_QUESTION == m_vMineData[t_pt.y][t_pt.x].m_iItemState)
					{
						s.push(t_pt);
					}
				}

				t_pt.x = pt.x - 1;
				if (t_pt.x >= 0)
				{
					if (CMineItem::STATE_NORMAL == m_vMineData[t_pt.y][t_pt.x].m_iItemState
						|| CMineItem::STATE_QUESTION == m_vMineData[t_pt.y][t_pt.x].m_iItemState)
					{
						s.push(t_pt);
					}
				}

				t_pt.x = pt.x;
				t_pt.y = pt.y+1;
				if (t_pt.y < m_nHeight)
				{
					if (CMineItem::STATE_NORMAL == m_vMineData[t_pt.y][t_pt.x].m_iItemState
						|| CMineItem::STATE_QUESTION == m_vMineData[t_pt.y][t_pt.x].m_iItemState)
					{
						s.push(t_pt);
					}
				}

				t_pt.y = pt.y - 1;
				if (t_pt.y >= 0)
				{
					if (CMineItem::STATE_NORMAL == m_vMineData[t_pt.y][t_pt.x].m_iItemState
						|| CMineItem::STATE_QUESTION == m_vMineData[t_pt.y][t_pt.x].m_iItemState)
					{
						s.push(t_pt);
					}
				}

				if (RangeCheck(pt.x-1, pt.y-1))
				{
					t_pt.x = pt.x-1;
					t_pt.y = pt.y-1;
					if (CMineItem::STATE_NORMAL == m_vMineData[t_pt.y][t_pt.x].m_iItemState
						|| CMineItem::STATE_QUESTION == m_vMineData[t_pt.y][t_pt.x].m_iItemState)
					{
						s.push(t_pt);
					}
				}
				if (RangeCheck(pt.x+1, pt.y-1))
				{
					t_pt.x = pt.x+1;
					t_pt.y = pt.y-1;
					if (CMineItem::STATE_NORMAL == m_vMineData[t_pt.y][t_pt.x].m_iItemState
						|| CMineItem::STATE_QUESTION == m_vMineData[t_pt.y][t_pt.x].m_iItemState)
					{
						s.push(t_pt);
					}
				}
				if (RangeCheck(pt.x-1, pt.y+1))
				{
					t_pt.x = pt.x-1;
					t_pt.y = pt.y+1;
					if (CMineItem::STATE_NORMAL == m_vMineData[t_pt.y][t_pt.x].m_iItemState
						|| CMineItem::STATE_QUESTION == m_vMineData[t_pt.y][t_pt.x].m_iItemState)
					{
						s.push(t_pt);
					}
				}
				if (RangeCheck(pt.x+1, pt.y+1))
				{
					t_pt.x = pt.x+1;
					t_pt.y = pt.y+1;
					if (CMineItem::STATE_NORMAL == m_vMineData[t_pt.y][t_pt.x].m_iItemState
						|| CMineItem::STATE_QUESTION == m_vMineData[t_pt.y][t_pt.x].m_iItemState)
					{
						s.push(t_pt);
					}
				}
			}//endof space
			else//has a mine neighbor
			{
				t_item.m_iItemState = CMineItem::STATE_CHECKED;
			}
		}
	}//endof while
}


int CMineData::ClearNeighbor(int x, int y)
{
	if (m_vMineData[y][x].m_bMine)
	{
		return 0;
	}

	int nFlagCount = 0;
	//1
	if (RangeCheck(x-1, y))
	{
		nFlagCount += Flag(x-1, y);
	}
	//2
	if (RangeCheck(x+1, y))
	{
		nFlagCount += Flag(x+1, y);
	}
	//3
	if (RangeCheck(x-1, y-1))
	{
		nFlagCount += Flag(x-1, y-1);
	}
	//4
	if (RangeCheck(x, y-1))
	{
		nFlagCount += Flag(x, y-1);
	}
	//5
	if (RangeCheck(x+1, y-1))
	{
		nFlagCount += Flag(x+1, y-1);
	}
	//6
	if (RangeCheck(x-1, y+1))
	{
		nFlagCount += Flag(x-1, y+1);
	}
	//7
	if (RangeCheck(x, y+1))
	{
		nFlagCount += Flag(x, y+1);
	}
	//8
	if (RangeCheck(x+1, y+1))
	{
		nFlagCount += Flag(x+1, y+1);
	}
	if (m_vMineData[y][x].m_nMineNeighbor == nFlagCount)
	{
		//1
		if (RangeCheck(x-1, y))
		{
			if (ClearItem(x-1, y))
			{
				return 1;
			}
		}
		//2
		if (RangeCheck(x+1, y))
		{
			if(ClearItem(x+1, y))
			{
				return 1;
			}
		}
		//3
		if (RangeCheck(x-1, y-1))
		{
			if (ClearItem(x-1, y-1))
			{
				return 1;
			}
		}
		//4
		if (RangeCheck(x, y-1))
		{
			if (ClearItem(x, y-1))
			{
				return 1;
			}
		}
		//5
		if (RangeCheck(x+1, y-1))
		{
			if (ClearItem(x+1, y-1))
			{
				return 1;
			}
		}
		//6
		if (RangeCheck(x-1, y+1))
		{
			if (ClearItem(x-1, y+1))
			{
				return 1;
			}
		}
		//7
		if (RangeCheck(x, y+1))
		{
			if (ClearItem(x, y+1))
			{
				return 1;
			}
		}
		//8
		if (RangeCheck(x+1, y+1))
		{
			if (ClearItem(x+1, y+1))
			{
				return 1;
			}
		}
	}

	return 0;
#if 0
	CMineItem &item = m_vMineData[y][x];
	//top line
	if (0 == y)
	{
		if (0 == x)//top-left
		{
			int nFlagCount = 0;
			nFlagCount = CheckedOrFlag(m_vMineData[0][1]) + CheckedOrFlag(m_vMineData[1][0]) + CheckedOrFlag(m_vMineData[1][1]);
			if (item.m_nMineNeighbor == nFlagCount)
			{
				//1
				if (m_vMineData[0][1].m_bMine 
					&& NormalOrQuestion(m_vMineData[0][1]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[0][1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(0, 1);
					return 0;
				}

				//2
				if (m_vMineData[1][1].m_bMine 
					&& NormalOrQuestion(m_vMineData[1][1]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[1][1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(1, 1);
					return 0;
				}

				//3
				if (m_vMineData[1][0].m_bMine 
					&& NormalOrQuestion(m_vMineData[1][0]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[1][0].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(1, 0);
					return 0;
				}
			}
		}
		else if (m_nWidth-1 ==  x)//top-right
		{
			int nFlagCount = 0;
			nFlagCount = CheckedOrFlag(m_vMineData[0][x-1]) + CheckedOrFlag(m_vMineData[1][x-1]) + CheckedOrFlag(m_vMineData[1][x]);
			if (item.m_nMineNeighbor == nFlagCount)
			{
				//1
				if (m_vMineData[0][x-1].m_bMine 
					&& NormalOrQuestion(m_vMineData[0][x-1]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[0][x-1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(0, x-1);
					return 0;
				}

				//2
				if (m_vMineData[1][x].m_bMine 
					&& NormalOrQuestion(m_vMineData[1][x]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[1][x].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(1, x);
					return 0;
				}

				//3
				if (m_vMineData[1][x-1].m_bMine 
					&& NormalOrQuestion(m_vMineData[1][x-1]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[1][x-1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(1, x-1);
					return 0;
				}
			}
		}
		else //top-middle
		{
			int nFlagCount = 0;
			nFlagCount = CheckedOrFlag(m_vMineData[y][x-1]) + CheckedOrFlag(m_vMineData[y][x+1])
				+ CheckedOrFlag(m_vMineData[y+1][x-1]) + CheckedOrFlag(m_vMineData[y+1][x]) + CheckedOrFlag(m_vMineData[y+1][x+1]);
			if (nFlagCount == item.m_nMineNeighbor)
			{
				//1
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y][x-1]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y][x-1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y, x-1);
					return 0;
				}
				//2
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y][x+1]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y][x+1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y, x+1);
					return 0;
				}
				//3
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y+1][x-1]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y+1][x-1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y+1, x-1);
					return 0;
				}
				//4
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y+1][x]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y+1][x].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y+1, x);
					return 0;
				}
				//5
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y][x-1]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y+1][x+1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y+1, x+1);
					return 0;
				}
			}
		}
	}
	else if (m_nHeight-1 == y) //bottom line
	{
		if (0 == x)//bottom-left
		{
			int nFlagCount = 0;
			nFlagCount = CheckedOrFlag(m_vMineData[y][1]) + CheckedOrFlag(m_vMineData[y][0]) + CheckedOrFlag(m_vMineData[1][1]);
			if (item.m_nMineNeighbor == nFlagCount)
			{
				//1
				if (m_vMineData[0][1].m_bMine 
					&& NormalOrQuestion(m_vMineData[0][1]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[0][1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(0, 1);
					return 0;
				}

				//2
				if (m_vMineData[1][1].m_bMine 
					&& NormalOrQuestion(m_vMineData[1][1]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[1][1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(1, 1);
					return 0;
				}

				//3
				if (m_vMineData[1][0].m_bMine 
					&& NormalOrQuestion(m_vMineData[1][0]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[1][0].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(1, 0);
					return 0;
				}
			}
		}
		else if (m_nWidth-1 ==  x)//top-right
		{
			int nFlagCount = 0;
			nFlagCount = CheckedOrFlag(m_vMineData[0][x-1]) + CheckedOrFlag(m_vMineData[1][x-1]) + CheckedOrFlag(m_vMineData[1][x]);
			if (item.m_nMineNeighbor == nFlagCount)
			{
				//1
				if (m_vMineData[0][x-1].m_bMine 
					&& NormalOrQuestion(m_vMineData[0][x-1]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[0][x-1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(0, x-1);
					return 0;
				}

				//2
				if (m_vMineData[1][x].m_bMine 
					&& NormalOrQuestion(m_vMineData[1][x]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[1][x].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(1, x);
					return 0;
				}

				//3
				if (m_vMineData[1][x-1].m_bMine 
					&& NormalOrQuestion(m_vMineData[1][x-1]))//check if a flag is wrong
				{
					return 1;//game over
				}
				else
				{
					m_vMineData[1][x-1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(1, x-1);
					return 0;
				}
			}
		}
		else //top-middle
		{
			int nFlagCount = 0;
			nFlagCount = CheckedOrFlag(m_vMineData[y][x-1]) + CheckedOrFlag(m_vMineData[y][x+1])
				+ CheckedOrFlag(m_vMineData[y+1][x-1]) + CheckedOrFlag(m_vMineData[y+1][x]) + CheckedOrFlag(m_vMineData[y+1][x+1]);
			if (nFlagCount == item.m_nMineNeighbor)
			{
				//1
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y][x-1]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y][x-1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y, x-1);
					return 0;
				}
				//2
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y][x+1]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y][x+1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y, x+1);
					return 0;
				}
				//3
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y+1][x-1]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y+1][x-1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y+1, x-1);
					return 0;
				}
				//4
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y+1][x]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y+1][x].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y+1, x);
					return 0;
				}
				//5
				if (item.m_bMine && NormalOrQuestion(m_vMineData[y][x-1]))
				{
					return 1;
				}
				else
				{
					m_vMineData[y+1][x+1].m_iItemState = CMineItem::STATE_CHECKED;
					FindSpace(y+1, x+1);
					return 0;
				}
			}
		}
	}
	else//middle in vertical
	{

	}
#endif
}


bool CMineData::GameWin(void) const
{
	int nChecked = 0;
	for (int ii = 0; ii < m_nHeight; ++ii)
	{
		for (int jj = 0; jj < m_nWidth; ++jj)
		{
			if (CMineItem::STATE_CHECKED == m_vMineData[ii][jj].m_iItemState)
			{
				++nChecked;
			}
		}
	}
	if (nChecked + m_nMineCount == m_nWidth*m_nHeight)
	{
		return true;
	}
	return false;
}


void CMineData::ShowMines(void)
{
	for (int ii = 0; ii < m_nHeight; ++ii)
	{
		for (int jj = 0; jj < m_nWidth; ++jj)
		{
			if (m_vMineData[ii][jj].m_bMine)
			{
				m_vMineData[ii][jj].m_iItemState = CMineItem::STATE_CHECKED;
			}
		}
	}
}


void CMineData::RetryGame(void)
{
	for (int ii = 0; ii < m_nHeight; ++ii)
	{
		for (int jj = 0; jj < m_nWidth; ++jj)
		{
			m_vMineData[ii][jj].m_iItemState = CMineItem::STATE_NORMAL;
		}
	}
}