//************************************************************
//				���ļ�Ϊ������Ķ���
//************************************************************
#pragma once
#include"Define.h"
#include"Console.h"

class CBlock
{
private:
	BlockType m_type{ B_L };		//���������
	Direction m_direction{ UP };		//����ĳ���
	Color m_color{ WHITE };		//�������ɫ

	int m_BlockPoint[4][2];		//���浱ǰ����ÿ�����ص����ڵ����꣨ÿ������4�����ص㣬ÿ������x��y���꣩

	int m_x { WIDTH / 2 - 1 };		//�����λ������
	int m_y { 0 };

	void SetBlockPoint();			//���õ�ǰ����ÿ�����ص������
	//void SetColor();		//���ò�ͬ���ͷ������ɫ
	
public:
	CBlock();
	//CBlock(BlockType type, Direction dir);
	CBlock(BlockType type, Direction dir, Color color, int x_position);

	void DrawBlock(Cell board[WIDTH][HEIGHT], int width, int board_x) const;		//���Ʒ���
	void ClearBlock(Cell board[WIDTH][HEIGHT], int width, int board_x) const;		//��������
	void ClearBlockNotPrint(Cell board[WIDTH][HEIGHT], int width) const;		//�������鵫�ǲ����Ƶ�������
	void MoveBlock(Direction deriction, const Cell board[WIDTH][HEIGHT], int width);		//�ƶ�����
	void RotateBlock(const Cell board[WIDTH][HEIGHT], int width);		//��ת����

	bool LandTest(const Cell board[WIDTH][HEIGHT], int width);		//�������¼��
	bool BlockCollisionTest(const Cell board[WIDTH][HEIGHT], int width) const;		//������ײ���

	BlockType GetBlockType() const;
	Direction GetBlockDirection() const;
	Color GetBlockColor() const;
	
	int GetXPosition() const;
	int GetYPosition() const;

	void SetXPosition(int x_pos);		//���÷����x����
	
	void PrintBlock(int x, int y) const;		//��ָ����λ��(x, y)�����Ʒ��飨���ڻ��ƽ����е���һ��������ʾ��
};


CBlock::CBlock()
{
	SetBlockPoint();
	//SetColor();
}
/*
CBlock::CBlock(BlockType type, Direction dir) : m_type{ type }, m_direction{ dir }
{
	SetBlockPoint();
	SetColor();
}*/

CBlock::CBlock(BlockType type, Direction dir, Color color, int x_position) : m_type{ type }, m_direction{ dir }, m_color{ color }, m_x{ x_position }
{
	SetBlockPoint();
}



void CBlock::SetBlockPoint()
{
	for (int i{ 0 }; i < 4; i++)		//���õ�ǰ�����ÿ�����ص�����꣬�������������ÿ�����ص��ƫ��
	{
		m_BlockPoint[i][0] = m_x + BlockPointOffset[m_type][m_direction][i][0];
		m_BlockPoint[i][1] = m_y + BlockPointOffset[m_type][m_direction][i][1];
	}
}
/*
void CBlock::SetColor()
{
	switch (m_type)
	{
		case B_I: m_color = WHITE; break;
		case B_L: m_color = RED; break;
		case B_J: m_color = GREEN; break;
		case B_Z: m_color = BLUE; break;
		case B_S: m_color = YELLOW; break;
		case B_T: m_color = CYAN; break;
		case B_O: m_color = PURPLE; break;
		default:  break;
	}
}*/

void CBlock::DrawBlock(Cell board[WIDTH][HEIGHT], int width, int board_x) const
{
	for (int i{ 0 }; i < 4; i++)
	{
		if (m_BlockPoint[i][0] >= 0 && m_BlockPoint[i][0] < width && m_BlockPoint[i][1] >= 0 && m_BlockPoint[i][1] < HEIGHT)		//ȷ���ƻ���������ʱ����ʹ������Խ��
		{
			board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].type = FULL_CELL;
			board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].color = m_color;
			PrintCell(board[m_BlockPoint[i][0]][m_BlockPoint[i][1]], m_BlockPoint[i][0] + board_x, m_BlockPoint[i][1] + BOARD_Y);	//�ڽ���ǰ����д���������ͬʱ�ڽ����ϻ��Ƴ���
		}
	}
	if(m_type == B_BOMB)
	{
		PrintBomb(m_x + board_x, m_y + BOARD_Y);
	}
}

void CBlock::ClearBlock(Cell board[WIDTH][HEIGHT], int width, int board_x) const
{
	for (int i{ 0 }; i < 4; i++)
	{
		if (m_BlockPoint[i][0] >= 0 && m_BlockPoint[i][0] < width && m_BlockPoint[i][1] >= 0 && m_BlockPoint[i][1] < HEIGHT)		//ȷ�����ƻ��������ʱ����ʹ������Խ��
		{
			board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].type = EMPTY_CELL;
			board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].color = GRAY;
			PrintCell(board[m_BlockPoint[i][0]][m_BlockPoint[i][1]], m_BlockPoint[i][0] + board_x, m_BlockPoint[i][1] + BOARD_Y);	//�ڽ���ǰ����д���������ͬʱ�ڽ����ϻ��Ƴ���
		}
	}
	if(m_type == B_BOMB)
	{
		ClearBomb(m_x + board_x, m_y + BOARD_Y);
	}
}

void CBlock::ClearBlockNotPrint(Cell board[WIDTH][HEIGHT], int width) const
{
	for (int i{ 0 }; i < 4; i++)
	{
		if (m_BlockPoint[i][0] >= 0 && m_BlockPoint[i][0] < width && m_BlockPoint[i][1] >= 0 && m_BlockPoint[i][1] < HEIGHT)		//ȷ�����ƻ��������ʱ����ʹ������Խ��
		{
			board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].type = EMPTY_CELL;
			board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].color = GRAY;
		}
	}
}

void CBlock::MoveBlock(Direction deriction, const Cell board[WIDTH][HEIGHT], int width)
{
	switch (deriction)
	{
		case LEFT: 
			m_x--;
			SetBlockPoint();
			for (int i{ 0 }; i < 4; i++)
			{
				if (board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].type == FULL_CELL || m_BlockPoint[i][0] <0)		//��������ƹ�������������������򳬳���߽磬������һ��
				{
					m_x++;
					SetBlockPoint();
				}
			}
			break;

		case RIGHT: 
			m_x++; 
			SetBlockPoint();
			for (int i{ 0 }; i < 4; i++)
			{
				if (board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].type == FULL_CELL || m_BlockPoint[i][0] >= width)		//��������ƹ�������������������򳬳��ұ߽磬������һ��
				{
					m_x--;
					SetBlockPoint();
				}
			}
			break;

		case DOWN: 
			m_y++;
			SetBlockPoint();
			break;

		default: break;
	}
}

void CBlock::RotateBlock(const Cell board[WIDTH][HEIGHT], int width)
{
	bool AbleToRotate{ true };		//������תflag
	switch (m_direction)
	{
		case UP: m_direction = RIGHT; break;
		case RIGHT: m_direction = DOWN; break;
		case DOWN: m_direction = LEFT; break;
		case LEFT: m_direction = UP; break;
		default: m_direction = UP; break;
	}
	SetBlockPoint();		//�Ե�ǰ�������޸�����Ҫ��������ÿ�����ص�����

	if (BlockCollisionTest(board, width))		//�������ת�����⵽��ײ
		AbleToRotate = false;		//������תflag��Ϊfalse

	if(AbleToRotate == false)
	{
		for (int i{ 1 }; i <= 3; i++)
		{
			m_x -= i;		//��������i��
			SetBlockPoint();
			if (BlockCollisionTest(board, width))		//�����⵽��ײ
			{
				m_x += i;		//�ƻ�ԭ����λ��
				SetBlockPoint();
			}
			else 		//���û�м�⵽��ײ
			{
				return;		//������ת���˳�����
			}
			/*
			����ֻ��Ҫ�������ƶ����ó������ƣ���Ϊ�κ�һ�ַ��鶼���������ת֮�������������������򳬳���߽�������
			������������ƵĻ���ĳ����������»���ַ�������ת��������ϰ�����һ�ߵ�BUG��*/
			/*
			m_x += i;		//��������i��
			SetBlockPoint();
			if (BlockCollisionTest(arry))		//�����⵽��ײ
			{
				m_x -= i;		//�ƻ�ԭ����λ��
				SetBlockPoint();
			}
			else 		//���û�м�⵽��ײ
			{
				return;
			}*/
		}

		for (int i{ 1 }; i <= 3; i++)
		{
			m_y += i;		//��������i��
			SetBlockPoint();
			if (BlockCollisionTest(board, width))		//�����⵽��ײ
			{
				for (int j{ 1 }; j <= 3; j++)
				{
					m_x -= j;		//ÿ����i��ʱ���γ�������j��
					SetBlockPoint();
					if (BlockCollisionTest(board, width))
					{
						m_x += j;		//��⵽��ײ�����ƻ�ԭ����λ��
						SetBlockPoint();
					}
					else			//û�м�⵽��ײ
					{
						return;
					}
				}
				m_y -= i;		//�ڲ�ѭ������������3�����ƻ���⵽��ײ�����ƻ�ԭ����λ��
				SetBlockPoint();
			}
			else 		//���û�м�⵽��ײ
			{
				return;
			}
		}
	}

	if (AbleToRotate == false)		//�����������ת
	{
		switch (m_direction)		//��ת��ԭ����λ��
		{
			case UP: m_direction = LEFT; break;
			case RIGHT: m_direction = UP; break;
			case DOWN: m_direction = RIGHT; break;
			case LEFT: m_direction = DOWN; break;
			default: break;
		}
		SetBlockPoint();		//�Ե�ǰ�������޸�����Ҫ��������ÿ�����ص�����
	}
}

bool CBlock::LandTest(const Cell board[WIDTH][HEIGHT], int width)		//������DrawBlock��ClearBlock����֮ǰ����
{
	bool LandFlag{ false };
	//�������ʱ�Ƿ�������������������Ѿ�������
	if(m_type == B_PIERCE)
	{
		if (board[m_x][m_y].type == FULL_CELL || m_y>=HEIGHT)
		{
			LandFlag = true;
			m_y = HEIGHT - 1;
			SetBlockPoint();
			while(board[m_x][m_y].type == FULL_CELL)
			{
				m_y--;
				SetBlockPoint();
			}
		}
	}
	else
	{
		for (int i{ 0 }; i < 4; i++)
		{
			if (board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].type == FULL_CELL || m_BlockPoint[i][1]>=HEIGHT)			//��⵱ǰ�����ÿ�����ص��Ƿ����������з�����Ѿ�����
			{
				LandFlag = true;
				m_y--;		//�Ѿ�������Ҫ����һ��
				SetBlockPoint();		//�Ե�ǰ�������޸�����Ҫ��������ÿ�����ص�����
				i = -1;
			}
		}
	}
	return LandFlag;
}

bool CBlock::BlockCollisionTest(const Cell board[WIDTH][HEIGHT], int width) const
{
	for (int i{ 0 }; i < 4; i++)
	{
		if (board[m_BlockPoint[i][0]][m_BlockPoint[i][1]].type == FULL_CELL || m_BlockPoint[i][0] >= width || m_BlockPoint[i][0] < 0 || m_BlockPoint[i][1] >= HEIGHT || m_BlockPoint[i][1] < 0)		//�����ǰ�������κ�һ�����ص�����λ���Ѿ����ǿյĻ򳬳��������ұ߽磬���⵽��ײ
			return true;
	}
	return false;
}

inline BlockType CBlock::GetBlockType() const
{
	return m_type;
}

inline Direction CBlock::GetBlockDirection() const
{
	return m_direction;
}

inline Color CBlock::GetBlockColor() const
{
	return m_color;
}

inline int CBlock::GetXPosition() const
{
	return m_x;
}

inline int CBlock::GetYPosition() const
{
	return m_y;
}

void CBlock::SetXPosition(int x_pos)
{
	m_x = x_pos;
	SetBlockPoint();
}

void CBlock::PrintBlock(int x, int y) const
{
	//����ʾ����֮ǰ�Ȱ���������ÿո����
	for (int i{ x }; i <= x + 3; i++)
		for (int j{ y }; j <= y + 3; j++)
			PrintString("  ", i, j, WHITE);

	if (m_type == B_BOMB)
	{
		PrintBomb(x, y);
	}
	else
	{
		Cell cell_temp{ FULL_CELL, m_color };
		int x_cell, y_cell;
		for (int i{ 0 }; i < 4; i++)		//������������ÿһ����
		{
			x_cell = x + BlockPointOffset[m_type][m_direction][i][0];
			y_cell = y + BlockPointOffset[m_type][m_direction][i][1];
			PrintCell(cell_temp, x_cell, y_cell);
		}
	}
}
