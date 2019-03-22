#pragma once
#include"Define.h"
#include<fstream>
#include<iostream>
using std::ofstream;
using std::ifstream;

class CUI
{
private:
	Cell m_board[WIDTH][HEIGHT];		//���浱ǰ��Ϸ������10x20��ÿ�����ӵ�״̬����ɫ
	int m_x{ 0 };		//���λ��
	int m_y{ 0 };
	bool m_map_edit{ true };			//trueʱ�༭��ͼ��falseʱ�༭����
	int m_item_select{ 1 };			//ѡ�е���Ŀ
	const int m_max_item{ 4 };		//�ܵ�ѡ�����

	//ѡ����������
	int m_score{ 0 };		//��Ϸ�÷�
	int m_strip_number{ 0 };		//�������ߵ�����
	int m_bomb_number{ 0 };		//ը�����ߵ�����
	int m_pierce_number{ 0 };		//���׵����ߵ�����

	void DrawBoard() const;			//������Ϸ����
	void ShowInfo() const;			//��ʾ��Ϸ��Ϣ
	void ShowHelpInfo() const;		//��ʾ������Ϣ

public:
	CUI();
	void ShowFixedInfo() const;		//��ʾ�����й̶��������Ϣ
	void KeyDetect(int key);			//����������
	void SaveToFile() const;		//����Ϸ״̬���浽�ļ�
	void LoadFromFile();		//���ļ�������Ϸ״̬

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
}

void CUI::DrawBoard() const
{
	int i, j;
	for (i = 0; i < WIDTH; i++)
		for (j = 0; j < HEIGHT; j++)
			PrintCell(m_board[i][j], i + MAP_X, j + MAP_Y);
	GotoXY(m_x + MAP_X, m_y + MAP_Y);
}

void CUI::ShowFixedInfo() const
{
	PrintString("����˹����浵�༭��", SETTINGS_X, SETTINGS_Y + 14, WHITE);
	PrintString("�汾��1.3", SETTINGS_X, SETTINGS_Y + 15, WHITE);
	PrintString("�����ڶ���˹����汾�汾��1.92", SETTINGS_X, SETTINGS_Y + 16, GRAY);
	
	PrintString("��ͼ�༭", MAP_X, MAP_Y - 1, CYAN);
	PrintString("���ݱ༭", SETTINGS_X, SETTINGS_Y - 1, CYAN);

	PrintString("�÷֣�", SETTINGS_X, SETTINGS_Y + 2, WHITE);
	PrintString("��������������", SETTINGS_X, SETTINGS_Y + 3, WHITE);
	PrintString("ը������������", SETTINGS_X, SETTINGS_Y + 4, WHITE);
	PrintString("���׵�����������", SETTINGS_X, SETTINGS_Y + 5, WHITE);

	PrintString("��ʾ����H���鿴������", 24, 23, GRAY);

	DrawBoard();
	ShowInfo();
}

void CUI::ShowInfo() const
{
	PrintInt(m_score, SETTINGS_X + 3, SETTINGS_Y + 2, YELLOW);

	PrintInt(m_strip_number, SETTINGS_X + 7, SETTINGS_Y + 3, YELLOW);
	PrintInt(m_bomb_number, SETTINGS_X + 7, SETTINGS_Y + 4, YELLOW);
	PrintInt(m_pierce_number, SETTINGS_X + 8, SETTINGS_Y + 5, YELLOW);

	if (m_map_edit)
	{
		for (int i{ 0 }; i <= m_max_item; i++)
		{
			PrintString("  ", SETTINGS_X - 1, SETTINGS_Y + 1 + i, WHITE);
		}
		PrintString("  ", SETTINGS_X - 1, SETTINGS_Y - 1, WHITE);
		PrintString("��", MAP_X - 1, MAP_Y - 1, CYAN);
	}
	else
	{
		PrintString("  ", MAP_X - 1, MAP_Y - 1, WHITE);
		PrintString("��", SETTINGS_X - 1, SETTINGS_Y - 1, CYAN);
		for (int i{ 0 }; i <= m_max_item; i++)
		{
			PrintString("  ", SETTINGS_X - 1, SETTINGS_Y + 1 + i, WHITE);
		}
		PrintString("��", SETTINGS_X - 1, SETTINGS_Y + 1 + m_item_select, CYAN);
	}
}

void CUI::KeyDetect(int key)
{
	switch (key)
	{
		case TAB_KEY: 
			m_map_edit = !m_map_edit;
			ShowInfo();
			break;
		case 'H': case'h':
			ShowHelpInfo();
			ShowFixedInfo();
			ShowInfo();
			break;
		default:
			break;
	}
	if (m_map_edit)		//�༭��ͼ
	{
		CursorVisible(true);
		GotoXY(m_x + MAP_X, m_y + MAP_Y);
		switch (key)
		{
			case UP_KEY:
				m_y--;
				if (m_y < 0) m_y = HEIGHT - 1;
				break;
			case DOWN_KEY:
				m_y++;
				if (m_y >= HEIGHT) m_y = 0;
				break;
			case LEFT_KEY:
				m_x--;
				if (m_x < 0) m_x = WIDTH - 1;
				break;
			case RIGHT_KEY:
				m_x++;
				if (m_x >= WIDTH) m_x = 0;
				break;
			case SPACE_KEY:
				m_board[m_x][m_y].type = !m_board[m_x][m_y].type;
				//DrawBoard();
				PrintCell(m_board[m_x][m_y], m_x + MAP_X, m_y + MAP_Y);
				break;
			case 'W': case 'w': m_board[m_x][m_y].color = WHITE; PrintCell(m_board[m_x][m_y], m_x + MAP_X, m_y + MAP_Y); break;
			case 'R': case 'r': m_board[m_x][m_y].color = RED; PrintCell(m_board[m_x][m_y], m_x + MAP_X, m_y + MAP_Y); break;
			case 'G': case 'g': m_board[m_x][m_y].color = GREEN; PrintCell(m_board[m_x][m_y], m_x + MAP_X, m_y + MAP_Y); break;
			case 'B': case 'b': m_board[m_x][m_y].color = BLUE; PrintCell(m_board[m_x][m_y], m_x + MAP_X, m_y + MAP_Y); break;
			case 'Y': case 'y': m_board[m_x][m_y].color = YELLOW; PrintCell(m_board[m_x][m_y], m_x + MAP_X, m_y + MAP_Y); break;
			case 'C': case 'c': m_board[m_x][m_y].color = CYAN; PrintCell(m_board[m_x][m_y], m_x + MAP_X, m_y + MAP_Y); break;
			case 'P': case 'p': m_board[m_x][m_y].color = PURPLE; PrintCell(m_board[m_x][m_y], m_x + MAP_X, m_y + MAP_Y); break;
			case 'A':case'a': m_board[m_x][m_y].color = GRAY; PrintCell(m_board[m_x][m_y], m_x + MAP_X, m_y + MAP_Y); break;
			default:
				break;
		}
		GotoXY(m_x + MAP_X, m_y + MAP_Y);
	}
	else			//�༭����
	{
		CursorVisible(false);
		switch (key)
		{
			case UP_KEY:
				m_item_select--;
				if (m_item_select<1) m_item_select = m_max_item;
				break;
			case DOWN_KEY:
				m_item_select++;
				if (m_item_select > m_max_item) m_item_select = 1;
				break;
			case ENTER_KEY:case RIGHT_KEY:
				switch (m_item_select)
				{
					case 1:		//���õ÷�
						GotoXY(SETTINGS_X + 3, SETTINGS_Y + 2);
						CursorVisible(true);
						std::cin >> m_score;
						CursorVisible(false);
						PrintString("              ", SETTINGS_X + 3, SETTINGS_Y + 2, WHITE);		//����÷������ַ�
						break;
					case 2:
						m_strip_number++;
						break;
					case 3:
						m_bomb_number++;
						break;
					case 4:
						m_pierce_number++;
						break;
					default: break;
				}
				break;
			case LEFT_KEY:
				switch (m_item_select)
				{
					case 2:
						if (m_strip_number>0)
						{
							m_strip_number--;
							PrintString("              ", SETTINGS_X + 7, SETTINGS_Y + 3, WHITE);
						}
						break;
					case 3:
						if (m_bomb_number > 0)
						{
							m_bomb_number--;
							PrintString("              ", SETTINGS_X + 7, SETTINGS_Y + 4, WHITE);
						}
						break;
					case 4:
						if (m_pierce_number > 0)
						{
							m_pierce_number--;
							PrintString("              ", SETTINGS_X + 8, SETTINGS_Y + 5, WHITE);
						}
						break;
					default: break;
				}
			default: break;
		}
		ShowInfo();
	}
}

void CUI::ShowHelpInfo() const
{
	system("cls");
	CursorVisible(false);
	PrintString("����˹����浵�༭��    �汾��1.3", 4, 0, WHITE);
	PrintString("����", 3, 3, CYAN);
	PrintString("��TAB���ڵ�ͼ�༭ģʽ�����ñ༭ģʽ֮���л���", 3, 5, WHITE);
	PrintString("��ͼ�༭ģʽ��", 3, 7, YELLOW);
	PrintString("���ո��л��������ԣ�����Ӧ����ĸ�����ø�����ɫ��", 3, 8, WHITE);
	PrintString("R��G��B��Y��C��P��A���ֱ�Ϊ��ɫ����ɫ����ɫ����ɫ������ɫ����ɫ�ͻ�ɫ��", 3, 9, WHITE);
	PrintString("���ݱ༭ģʽ��", 3, 11, YELLOW);
	PrintString("�����·����ѡ����Ŀ�����س���ȷ�ϣ�", 3, 12, WHITE);
	PrintString("�������������а����ҷ�����ֱ�Ӽ���Ӧ����������", 3, 13, WHITE);
	PrintString("�밴ESC�����ء�", 3, 16, GRAY);
	while (true)
	{
		if (_getch() == QUIT_KEY)
		{
			system("cls");
			return;
		}
	}
}

void CUI::SaveToFile() const
{
	ofstream SaveFile{ "GameData.dat" };
	for (int j{ 0 }; j < HEIGHT; j++)
	{
		for (int i{ 0 }; i < WIDTH; i++)
		{
			if (m_board[i][j].type == FULL_CELL)
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
	// SaveFile << (m_invisible_mode ? 'Y' : 'N');
	// SaveFile << m_invisible_mode_difficulty;
	SaveFile.close();
}

void CUI::LoadFromFile()
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
	//��ȡը�����ߵĸ���
	i = 0;
	do OpenFile.get(str[i++]);
	while (str[i - 1] != ',' &&i < 10);
	str[i - 1] = '\0';
	m_bomb_number = atoi(str);
	//��ȡ���׵����ߵĸ���
	i = 0;
	do OpenFile.get(str[i++]);
	while (str[i - 1] != ',' &&i < 10);
	str[i - 1] = '\0';
	m_pierce_number = atoi(str);
	OpenFile.close();
}
