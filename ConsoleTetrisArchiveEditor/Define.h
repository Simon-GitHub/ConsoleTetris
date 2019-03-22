#pragma once
#include<Windows.h>
#define UP_KEY (-1)			//�����Ϸ����
#define DOWN_KEY (-2)		//�����·����
#define LEFT_KEY (-3)		//���������
#define RIGHT_KEY (-4)	//�����ҷ����
#define QUIT_KEY 27		//�����˳�������esc���˳���
#define SPACE_KEY ' '	//����ո��
#define TAB_KEY 9		//����tab��
#define ENTER_KEY 13		//����س���

#define FULL_CELL true		//��������ϵĸ�������״̬
#define EMPTY_CELL false		//��������ϵĸ��ӿյ�״̬
const int WIDTH{ 20 };
const int HEIGHT{ 23 };
const int MAP_X{ 2 };		//��ͼ�༭��ӡ����ʼx����
const int MAP_Y{ 1 };		//��ͼ�༭��ӡ����ʼy����
const int SETTINGS_X{ 24 };		//���ñ༭��ӡ����ʼx����
const int SETTINGS_Y{ 1 };		//���ñ༭��ӡ����ʼy����

using CellType = bool;		//�����ϵĸ��ӵ�״̬

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

enum Color
{
	GRAY = 8,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	WHITE
};

struct Cell
{
	CellType type;
	Color color;
};

//��x,y���괦�������ĸ���
void PrintCell(Cell cell, int x, int y)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	if (cell.type == FULL_CELL)
		WriteConsoleOutputCharacterA(h, "��", 2, pos, &unuse);
	else
		WriteConsoleOutputCharacterA(h, "��", 2, pos, &unuse);
	FillConsoleOutputAttribute(h, cell.color, 2, pos, &unuse);
}
/*
//��x,y���괦�������ĸ��ӣ�ָ����ɫ��
void PrintCell(Cell cell, int x, int y, Color color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	if (cell.type == FULL_CELL)
		WriteConsoleOutputCharacterA(h, "��", 2, pos, &unuse);
	else
		WriteConsoleOutputCharacterA(h, "��", 2, pos, &unuse);
	FillConsoleOutputAttribute(h, color, 2, pos, &unuse);
}*/


//�ڽ����x,y���괦���һ������
void PrintInt(int num, int x, int y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	char str[20];
	_itoa_s(num, str, 10);
	size_t len{ strlen(str) };
	WriteConsoleOutputCharacterA(h, str, len, pos, &unuse);		//����ַ�
	FillConsoleOutputAttribute(h, color, len, pos, &unuse);		//������ɫ
}

//�ڽ����x,y���괦���һ���ַ���
void PrintString(const char *str, int x, int y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	size_t len{ strlen(str) };
	WriteConsoleOutputCharacterA(h, str, len, pos, &unuse);
	FillConsoleOutputAttribute(h, color, len, pos, &unuse);		//������ɫ
}

//����ƶ���x,y����
void GotoXY(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(h, pos);
}

//��ʾ�����ع��
void CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = visible;
	cci.dwSize = 25;		//����ȣ�ȡֵΪ1~100
	SetConsoleCursorInfo(h, &cci);
}