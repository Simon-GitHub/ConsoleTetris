//************************************************************
//				���ļ�Ϊ������Ķ���
//************************************************************
#pragma once
#pragma comment (lib,"winmm.lib")
#include"Define.h"
#include"Block.h"
#include"Console.h"
#include"Ini.h"
#include <windows.h>
#include<fstream>
#include<iostream>
using std::ofstream;
using std::ifstream;

class CUI
{
private:
	Cell m_board[WIDTH][HEIGHT];		//���浱ǰ��Ϸ������10x20��ÿ�����ӵ�״̬����ɫ����FULL_CELL��EMPTY_CELL����״̬

	CBlock CurrentBlock1;		//���1�ĵ�ǰ����
	CBlock CurrentBlock2;		//���2�ĵ�ǰ����
	CBlock NextBlock1;		//���1����һ������
	CBlock NextBlock2;		//���2����һ������

	int m_score{ 0 };		//��Ϸ�÷�
	int m_level{ 1 };		//��Ϸ�ȼ�
	
	int m_strip_number{ 0 };		//�������ߵ�����
	int m_bomb_number{ 0 };		//ը�����ߵ�����
	int m_pierce_number{ 0 };		//���׵����ߵ�����

	bool m_load_flag{ false };		//ִ������������󣬴�flag��Ϊtrue

	int m_board_x{};		//���ƽ������ʼx���꣨��Ҫ���ݽ�����m_width���㣩
	int m_block1_x{};		//˫��ģʽ�����1���Ʒ������ʼxλ�ã���Ҫ���ݽ�����m_width���㣩
	int m_block2_x{};		//˫��ģʽ�����2���Ʒ������ʼxλ�ã���Ҫ���ݽ�����m_width���㣩

	//ѡ����������
	bool m_clear_animation;		//�Ƿ���ʾ��������
	int m_clear_animation_speed;		//����ÿ�����ӵļ��ʱ�䣨��λ��ms����ֵԽС�ٶ�Խ��
	bool m_allow_level_up;		//�Ƿ���������
	int m_score_per_level;		//ÿ���ٷ�����
	Color m_color_table[9];		//����7�����͵ķ���+2�ֵ��ߵ���ɫ
	bool m_atuo_save{ false };		//�˳�ʱ�Ƿ��Զ��浵
	
	bool m_invisible_mode;		//����ģʽ
	int m_invisible_mode_difficulty;		//����ģʽ�Ѷȣ�0���ͣ�1���У�2��
	bool m_double_player;		//˫��ģʽ
	int m_width;		//������ʾ�Ŀ��
	bool m_sound_effect;		//��Ϸ��Ч
	
	//���1�ļ�λ�趨����
	int m_1_left_key;		//�������Ƽ�
	int m_1_right_key;		//�������Ƽ�
	int m_1_down_key;		//�������Ƽ�
	int m_1_rotate_key;		//������ת��
	int m_1_sink_key;		//����ֱ�������
	//���2�ļ�λ�趨����
	int m_2_left_key;		//�������Ƽ�
	int m_2_right_key;		//�������Ƽ�
	int m_2_down_key;		//�������Ƽ�
	int m_2_rotate_key;		//������ת��
	int m_2_sink_key;		//����ֱ�������

	void CalculateLevel();		//����ȼ�
	void ShowSettingsInfo(int x, int y) const;		//������x,y����ʾѡ�������е���Ϣ
	void ColorSettings();			//������ɫ����
	void DrawBoardVisible() const;		//���κ�ʱ����ʾ���棨����������ģʽʱ��ʾ���棩
	void ShowPause() const;		//��ʾ��ͣʱ����Ϸ����
	void Pause();		//��ͣ����
	void KeySettings();		//��λ����
	void CalculateBoardXAndBlockPosition();		//���ݽ����ȼ�����ƽ������ʼx����ͷ�����ʼx����
	
public:
	CUI();

	void DrawBoard() const;			//������Ϸ����
	void DrawCurrentBlock(Player player);		//����Ϸ�����ϻ��Ƶ�ǰ����
	void ClearCurrentBlock(Player player, bool print);			//����Ϸ�����ϲ�����ǰ���飬������ʾ�Ƿ��ڲ�����ͬʱ�ڽ����ϻ��Ƴ���

	bool BlockLandTest(Player player);			//���������ж�
	void ClearLine();		//��������
	void GetAProp();		//�����ȡһ������
	bool GameOver(Player player) const;	//��Ϸ�����ж�

	void SetNextBlock(Player player);		//����һ����������Ϊ��ǰ����

	void KeyDetect(int key);			//����������
	void ShowInfo() const;			//��ʾ��Ϸ��Ϣ
	void ShowHelpInfo() const;		//��ʾ������Ϣ
	bool ShowGameOver() const;		//��ʾ��Ϸ����ʱ����Ϸ����
	void OptionSettings();		//ѡ������

	int GetIntervalTime() const;		//���ݵ�ǰ�ȼ����㷽������ʱ�ļ��ʱ�䣨��λ��ms��

	void SaveData() const;		//����Ϸ���ݱ��浽�ļ�
	void LoadData();		//���ļ�������Ϸ����
	void SaveSettings() const;		//����Ϸ���ñ��浽ini�ļ�
	void LoadSettings();		//��ini�ļ�������Ϸ����

	bool GetAutoSave() const;		//��ȡ�Ƿ��Զ��浵ѡ��
	int GetDownKey(Player player) const;		//��ȡ�������Ƽ����趨
	bool KeyIsControlKey(int key) const;		//�����жϰ��ļ��ǲ�����Ϸ���Ƽ�
	bool DoublePlayer() const;		//��ȡ˫��ģʽѡ��

};


CUI::CUI()
{
	for (int i{ 0 }; i < WIDTH; i++)
	{
		for (int j{ 0 }; j < HEIGHT; j++)
		{
			m_board[i][j].type = EMPTY_CELL;
			m_board[i][j].color = GRAY;
		}
	}
	
	LoadSettings();		//��ʼ��ʱ��������
	m_color_table[7] = WHITE;		//ը��������ɫ��ʼ��
	m_color_table[8] = WHITE;		//���׵�������ɫ��ʼ��
	CalculateBoardXAndBlockPosition();

	SYSTEMTIME current_time;
	GetLocalTime(&current_time);			//��ȡ��ǰʱ��
	srand(current_time.wMilliseconds);		//�õ�ǰʱ��ĺ��������ò��������������
	BlockType type{ static_cast<BlockType>(rand() % 7) };
	//�������һ�����1�ĵ�ǰ��������ͺͳ���˫��ģʽ����BLOCK1_X��λ�����ɣ���˫��ģʽ���ڽ����м�λ������
	CurrentBlock1 = CBlock(type, static_cast<Direction>(rand() % 4), m_color_table[type], m_double_player ? m_block1_x : m_width / 2 - 1);
	type = static_cast<BlockType>(rand() % 7);
	NextBlock1 = CBlock(type, static_cast<Direction>(rand() % 4), m_color_table[type], m_double_player ? m_block1_x : m_width / 2 - 1);		//���������һ������1�����ͺͳ���
	
	type = static_cast<BlockType>(rand()*2 % 7);
	CurrentBlock2 = CBlock(type, static_cast<Direction>(rand() % 4), m_color_table[type], m_block2_x);		//�������һ����ǰ����2�����ͺͳ���
	type = static_cast<BlockType>(rand() % 7);
	NextBlock2 = CBlock(type, static_cast<Direction>(rand() % 4), m_color_table[type], m_block2_x);		//���������һ������2�����ͺͳ���
}



void CUI::DrawBoard() const
{
	int i, j;
	for (i = 0; i < m_width; i++)
		for (j = 0; j < HEIGHT; j++)
			m_invisible_mode ? PrintCell(Cell{ EMPTY_CELL, GRAY }, i + m_board_x, j + BOARD_Y) : PrintCell(m_board[i][j], i + m_board_x, j + BOARD_Y);
}

void CUI::DrawBoardVisible() const
{
	int i, j;
	for (i = 0; i < m_width; i++)
		for (j = 0; j < HEIGHT; j++)
			PrintCell(m_board[i][j], i + m_board_x, j + BOARD_Y);
}

inline void CUI::DrawCurrentBlock(Player player)
{
	if (player == PLAYER1) CurrentBlock1.DrawBlock(m_board, m_width, m_board_x);
	else CurrentBlock2.DrawBlock(m_board, m_width, m_board_x);
}

inline void CUI::ClearCurrentBlock(Player player, bool print)
{
	if (player == PLAYER1) print ? CurrentBlock1.ClearBlock(m_board, m_width, m_board_x) : CurrentBlock1.ClearBlockNotPrint(m_board, m_width);
	else print ? CurrentBlock2.ClearBlock(m_board, m_width, m_board_x) : CurrentBlock2.ClearBlockNotPrint(m_board, m_width);
}

inline bool CUI::BlockLandTest(Player player)
{
	bool land_flag{ false };
	if (player == PLAYER1)
	{
		land_flag = CurrentBlock1.LandTest(m_board, m_width);
		if (land_flag && m_sound_effect && CurrentBlock1.GetBlockType() != B_BOMB) PlaySound(_T("./sound/land.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	else
	{
		land_flag = CurrentBlock2.LandTest(m_board, m_width);
		if (land_flag && m_sound_effect && CurrentBlock2.GetBlockType() != B_BOMB) PlaySound(_T("./sound/land.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	return land_flag;
}

void CUI::CalculateLevel()
{
	if (m_allow_level_up)
		m_level = m_score / m_score_per_level + 1;		//ÿ�����ض��ĵ÷֣��ȼ�����1��
	else
		m_level = 1;		//����������ʱ��һֱ��1��
}

void CUI::ClearLine()
{
	int i, j;
	int clear_count{ 0 };		//ͳ�������е�����
	if(CurrentBlock1.GetBlockType() == B_BOMB)		//��ǰ������ը��ʱ����ը�������������·�4x4��4x8�����ڵ����з���
	{
		if (m_sound_effect) PlaySound(_T("./sound/bomb.wav"), NULL, SND_ASYNC | SND_FILENAME);
		for(i = 0; i<4; i++)
			for(j = 0; j<8; j++)
			{
				if (CurrentBlock1.GetYPosition() + j < HEIGHT)
				{
					m_board[CurrentBlock1.GetXPosition()+i][CurrentBlock1.GetYPosition()+j].type = EMPTY_CELL;
					m_board[CurrentBlock1.GetXPosition()+i][CurrentBlock1.GetYPosition()+j].color = GRAY;
					PrintCell(Cell{ EMPTY_CELL, GRAY }, CurrentBlock1.GetXPosition() + i + m_board_x, CurrentBlock1.GetYPosition() + j + BOARD_Y);
				}
			}
	}
	else if (CurrentBlock2.GetBlockType() == B_BOMB)
	{
		if (m_sound_effect) PlaySound(_T("./sound/bomb.wav"), NULL, SND_ASYNC | SND_FILENAME);
		for (i = 0; i<4; i++)
			for (j = 0; j<8; j++)
			{
				if (CurrentBlock2.GetYPosition() + j < HEIGHT)
				{
					m_board[CurrentBlock2.GetXPosition() + i][CurrentBlock2.GetYPosition() + j].type = EMPTY_CELL;
					m_board[CurrentBlock2.GetXPosition() + i][CurrentBlock2.GetYPosition() + j].color = GRAY;
					PrintCell(Cell{ EMPTY_CELL, GRAY }, CurrentBlock2.GetXPosition() + i + m_board_x, CurrentBlock2.GetYPosition() + j + BOARD_Y);
				}
			}
	}
	else
	{
		bool clear_flag{ true };			//��ǰ�п�������flag
		for (i = HEIGHT - 1; i >= 0; i--)		//��������һ�п�ʼ�ж�
		{
			for (j = 0; j < m_width; j++)
			{
				if (m_board[j][i].type == EMPTY_CELL)	//ֻҪ��ǰ����һ�������ǿյģ����оͲ�������
					clear_flag = false;	
			}

			if (clear_flag)		//�����ǰ�п�������
			{
				if (m_sound_effect) PlaySound(_T("./sound/clear.wav"), NULL, SND_ASYNC | SND_FILENAME);
				if (m_invisible_mode && m_invisible_mode_difficulty<=1 && clear_count == 0)		//����ģʽ���Ѷ�Ϊ�ͻ���ʱ����������У�����������һ��֮ǰ��ʾ����500����
				{
					DrawBoardVisible();
					Sleep(500);
				}
				if (m_clear_animation)		//���������ʾ������������������ո�������ʾ����ʱ�Ķ���
				{
					if (m_invisible_mode_difficulty <=1)
						DrawBoardVisible();		//ˢ��һ�ν�����ʾ
					else DrawBoard();
					if (m_invisible_mode && m_invisible_mode_difficulty == 2)		//������ģʽ���Ѷ�Ϊ��ʱ����������У��Ȱѵ�ǰ������������ʾ����
					{
						for (j = 0; j < m_width; j++)
						{
							PrintCell(m_board[j][i], j + m_board_x, i + BOARD_Y);
						}
					}
					if (clear_count % 2 == 0)
					{
						for (j = 0; j < m_width; j++)		//����ߵĸ��ӿ�ʼ���
						{
							PrintCell(Cell{ EMPTY_CELL, GRAY }, j + m_board_x, i + BOARD_Y);		//����һ���յĸ���
							Sleep(m_clear_animation_speed);				//ÿ���һ��������ͣһ��ʱ��
						}
					}
					else
					{
						for (j = m_width - 1; j >= 0; j--)		//���ұߵĸ��ӿ�ʼ���
						{
							PrintCell(Cell{ EMPTY_CELL, GRAY }, j + m_board_x, i + BOARD_Y);		//����һ���յĸ���
							Sleep(m_clear_animation_speed);				//ÿ���һ��������ͣһ��ʱ��
						}
					}
				}

				for (int k{ i }; k>= 0; k--)		//�ӵ�i�п�ʼ�����ÿһ����������һ��
				{
					if (k == 0)		//������������һ�У���Ѹ������
					{
						for (j = 0; j < m_width; j++)
						{
							m_board[j][k].type = EMPTY_CELL;
							m_board[j][k].color = GRAY;
						}
					}
					else
					{
						for (j = 0; j < m_width; j++)
						{
							m_board[j][k] = m_board[j][k - 1];
						}
					}
				}
				i++;		//����ѵ�ǰ�������ˣ���ȻҪ�ӵ�ǰ�п�ʼ�жϣ�i�Ͳ����Լ����������Լ�1
				clear_count++;		//�����е�������1
			}
			clear_flag = true;		//�ж���һ�к�clear_flag��Ϊtrue
		}
	}
	
	if (m_invisible_mode)
	{
		if(m_invisible_mode_difficulty == 0)		//����ģʽ�Ѷ�Ϊ��ʱ��ÿ�η���ÿ�����䶼��ʾ�������500����
		{
			DrawBoardVisible();
		}
		else if(m_invisible_mode_difficulty == 1)			//����ģʽ�Ѷ�Ϊ��ʱ������������У�������������ʾ����500����
		{
			if (clear_count > 0) DrawBoardVisible();
		}
		Sleep(500);
		DrawBoard();		//����ģʽʱÿ�η�������ʱ��ˢ�½���
	}
	else
	{
		if (clear_count > 0) DrawBoard();		//������ģʽʱ��������ʱ����ˢ�½���
	}
	SYSTEMTIME current_time;
	GetLocalTime(&current_time);			//��ȡ��ǰʱ��
	srand(current_time.wMilliseconds);		//�õ�ǰʱ��ĺ��������ò��������������
	switch (clear_count)		//��������������������Ӧ�ĵ÷ּ���õ���
	{
		case 1:
			m_score += 1;
			if (rand() % 10 == 0) GetAProp();		//����1��1/10�ĸ��ʻ�õ���
			break;
		case 2:
			m_score += 3;
			if (rand() % 4 == 0) GetAProp();		//����2��1/4�ĸ��ʻ�õ���
			break;
		case 3:
			m_score += 5;
			if (rand() % 2 == 0) GetAProp();		//����3��1/2�ĸ��ʻ�õ���
			break;
		case 4:
			m_score += 8;
			GetAProp();		//����4�бض����һ������
			break;
		default: break;
	}
	CalculateLevel();		//����ȼ�
}

void CUI::GetAProp()
{
	SYSTEMTIME current_time;
	GetLocalTime(&current_time);			//��ȡ��ǰʱ��
	srand(current_time.wMilliseconds);		//�õ�ǰʱ��ĺ��������ò��������������
	//������һ�����ߣ��������������999��
	switch(rand() % 3)
	{
		case 0: if (m_strip_number < 1000) m_strip_number++; break;
		case 1: if (m_bomb_number < 1000) m_bomb_number++; break;
		case 2: if (m_pierce_number < 1000) m_pierce_number++; break;
	}
}

inline bool CUI::GameOver(Player player) const
{
	if (player == PLAYER1)
	{
		if (CurrentBlock1.GetBlockType() == B_BOMB) return false;		//��ǰ������ը��ʱ����ʹ��Ϸ����
		else return CurrentBlock1.BlockCollisionTest(m_board, m_width);		//�����ǰ������һ������ʱ��ͼ�⵽��ײ������Ϸ����
	}
	else
	{
		if (CurrentBlock2.GetBlockType() == B_BOMB) return false;		//��ǰ������ը��ʱ����ʹ��Ϸ����
		else return CurrentBlock2.BlockCollisionTest(m_board, m_width);		//�����ǰ������һ������ʱ��ͼ�⵽��ײ������Ϸ����
	}
}


void CUI::SetNextBlock(Player player)
{
	SYSTEMTIME current_time;
	GetLocalTime(&current_time);			//��ȡ��ǰʱ��
	if (player == PLAYER1)
	{
		CurrentBlock1 = NextBlock1;
		srand(current_time.wMilliseconds);		//�õ�ǰʱ��ĺ��������ò��������������
		BlockType type{ static_cast<BlockType>(rand() % 7) };
		NextBlock1 = CBlock(type, static_cast<Direction>(rand() % 4), m_color_table[type], m_double_player ? m_block1_x : m_width / 2 - 1);		//�������������һ����������ͺͳ���
	}
	else
	{
		CurrentBlock2 = NextBlock2;
		srand(current_time.wMilliseconds);		//�õ�ǰʱ��ĺ��������ò��������������
		BlockType type{ static_cast<BlockType>(rand() % 7) };
		NextBlock2 = CBlock(type, static_cast<Direction>(rand() % 4), m_color_table[type], m_block2_x);		//�������������һ����������ͺͳ���
	}
}


void CUI::KeyDetect(int key)
{
	if (key == m_1_left_key)
	{
		CurrentBlock1.MoveBlock(LEFT, m_board, m_width);		//ִ�����Ʋ���
	}
	else if (key == m_1_right_key)
	{
		CurrentBlock1.MoveBlock(RIGHT, m_board, m_width);	//ִ�����Ʋ���
	}
	else if (key == m_1_down_key)
	{
		CurrentBlock1.MoveBlock(DOWN, m_board, m_width);		//ִ�����Ʋ���
	}
	else if (key == m_1_rotate_key)
	{
		if (m_sound_effect) PlaySound(_T("./sound/rotate.wav"), NULL, SND_ASYNC | SND_FILENAME);
		CurrentBlock1.RotateBlock(m_board, m_width);		//ִ����ת����
	}
	else if (key == m_1_sink_key)
	{
		while (!BlockLandTest(PLAYER1))			//�����³���ʱһֱִ�����²�����ֱ����������Ϊֹ
			CurrentBlock1.MoveBlock(DOWN, m_board, m_width);
		CurrentBlock1.MoveBlock(DOWN, m_board, m_width);		//whileѭ������֮����ִ��һ���������
	}
	else if (key == m_2_left_key && m_double_player)
	{
		CurrentBlock2.MoveBlock(LEFT, m_board, m_width);		//ִ�����Ʋ���
	}
	else if (key == m_2_right_key && m_double_player)
	{
		CurrentBlock2.MoveBlock(RIGHT, m_board, m_width);	//ִ�����Ʋ���
	}
	else if (key == m_2_down_key && m_double_player)
	{
		CurrentBlock2.MoveBlock(DOWN, m_board, m_width);		//ִ�����Ʋ���
	}
	else if (key == m_2_rotate_key && m_double_player)
	{
		if (m_sound_effect) PlaySound(_T("./sound/rotate.wav"), NULL, SND_ASYNC | SND_FILENAME);
		CurrentBlock2.RotateBlock(m_board, m_width);		//ִ����ת����
	}
	else if (key == m_2_sink_key && m_double_player)
	{
		while (!BlockLandTest(PLAYER2))			//�����³���ʱһֱִ�����²�����ֱ����������Ϊֹ
			CurrentBlock2.MoveBlock(DOWN, m_board, m_width);
		CurrentBlock2.MoveBlock(DOWN, m_board, m_width);		//whileѭ������֮����ִ��һ���������
	}
	else
	{
		switch (key)
		{
			case CHEAT_KEY:		//�������׼��������ȡһ������
				GetAProp();
				ShowInfo();
				break;
			case LEVELUP_KEY:		//���¡�һ������������������1������ĵ÷�
				m_score += m_score_per_level;
				CalculateLevel();
				ShowInfo();
				break;
			case PLAYER1_STRIP1_KEY:		//���µ���1����ʹ�ó�������
				if (m_strip_number > 0 && NextBlock1.GetBlockType() != B_I)
				{
					NextBlock1 = CBlock(B_I, static_cast<Direction>(rand() % 4), m_color_table[B_I], m_block1_x);
					m_strip_number--;
					ShowInfo();
				}
				break;
			case PLAYER1_STRIP2_KEY:		//���µ���2����ʹ��ը������
				if (m_bomb_number > 0 && NextBlock1.GetBlockType() != B_BOMB)
				{
					NextBlock1 = CBlock(B_BOMB, UP, m_color_table[B_BOMB], m_block1_x);
					m_bomb_number--;
					ShowInfo();
				}
				break;
			case PLAYER1_STRIP3_KEY:		//���µ���3����ʹ�ô��׵�����
				if (m_pierce_number > 0 && NextBlock1.GetBlockType() != B_PIERCE)
				{
					NextBlock1 = CBlock(B_PIERCE, UP, m_color_table[B_PIERCE], m_block1_x);
					m_pierce_number--;
					ShowInfo();
				}
				break;
			case PLAYER2_STRIP1_KEY:		//���µ���1����ʹ�ó�������
				if (m_strip_number > 0 && NextBlock2.GetBlockType() != B_I && m_double_player)
				{
					NextBlock2 = CBlock(B_I, static_cast<Direction>(rand() % 4), m_color_table[B_I], m_block2_x);
					m_strip_number--;
					ShowInfo();
				}
				break;
			case PLAYER2_STRIP2_KEY:		//���µ���2����ʹ��ը������
				if (m_bomb_number > 0 && NextBlock2.GetBlockType() != B_BOMB && m_double_player)
				{
					NextBlock2 = CBlock(B_BOMB, UP, m_color_table[B_BOMB], m_block2_x);
					m_bomb_number--;
					ShowInfo();
				}
				break;
			case PLAYER2_STRIP3_KEY:		//���µ���3����ʹ�ô��׵�����
				if (m_pierce_number > 0 && NextBlock2.GetBlockType() != B_PIERCE && m_double_player)
				{
					NextBlock2 = CBlock(B_PIERCE, UP, m_color_table[B_PIERCE], m_block2_x);
					m_pierce_number--;
					ShowInfo();
				}
				break;
			case PAUSE_KEY:		//������ͣ����ִ����ͣʱ�Ĵ���
				Pause();
				ClearCurrentBlock(PLAYER1, true);
				ClearCurrentBlock(PLAYER2, true);
				system("cls");
				ShowInfo();				//����ͣ״̬�ָ�����½�����Ϣ
				if (m_invisible_mode && m_load_flag == true)		//����ģʽ�����ִ������������������ͣ״̬�ָ�����ʾ����500����
				{
					DrawBoardVisible();
					Sleep(500);
					m_load_flag = false;
				}
				DrawBoard();
				break;
			default: break;
		}
	}
}

void CUI::ShowInfo() const
{
	const int x_left_info{ 1 };		//�����Ϣ����ʼx����
	const int y_left_info{ 4 };		//�����Ϣ����ʼy����
	const int x_right_info{ 29 };		//�Ҳ���Ϣ����ʼx����
	const int y_right_info{ 3 };		//�Ҳ���Ϣ����ʼy����
	PrintString(L"����˹����    �汾��", 2, 0, WHITE);
	PrintString(L"1.93", 12, 0, YELLOW);
	PrintString(L"���ߣ�ZY    ���䣺380526481@qq.com", 16, 0, WHITE);
	PrintString(L"�÷֣�", x_left_info, y_left_info, WHITE);
	PrintInt(m_score, x_left_info + 3, y_left_info, CYAN);
	if (m_allow_level_up)		//ֻ����������ʱ����ʾ�ȼ���Ϣ
	{
		PrintString(L"�ȼ���", x_left_info, y_left_info + 2, WHITE);
		PrintInt(m_level, x_left_info + 3, y_left_info + 2, CYAN);
	}
	
	if (m_strip_number > 0)
	{
		PrintString(L"1.����", x_left_info, y_left_info + 6, GREEN);
		PrintString(L"��", x_left_info + 3, y_left_info + 6, YELLOW);
		PrintString(L"   ", x_left_info + 4, y_left_info + 6, WHITE);
		PrintInt(m_strip_number, x_left_info + 4, y_left_info + 6, YELLOW);
	}
	else PrintString(L"           ", x_left_info, y_left_info + 6, WHITE);
	if (m_bomb_number > 0)
	{
		PrintString(L"2.ը��", x_left_info, y_left_info + 7, GREEN);
		PrintString(L"��", x_left_info + 3, y_left_info + 7, YELLOW);
		PrintString(L"   ", x_left_info + 4, y_left_info + 7, WHITE);
		PrintInt(m_bomb_number, x_left_info + 4, y_left_info + 7, YELLOW);
	}
	else PrintString(L"           ", x_left_info, y_left_info + 7, WHITE);
	if (m_pierce_number > 0)
	{
		PrintString(L"3.���׵�", x_left_info, y_left_info + 8, GREEN);
		PrintString(L"��", x_left_info + 4, y_left_info + 8, YELLOW);
		PrintString(L"   ", x_left_info + 5, y_left_info + 8, WHITE);
		PrintInt(m_pierce_number, x_left_info + 5, y_left_info + 8, YELLOW);
	}
	else PrintString(L"             ", x_left_info, y_left_info + 8, WHITE);

	PrintString(m_double_player ? L"���1��һ�����飺" : L"��һ�����飺", x_right_info, y_right_info, WHITE);
	NextBlock1.PrintBlock(x_right_info + 1, y_right_info + 2);	//������1����һ������

	if (m_double_player)		//ֻ��˫��ģʽ�²���ʾ���2����һ������
	{
		PrintString(L"���2��һ�����飺", x_right_info, y_right_info+7, WHITE);
		NextBlock2.PrintBlock(x_right_info + 1, y_right_info + 9);	//������2����һ������
	}

	PrintString(L"������", x_right_info, y_right_info + 14, WHITE);
	PrintString(L"���س�����ͣ��", x_right_info, y_right_info + 15, WHITE);
	PrintString(L"��ESC���˳���", x_right_info, y_right_info + 16, WHITE);
	PrintString(L"��O������ѡ�����ã�", x_right_info, y_right_info + 17, WHITE);
	PrintString(L"��H���鿴��ϸ������Ϣ��", x_right_info, y_right_info + 18, WHITE);
}

void CUI::ShowHelpInfo() const
{
	const int x{ 9 }, y{ 3 };		//ѡ������ַ��������ʼλ��
	system("cls");
	PrintString(L"��ϸ����", x, y, CYAN);
	PrintString(L"���1Ĭ�ϰ�����", x, y + 2, WHITE);
	PrintString(L"A�����ƣ�D�����ƣ�S�����ƣ�W����ת���ո�ֱ������", x, y + 3, WHITE);
	PrintString(L"���2Ĭ�ϰ�����", x, y + 4, WHITE);
	PrintString(L"�������ƣ��������ƣ��������ƣ�������ת��/��ֱ������", x, y + 5, WHITE);
	PrintString(L"���1��1��2��3��ʹ�õ��ߣ����2��8��9��0��ʹ�õ���", x, y + 6, WHITE);
	PrintString(L"��ESC�����ء�", x, y + 8, GRAY);
	while (GetKey() != QUIT_KEY) {}
	system("cls");
}

bool CUI::ShowGameOver() const
{
	int i, j;
	for (i = 0; i < m_width; i++)
		for (j = 0; j < HEIGHT; j++)
			PrintCell(m_board[i][j], i + m_board_x, j + BOARD_Y, RED);
	PrintString(L"               Game Over!               ", BOARD_X, BOARD_Y + 10, RED);
	PrintString(L"          �Ƿ����?��(Y)|��(N)          ", BOARD_X, BOARD_Y + 11, RED);
	while (true)
	{
		switch (GetKey())
		{
			case 'Y': return true;
			case 'N': case QUIT_KEY: return false;
			default: break;
		}
	}
}


void CUI::ShowPause() const
{
	int i, j;
	for (i = 0; i < m_width; i++)
		for (j = 0; j < HEIGHT; j++)
			PrintCell(m_board[i][j], i + m_board_x, j + BOARD_Y, CYAN);
	PrintString(L"        ����ͣ�����س�����������        ", BOARD_X, BOARD_Y+9, CYAN);
	PrintString(L"      S������    L������    O��ѡ��     ", BOARD_X, BOARD_Y + 10, CYAN);
}

void CUI::Pause()
{
	ShowInfo();
	ShowPause();		//��ʾ��Ϸ��ͣʱ�Ľ���
	int key;
	while (true)
	{
		key = GetKey();
		if (key == QUIT_KEY || key == PAUSE_KEY)		//��ESC������ͣ������
		{
			break;
		}
		if (key == 'S')		//��S������
		{
			ClearCurrentBlock(PLAYER1, false);		//����ǰ����Ҫ�������ǰ����
			ClearCurrentBlock(PLAYER2, false);
			SaveData();
			PrintString(L"                �ѱ��档                ", BOARD_X, BOARD_Y+11, CYAN);
		}
		if (key == 'L')		//��L������
		{
			LoadData();
			PrintString(L"                �����롣                ", BOARD_X, BOARD_Y + 11, CYAN);
			SetNextBlock(PLAYER1);			//����֮��������ǰ���飬������һ������
			SetNextBlock(PLAYER2);
			m_load_flag = true;
		}
		if (key == 'O')		//��O������ѡ������
		{
			OptionSettings();
			ShowInfo();
			ShowPause();
		}
	}
}

int CUI::GetIntervalTime() const
{
	switch (m_level)
	{
		case 1: return 1000;
		case 2: return 800;
		case 3: return 650;
		case 4: return 500;
		case 5: return 400;
		case 6: return 320;
		case 7: return 250;
		case 8: return 190;
		default: return 150;
	}
}

void CUI::SaveData() const
{
	ofstream SaveFile{ "GameData.dat" };
	for (int j{ 0 }; j < HEIGHT; j++)
	{
		for (int i{ 0 }; i < WIDTH; i++)
		{
			if(m_board[i][j].type == FULL_CELL)
				SaveFile << 1;
			else SaveFile << 0;
			switch (m_board[i][j].color)
			{
				case	BLUE: SaveFile << 'B'; break;
				case GREEN: SaveFile << 'G'; break;
				case CYAN: SaveFile << 'C'; break;
				case RED: SaveFile << 'R'; break;
				case PURPLE: SaveFile << 'P'; break;
				case YELLOW: SaveFile << 'Y'; break;
				case WHITE: SaveFile << 'W'; break;
				default: SaveFile << 'N'; break;
			}
		}
	}
	SaveFile << m_score;
	SaveFile << ',';
	SaveFile << m_strip_number;
	SaveFile << ',';
	SaveFile << m_bomb_number;
	SaveFile << ',';
	SaveFile << m_pierce_number;
	SaveFile << ',';
	SaveFile.close();
}

void CUI::LoadData()
{
	ifstream OpenFile{ "GameData.dat" };
	char ch;
	//��ȡ����ÿ������״̬
	for (int j{ 0 }; j < HEIGHT; j++)
	{
		for (int i{ 0 }; i < WIDTH; i++)
		{
			OpenFile.get(ch);
			if (ch == '1')
				m_board[i][j].type = FULL_CELL;
			else
				m_board[i][j].type = EMPTY_CELL;
			OpenFile.get(ch);
			switch (ch)
			{
				case 'B': m_board[i][j].color = BLUE; break;
				case 'G': m_board[i][j].color = GREEN; break;
				case 'C': m_board[i][j].color = CYAN; break;
				case 'R': m_board[i][j].color = RED; break;
				case 'P': m_board[i][j].color = PURPLE; break;
				case 'Y': m_board[i][j].color = YELLOW; break;
				case 'W': m_board[i][j].color = WHITE; break;
				default:	 m_board[i][j].color = GRAY; break;
			}
		}
	}
	int i{ 0 };
	char str[10];
	//��ȡ�÷�
	do OpenFile.get(str[i++]);
	while (str[i - 1] != ',' &&i < 10);
	str[i - 1] = '\0';
	m_score = atoi(str);		//����ȡ�����ַ���ת�������ֱ��浽m_score��
	if (m_score < 0) m_score = 0;
	//��ȡ�������ߵĸ���
	i = 0;
	do OpenFile.get(str[i++]);
	while (str[i - 1] != ',' &&i < 10);
	str[i - 1] = '\0';
	m_strip_number = atoi(str);
	if (m_strip_number > 999) m_strip_number = 999;
	//��ȡը�����ߵĸ���
	i = 0;
	do OpenFile.get(str[i++]);
	while (str[i - 1] != ',' &&i < 10);
	str[i - 1] = '\0';
	m_bomb_number = atoi(str);
	if (m_bomb_number > 999) m_bomb_number = 999;
	//��ȡ���׵����ߵĸ���
	i = 0;
	do OpenFile.get(str[i++]);
	while (str[i - 1] != ',' &&i < 10);
	str[i - 1] = '\0';
	m_pierce_number = atoi(str);
	if (m_pierce_number > 999) m_pierce_number = 999;
	OpenFile.close();
}

void CUI::SaveSettings() const
{
	WriteIntToIni("����", "��������", m_clear_animation);
	WriteIntToIni("����", "�����������ʱ��", m_clear_animation_speed);
	WriteIntToIni("����", "��������", m_allow_level_up);
	WriteIntToIni("����", "����1������÷�", m_score_per_level);
	WriteIntToIni("����", "�Զ��浵", m_atuo_save);
	WriteIntToIni("����", "����ģʽ", m_invisible_mode);
	WriteIntToIni("����", "����ģʽ�Ѷ�", m_invisible_mode_difficulty);
	WriteIntToIni("����", "˫��ģʽ", m_double_player);
	WriteIntToIni("����", "������ʾ�Ŀ��", m_width);
	WriteIntToIni("����", "��Ϸ��Ч", m_sound_effect);

	WriteIntToIni("��ɫ����", "I�ͷ�����ɫ", m_color_table[0]);
	WriteIntToIni("��ɫ����", "L�ͷ�����ɫ", m_color_table[1]);
	WriteIntToIni("��ɫ����", "J�ͷ�����ɫ", m_color_table[2]);
	WriteIntToIni("��ɫ����", "Z�ͷ�����ɫ", m_color_table[3]);
	WriteIntToIni("��ɫ����", "S�ͷ�����ɫ", m_color_table[4]);
	WriteIntToIni("��ɫ����", "T�ͷ�����ɫ", m_color_table[5]);
	WriteIntToIni("��ɫ����", "O�ͷ�����ɫ", m_color_table[6]);
	
	WriteIntToIni("��������", "���1���Ƽ�", m_1_left_key);
	WriteIntToIni("��������", "���1���Ƽ�", m_1_right_key);
	WriteIntToIni("��������", "���1���Ƽ�", m_1_down_key);
	WriteIntToIni("��������", "���1��ת��", m_1_rotate_key);
	WriteIntToIni("��������", "���1ֱ�������", m_1_sink_key);
	WriteIntToIni("��������", "���2���Ƽ�", m_2_left_key);
	WriteIntToIni("��������", "���2���Ƽ�", m_2_right_key);
	WriteIntToIni("��������", "���2���Ƽ�", m_2_down_key);
	WriteIntToIni("��������", "���2��ת��", m_2_rotate_key);
	WriteIntToIni("��������", "���2ֱ�������", m_2_sink_key);
}

void CUI::LoadSettings()
{
	m_clear_animation = (GetIntFromIni("����", "��������", 1) != 0);
	m_clear_animation_speed = GetIntFromIni("����", "�����������ʱ��", 40);
	if (m_clear_animation_speed < 5) m_clear_animation_speed = 40;		//��������˷Ƿ���ֵ�������ó�Ĭ��ֵ
	m_allow_level_up = (GetIntFromIni("����", "��������", 1) != 0);
	m_score_per_level = GetIntFromIni("����", "����1������÷�", 150);
	if (m_score_per_level < 1) m_score_per_level = 150;		//��������˷Ƿ���ֵ�������ó�Ĭ��ֵ
	m_atuo_save = (GetIntFromIni("����", "�Զ��浵", 0) != 0);
	m_invisible_mode = (GetIntFromIni("����", "����ģʽ", 0) != 0);
	m_invisible_mode_difficulty = GetIntFromIni("����", "����ģʽ�Ѷ�", 0);
	if (m_invisible_mode_difficulty > 2) m_invisible_mode_difficulty = 2;
	if (m_invisible_mode_difficulty < 0) m_invisible_mode_difficulty = 0;
	m_double_player = (GetIntFromIni("����", "˫��ģʽ", 0) != 0);
	m_width = GetIntFromIni("����", "������ʾ�Ŀ��", 10);
	if (m_width < 10) m_width = 10;
	if (m_width > 20) m_width = 20;
	m_sound_effect = (GetIntFromIni("����", "��Ϸ��Ч", 1) != 0);

	m_color_table[0] = static_cast<Color>(GetIntFromIni("��ɫ����", "I�ͷ�����ɫ", WHITE));
	m_color_table[1] = static_cast<Color>(GetIntFromIni("��ɫ����", "L�ͷ�����ɫ", RED));
	m_color_table[2] = static_cast<Color>(GetIntFromIni("��ɫ����", "J�ͷ�����ɫ", GREEN));
	m_color_table[3] = static_cast<Color>(GetIntFromIni("��ɫ����", "Z�ͷ�����ɫ", BLUE));
	m_color_table[4] = static_cast<Color>(GetIntFromIni("��ɫ����", "S�ͷ�����ɫ", YELLOW));
	m_color_table[5] = static_cast<Color>(GetIntFromIni("��ɫ����", "T�ͷ�����ɫ", CYAN));
	m_color_table[6] = static_cast<Color>(GetIntFromIni("��ɫ����", "O�ͷ�����ɫ", PURPLE));
	
	m_1_left_key = GetIntFromIni("��������", "���1���Ƽ�", 'A');
	m_1_right_key = GetIntFromIni("��������", "���1���Ƽ�", 'D');
	m_1_down_key = GetIntFromIni("��������", "���1���Ƽ�", 'S');
	m_1_rotate_key = GetIntFromIni("��������", "���1��ת��", 'W');
	m_1_sink_key = GetIntFromIni("��������", "���1ֱ�������", SPACE_KEY);
	m_2_left_key = GetIntFromIni("��������", "���2���Ƽ�", LEFT_KEY);
	m_2_right_key = GetIntFromIni("��������", "���2���Ƽ�", RIGHT_KEY);
	m_2_down_key = GetIntFromIni("��������", "���2���Ƽ�", DOWN_KEY);
	m_2_rotate_key = GetIntFromIni("��������", "���2��ת��", UP_KEY);
	m_2_sink_key = GetIntFromIni("��������", "���2ֱ�������", '/');
}

inline void CUI::ShowSettingsInfo(int x, int y) const
{
	system("cls");
	PrintString(L"ѡ������", x, y, CYAN);
	PrintString(L"1����ʾ����������", x, y+2, WHITE);
	PrintString(L"2�������������ʱ�䣨��λ��ms����", x, y + 3, WHITE);
	PrintString(L"3������������", x, y + 4, WHITE);
	PrintString(L"4������1������ĵ÷֣�", x, y + 5, WHITE);
	PrintString(L"5���˳�ʱ�Զ��浵��", x, y + 6, WHITE);
	PrintString(L"6������ģʽ��", x, y + 7, WHITE);
	PrintString(L"7������ģʽ�Ѷȣ�", x, y + 8, WHITE);
	PrintString(L"8��������ɫ����", x, y + 9, WHITE);
	PrintString(L"9����λ����", x, y + 10, WHITE);
	PrintString(L"10��˫��ģʽ��", x, y + 11, WHITE);
	PrintString(L"11�������ȣ�", x, y + 12, WHITE);
	PrintString(L"12����Ϸ��Ч��", x, y + 13, WHITE);

	PrintString(L"�����·����ѡ����Ŀ���س���ȷ�ϣ�ESC������", x, y+16, GRAY);
}

void CUI::OptionSettings()
{
	const int x{ 9 }, y{ 3 };		//ѡ������ַ��������ʼλ��
	int item_select{ 1 };		//ѡ�е���Ŀ
	const int max_selection{ 12 };		//ѡ������
	ShowSettingsInfo(x, y);		//��ʾѡ������й̶�����Ϣ
	
	while (true)
	{
		//��ʾѡ���������Ҫ�仯����Ϣ
		PrintString(m_clear_animation ? L"��" : L"��", x + 9, y + 2, YELLOW);
		PrintInt(m_clear_animation_speed, x + 17, y + 3, YELLOW);
		PrintString(m_allow_level_up ? L"��" : L"��", x + 7, y + 4, YELLOW);
		PrintInt(m_score_per_level, x + 12, y + 5, YELLOW);
		PrintString(m_atuo_save ? L"��" : L"��", x + 10, y + 6, YELLOW);
		PrintString(m_invisible_mode ? L"��" : L"��", x + 7, y + 7, YELLOW);
		switch(m_invisible_mode_difficulty)
		{
			case 0: PrintString(L"��", x + 9, y + 8, YELLOW); break;
			case 1: PrintString(L"��", x + 9, y + 8, YELLOW); break;
			case 2: PrintString(L"��", x + 9, y + 8, YELLOW); break;
			default: break;
		}
		PrintString(m_double_player ? L"��" : L"��", x + 7, y + 11, YELLOW);
		PrintInt(m_width, x + 7, y + 12, YELLOW);
		PrintString(m_sound_effect ? L"��" : L"��", x + 7, y + 13, YELLOW);

		//���ѡ��ָʾ�ַ�
		for (int i{ 1 }; i <= max_selection; i++)
			PrintString(L"  ", x - 2, y + 1 + i, WHITE);		//�������ѡ��ָʾ�ַ�����������ո�
		PrintString(L"��", x - 2, y + 1 + item_select, CYAN);

		switch (GetKey())
		{
			case UP_KEY: 
				item_select--;
				if (item_select < 1) item_select = max_selection;
				break;
			case DOWN_KEY:
				item_select++;
				if (item_select > max_selection) item_select = 1;
				break;
			case ENTER_KEY: case LEFT_KEY: case RIGHT_KEY:
				switch (item_select)
				{
					case 1: m_clear_animation = !m_clear_animation; break;
					case 2: 
						GotoXY(x + 17, y + 3);
						CursorVisible(true);
						std::cin >> m_clear_animation_speed;
						if (m_clear_animation_speed < 5) m_clear_animation_speed = 5;		//���������ļ��ʱ�䲻����С��5����
						if (m_clear_animation_speed > 9999) m_clear_animation_speed = 9999;		//���������ļ��ʱ�䲻�������9999����
						CursorVisible(false);
						PrintString(L"          ", x + 17, y + 3, WHITE);		//�ÿո񸲸ǵ�ԭ�����ַ�
						break;
					case 3:
						m_allow_level_up = !m_allow_level_up;
						CalculateLevel();
						break;
					case 4:
						GotoXY(x + 12, y + 5);
						CursorVisible(true);
						std::cin >> m_score_per_level;
						if (m_score_per_level < 1) m_score_per_level = 1;		//ÿ��һ����Ҫ�ĵ÷ֲ�����С��1
						CalculateLevel();
						CursorVisible(false);
						PrintString(L"          ", x + 12, y + 5, WHITE);			//�ÿո񸲸ǵ�ԭ�����ַ�
						break;
					case 5:
						m_atuo_save = !m_atuo_save;
						break;
					case 6:
						m_invisible_mode = !m_invisible_mode;
						break;
					case 7:
						m_invisible_mode_difficulty ++;
						if (m_invisible_mode_difficulty > 2) m_invisible_mode_difficulty = 0;
						break;
					case 8:
						ColorSettings();
						ShowSettingsInfo(x, y);			//����ɫ���õĶ����˵��˳�����ˢ��һ����Ϣ
						break;
					case 9:
						KeySettings();
						ShowSettingsInfo(x, y);			//�Ӽ�λ���õĶ����˵��˳�����ˢ��һ����Ϣ
						break;
					case 10:
						m_double_player = !m_double_player;
						NextBlock1.SetXPosition(m_double_player ? m_block1_x : m_width / 2 - 1);		//�л�����/˫��ģʽ�������������1��һ�������λ��
						if (m_double_player)
						{
							NextBlock2.SetXPosition(m_block2_x);		//���ӵ���ģʽ�л�Ϊ˫��ģʽʱ����һ�������xλ������Ϊ˫��ģʽ�µ�λ��
							SetNextBlock(PLAYER2);		//�������2�ĵ�ǰ���飬�趨��һ������
						}
						break;
					case 11:
						//���ڸı�����ȿ���Ҫ�ı䵱ǰ�����λ�ã�������Ҫ�ڿ�ȸı�ǰ�������ǰ����
						ClearCurrentBlock(PLAYER1, false);
						ClearCurrentBlock(PLAYER2, false);

						GotoXY(x + 7, y + 12);
						CursorVisible(true);
						std::cin >> m_width;
						if (m_width < 10) m_width = 10;
						if (m_width > 20) m_width = 20;
						CursorVisible(false);
						PrintString(L"  ", x + 7, y + 12, WHITE);			//�ÿո񸲸ǵ�ԭ�����ַ�

						CalculateBoardXAndBlockPosition();
						NextBlock1.SetXPosition(m_double_player ? m_block1_x : m_width / 2 - 1);		//�޸Ľ����Ⱥ�����������һ�������λ��
						NextBlock2.SetXPosition(m_block2_x);
						//�����õĽ����ȱ�ԭ��Сʱ�������ǰ�����Ѿ��ڽ������棬��Ҫ�����ƶ������棬��ֹ�ж�Ϊ��Ϸ����
						if (CurrentBlock1.BlockCollisionTest(m_board, m_width))
							CurrentBlock1.SetXPosition(m_double_player ? m_block1_x : m_width / 2 - 1);
						if (CurrentBlock2.BlockCollisionTest(m_board, m_width))
							CurrentBlock2.SetXPosition(m_block2_x);
						break;
					case 12:
						m_sound_effect = !m_sound_effect;
						break;
					default:
						break;
				}
				SaveSettings();		//ѡ�����ø��ĺ󱣴�����
				break;
			case QUIT_KEY:
				system("cls");
				return;
			default: break;
		}
	}
}

void CUI::ColorSettings()
{
	const int x{ 9 }, y{ 3 };		//ѡ������ַ��������ʼλ��
	const int max_selection{ 8 };		//ѡ������
	int color_select{ 1 };		//������ɫ������ѡ�е���Ŀ
	system("cls");
	//��ʾѡ������й̶�����Ϣ
	PrintString(L"������ɫ����", x, y, CYAN);
	PrintString(L"I�ͣ�", x, y + 2, WHITE);
	PrintString(L"L�ͣ�", x, y + 3, WHITE);
	PrintString(L"J�ͣ�", x, y + 4, WHITE);
	PrintString(L"Z�ͣ�", x, y + 5, WHITE);
	PrintString(L"S�ͣ�", x, y + 6, WHITE);
	PrintString(L"T�ͣ�", x, y + 7, WHITE);
	PrintString(L"O�ͣ�", x, y + 8, WHITE);
	PrintString(L"�ָ�Ĭ����ɫ", x, y + 9, WHITE);
	
	PrintString(L"�����·����ѡ����Ŀ�����ҷ����ѡ����ɫ��ESC������", x, y+12, GRAY);

	while (true)
	{
		//�����ɫ���õ�ѡ��ָʾ�ַ�
		for (int i{ 1 }; i <= max_selection; i++)
			PrintString(L"  ", x - 2, y + 1 + i, WHITE);
		PrintString(L"��", x - 2, y + 1 + color_select, CYAN);
		//��ʾѡ���������Ҫ�仯����Ϣ
		PrintColor(x + 3, y + 2, m_color_table[B_I]);
		PrintColor(x + 3, y + 3, m_color_table[B_L]);
		PrintColor(x + 3, y + 4, m_color_table[B_J]);
		PrintColor(x + 3, y + 5, m_color_table[B_Z]);
		PrintColor(x + 3, y + 6, m_color_table[B_S]);
		PrintColor(x + 3, y + 7, m_color_table[B_T]);
		PrintColor(x + 3, y + 8, m_color_table[B_O]);
		
		switch (GetKey())
		{
			case UP_KEY:
				color_select--;
				if (color_select < 1) color_select = max_selection;
				break;
			case DOWN_KEY:
				color_select++;
				if (color_select > max_selection) color_select = 1;
				break;
			case ENTER_KEY: case RIGHT_KEY:
				int temp;
				if (color_select == 8)		//ѡ���ˡ��ָ�Ĭ����ɫ��
				{
					m_color_table[B_I] = WHITE;
					m_color_table[B_L] = RED;
					m_color_table[B_J] = GREEN;
					m_color_table[B_Z] = BLUE;
					m_color_table[B_S] = YELLOW;
					m_color_table[B_T] = CYAN;
					m_color_table[B_O] = PURPLE;
				}
				else
				{
					temp = static_cast<int>(m_color_table[color_select-1]);			//����ö�����Ͳ����Լӣ������Ƚ���ɫ����ǿ��ת����int�ͣ��ԼӺ�ת������ɫ����
					temp++;
					m_color_table[color_select-1] = static_cast<Color>(temp);
					if (m_color_table[color_select-1] > WHITE)
						m_color_table[color_select-1] = GRAY;
				}
				break;
			case LEFT_KEY:
				if (color_select < 8)
				{
					temp = static_cast<int>(m_color_table[color_select - 1]);
					temp--;
					m_color_table[color_select - 1] = static_cast<Color>(temp);
					if (m_color_table[color_select - 1] < GRAY)
						m_color_table[color_select - 1] = WHITE;
				}
				break;
			case QUIT_KEY:
				return;
			default:
				break;
		}
	}
}

void CUI::KeySettings()
{
	const int x{ 9 }, y{ 3 };		//ѡ������ַ��������ʼλ��
	const int max_selection{ 11 };		//ѡ������
	int item_select{ 1 };		//��λ������ѡ�е���Ŀ
	system("cls");
	//��ʾѡ������й̶�����Ϣ
	PrintString(L"��λ����", x, y, CYAN);
	PrintString(L"���1���Ƽ���", x, y + 2, WHITE);
	PrintString(L"���1���Ƽ���", x, y + 3, WHITE);
	PrintString(L"���1���Ƽ���", x, y + 4, WHITE);
	PrintString(L"���1��ת����", x, y + 5, WHITE);
	PrintString(L"���1ֱ���������", x, y + 6, WHITE);
	PrintString(L"���2���Ƽ���", x, y + 7, WHITE);
	PrintString(L"���2���Ƽ���", x, y + 8, WHITE);
	PrintString(L"���2���Ƽ���", x, y + 9, WHITE);
	PrintString(L"���2��ת����", x, y + 10, WHITE);
	PrintString(L"���2ֱ���������", x, y + 11, WHITE);
	PrintString(L"�ָ�Ĭ���趨", x, y + 12, WHITE);
	
	PrintString(L"�����·����ѡ����Ŀ���س���������Ӧ�ļ�λ���ã�ESC������", x, y+15, GRAY);

	while (true)
	{
		//�����λ���õ�ѡ��ָʾ�ַ�
		for (int i{ 1 }; i <= max_selection; i++)
			PrintString(L"  ", x - 2, y + 1 + i, WHITE);
		PrintString(L"��", x - 2, y + 1 + item_select, CYAN);
		//��ʾѡ���������Ҫ�仯����Ϣ
		PrintKey(m_1_left_key, x + 7, y + 2, YELLOW);
		PrintKey(m_1_right_key, x + 7, y + 3, YELLOW);
		PrintKey(m_1_down_key, x + 7, y + 4, YELLOW);
		PrintKey(m_1_rotate_key, x + 7, y + 5, YELLOW);
		PrintKey(m_1_sink_key, x + 9, y + 6, YELLOW);
		PrintKey(m_2_left_key, x + 7, y + 7, YELLOW);
		PrintKey(m_2_right_key, x + 7, y + 8, YELLOW);
		PrintKey(m_2_down_key, x + 7, y + 9, YELLOW);
		PrintKey(m_2_rotate_key, x + 7, y + 10, YELLOW);
		PrintKey(m_2_sink_key, x + 9, y + 11, YELLOW);

		switch (GetKey())
		{
			case UP_KEY:
				item_select--;
				if (item_select < 1) item_select = max_selection;
				break;
			case DOWN_KEY:
				item_select++;
				if (item_select > max_selection) item_select = 1;
				break;
			case ENTER_KEY: case RIGHT_KEY:
				switch (item_select)
				{
					case 1:
						GotoXY(x + 7, y + 2);
						CursorVisible(true);
						while(true)
						{
							m_1_left_key = GetKey();
							if (IllegalControlKey(m_1_left_key))
								PrintString(L"�Ƿ����������������룡",x + 7, y + 2, RED);
							else break;
						}
						PrintString(L"                      ",x + 7, y + 2, WHITE);
						CursorVisible(false);
						break;
					case 2:
						GotoXY(x + 7, y + 3);
						CursorVisible(true);
						while(true)
						{
							m_1_right_key = GetKey();
							if (IllegalControlKey(m_1_right_key))
								PrintString(L"�Ƿ����������������룡",x + 7, y + 3, RED);
							else break;
						}
						PrintString(L"                      ",x + 7, y + 3, WHITE);
						CursorVisible(false);
						break;
					case 3:
						GotoXY(x + 7, y + 4);
						CursorVisible(true);
						while(true)
						{
							m_1_down_key = GetKey();
							if (IllegalControlKey(m_1_down_key))
								PrintString(L"�Ƿ����������������룡",x + 7, y + 4, RED);
							else break;
						}
						PrintString(L"                      ",x + 7, y + 4, WHITE);
						CursorVisible(false);
						break;
					case 4:
						GotoXY(x + 7, y + 5);
						CursorVisible(true);
						while(true)
						{
							m_1_rotate_key = GetKey();
							if (IllegalControlKey(m_1_rotate_key))
								PrintString(L"�Ƿ����������������룡",x + 7, y + 5, RED);
							else break;
						}
						PrintString(L"                      ",x + 7, y + 5, WHITE);
						CursorVisible(false);
						break;
					case 5:
						GotoXY(x + 9, y + 6);
						CursorVisible(true);
						while(true)
						{
							m_1_sink_key = GetKey();
							if (IllegalControlKey(m_1_sink_key))
								PrintString(L"�Ƿ����������������룡",x + 9, y + 6, RED);
							else break;
						}
						PrintString(L"                      ",x + 9, y + 6, WHITE);
						CursorVisible(false);
						break;
					case 6:
						GotoXY(x + 7, y + 7);
						CursorVisible(true);
						while (true)
						{
							m_2_left_key = GetKey();
							if (IllegalControlKey(m_2_left_key))
								PrintString(L"�Ƿ����������������룡", x + 7, y + 7, RED);
							else break;
						}
						PrintString(L"                      ", x + 7, y + 7, WHITE);
						CursorVisible(false);
						break;
					case 7:
						GotoXY(x + 7, y + 8);
						CursorVisible(true);
						while (true)
						{
							m_2_right_key = GetKey();
							if (IllegalControlKey(m_2_right_key))
								PrintString(L"�Ƿ����������������룡", x + 7, y + 8, RED);
							else break;
						}
						PrintString(L"                      ", x + 7, y + 8, WHITE);
						CursorVisible(false);
						break;
					case 8:
						GotoXY(x + 7, y + 9);
						CursorVisible(true);
						while (true)
						{
							m_2_down_key = GetKey();
							if (IllegalControlKey(m_2_down_key))
								PrintString(L"�Ƿ����������������룡", x + 7, y + 9, RED);
							else break;
						}
						PrintString(L"                      ", x + 7, y + 9, WHITE);
						CursorVisible(false);
						break;
					case 9:
						GotoXY(x + 7, y + 10);
						CursorVisible(true);
						while (true)
						{
							m_2_rotate_key = GetKey();
							if (IllegalControlKey(m_2_rotate_key))
								PrintString(L"�Ƿ����������������룡", x + 7, y + 10, RED);
							else break;
						}
						PrintString(L"                      ", x + 7, y + 10, WHITE);
						CursorVisible(false);
						break;
					case 10:
						GotoXY(x + 9, y + 11);
						CursorVisible(true);
						while (true)
						{
							m_2_sink_key = GetKey();
							if (IllegalControlKey(m_2_sink_key))
								PrintString(L"�Ƿ����������������룡", x + 9, y + 11, RED);
							else break;
						}
						PrintString(L"                      ", x + 9, y + 11, WHITE);
						CursorVisible(false);
						break;
					case 11:		//ѡ���ˡ��ָ�Ĭ���趨��
						m_1_left_key = 'A';
						m_1_right_key = 'D';
						m_1_down_key = 'S';
						m_1_rotate_key = 'W';
						m_1_sink_key = SPACE_KEY;
						m_2_left_key = LEFT_KEY;
						m_2_right_key = RIGHT_KEY;
						m_2_down_key = DOWN_KEY;
						m_2_rotate_key = UP_KEY;
						m_2_sink_key = '/';
						break;
				}
				break;
			case QUIT_KEY:
				return;
			default:
				break;
		}
	}
}

inline bool CUI::GetAutoSave() const
{
	return m_atuo_save;
}

inline int CUI::GetDownKey(Player player) const
{
	if (player == PLAYER1) return m_1_down_key;
	else return m_2_down_key;
}

inline bool CUI::KeyIsControlKey(int key) const
{
	return (key == m_1_left_key || key == m_1_right_key || key == m_1_down_key || key == m_1_rotate_key || key == m_1_sink_key ||
				key == m_2_left_key || key == m_2_right_key || key == m_2_down_key || key == m_2_rotate_key || key == m_2_sink_key ||
				key == CHEAT_KEY || key == LEVELUP_KEY || key == PAUSE_KEY ||
				key == PLAYER1_STRIP1_KEY || key == PLAYER1_STRIP2_KEY || key == PLAYER1_STRIP3_KEY ||
				key == PLAYER2_STRIP1_KEY || key == PLAYER2_STRIP2_KEY || key == PLAYER2_STRIP3_KEY);
}

inline bool CUI::DoublePlayer() const
{
	return m_double_player;
}

void CUI::CalculateBoardXAndBlockPosition()
{
	m_board_x = BOARD_X + 10 - m_width / 2;
	//BOARD_X + 10Ϊ��������λ�ã�Ϊ������Ϸ�����ڿ�ȱ仯��ʱ��ʼ��������λ�ã����ƽ������ʼλ��Ϊ����λ��-m_width/2
	m_block1_x = m_width / 4 - 1;
	m_block2_x = m_width / 4 * 3 - 1;
}