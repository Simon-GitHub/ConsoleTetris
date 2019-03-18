//************************************************************
//				���ļ�Ϊ����̨���ȫ�ֺ����Ķ���
//************************************************************
#pragma once
#include<Windows.h>
#include"Define.h"

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

//��x,y���괦�������ĸ���
void PrintCell(Cell cell, short x, short y)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	if (cell.type == FULL_CELL)
	{
		WriteConsoleOutputCharacterA(handle, "��", 2, pos, &unuse);
		FillConsoleOutputAttribute(handle, cell.color, 2, pos, &unuse);
	}
	else
	{
		WriteConsoleOutputCharacterA(handle, "��", 2, pos, &unuse);
		FillConsoleOutputAttribute(handle, GRAY, 2, pos, &unuse);
	}
}

//��x,y���괦�������ĸ��ӣ�ָ����ɫ��
void PrintCell(Cell cell, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	if (cell.type == FULL_CELL)
		WriteConsoleOutputCharacterA(handle, "��", 2, pos, &unuse);
	else
		WriteConsoleOutputCharacterA(handle, "��", 2, pos, &unuse);
	FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);
}


//�ڽ����x,y���괦���һ������
void PrintInt(int num, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	char str[20];
	_itoa_s(num, str, 10);
	size_t len{ strlen(str) };
	WriteConsoleOutputCharacterA(handle, str, len, pos, &unuse);		//����ַ�
	FillConsoleOutputAttribute(handle, color, len, pos, &unuse);		//������ɫ
}

//�ڽ����x,y���괦���һ���ַ���
void PrintString(char *str, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	size_t len{ strlen(str) };
	WriteConsoleOutputCharacterA(handle, str, len, pos, &unuse);
	FillConsoleOutputAttribute(handle, color, len, pos, &unuse);		//������ɫ
}

//����ƶ���x,y����
void GotoXY(short x, short y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//�ڽ����x,y�������ͬ��ɫ�ĺ���
void PrintColor(short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	switch (color)
	{
		case WHITE: WriteConsoleOutputCharacterA(handle, "��ɫ  ", 6, pos, &unuse); break;
		case RED: WriteConsoleOutputCharacterA(handle, "��ɫ  ", 6, pos, &unuse); break;
		case GREEN: WriteConsoleOutputCharacterA(handle, "��ɫ  ", 6, pos, &unuse); break;
		case BLUE: WriteConsoleOutputCharacterA(handle, "��ɫ  ", 6, pos, &unuse); break;
		case YELLOW: WriteConsoleOutputCharacterA(handle, "��ɫ  ", 6, pos, &unuse); break;
		case CYAN: WriteConsoleOutputCharacterA(handle, "����ɫ", 6, pos, &unuse); break;
		case PURPLE: WriteConsoleOutputCharacterA(handle, "��ɫ  ", 6, pos, &unuse); break;
		case GRAY:WriteConsoleOutputCharacterA(handle, "��ɫ  ", 6, pos, &unuse); break;
		default: break;
	}
	FillConsoleOutputAttribute(handle, color, 6, pos, &unuse);
}

//��ʾ�����ع��
void CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = visible;
	cci.dwSize = 25;		//����ȣ�ȡֵΪ1~100
	SetConsoleCursorInfo(handle, &cci);
}

//����ը��
void PrintBomb(int x, int y)
{
	PrintCell(Cell{ FULL_CELL, RED }, x, y);
	PrintCell(Cell{ FULL_CELL, GREEN }, x + 3, y);
	PrintCell(Cell{ FULL_CELL, BLUE }, x , y+ 3);
	PrintCell(Cell{ FULL_CELL, YELLOW }, x + 3, y + 3);
	PrintCell(Cell{ FULL_CELL, GRAY }, x + 1, y + 3);
	PrintCell(Cell{ FULL_CELL, GRAY }, x + 2, y + 3);

	PrintCell(Cell{ FULL_CELL, GREEN }, x + 1, y + 1);
	PrintCell(Cell{ FULL_CELL, RED }, x + 2, y + 1);
	PrintCell(Cell{ FULL_CELL, YELLOW }, x + 1, y + 2);
	PrintCell(Cell{ FULL_CELL, BLUE }, x + 2, y + 2);
}

//����ը��
void ClearBomb(int x, int y)
{
	PrintCell(Cell{ EMPTY_CELL, GRAY }, x, y);
	PrintCell(Cell{ EMPTY_CELL, GRAY }, x + 3, y);
	PrintCell(Cell{ EMPTY_CELL, GRAY }, x, y + 3);
	PrintCell(Cell{ EMPTY_CELL, GRAY }, x + 3, y + 3);
	PrintCell(Cell{ EMPTY_CELL, GRAY }, x + 1, y + 3);
	PrintCell(Cell{ EMPTY_CELL, GRAY }, x + 2, y + 3);

	PrintCell(Cell{ EMPTY_CELL, GRAY }, x + 1, y + 1);
	PrintCell(Cell{ EMPTY_CELL, GRAY }, x + 2, y + 1);
	PrintCell(Cell{ EMPTY_CELL, GRAY }, x + 1, y + 2);
	PrintCell(Cell{ EMPTY_CELL, GRAY }, x + 2, y + 2);
}

//�����ڼ�λ�趨�����һ����������Ϣ
void PrintKey(int key, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	char buf[2];
	/*if (IllegalControlKey(key))
	{
		WriteConsoleOutputCharacterA(handle, "�����Ƿ���", 10, pos, &unuse);
		FillConsoleOutputAttribute(handle, RED, 10, pos, &unuse);
	}*/
	if(key != UP_KEY && key != DOWN_KEY && key != LEFT_KEY && key != RIGHT_KEY && (key>127 || key<=0))
	{
		WriteConsoleOutputCharacterA(handle, "δ�趨", 6, pos, &unuse);
		FillConsoleOutputAttribute(handle, RED, 6, pos, &unuse);
		return;
	}
	switch (key)
	{
		case ENTER_KEY:
			WriteConsoleOutputCharacterA(handle, "�س���", 6, pos, &unuse);
			FillConsoleOutputAttribute(handle, color, 6, pos, &unuse);
			break;
		case ' ':
			WriteConsoleOutputCharacterA(handle, "�ո��", 6, pos, &unuse);
			FillConsoleOutputAttribute(handle, color, 6, pos, &unuse);
			break;
		case 9:
			WriteConsoleOutputCharacterA(handle, "Tab��", 5, pos, &unuse);
			FillConsoleOutputAttribute(handle, color, 5, pos, &unuse);
			break;
		case UP_KEY:
			WriteConsoleOutputCharacterA(handle, "��", 2, pos, &unuse);
			FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);
			break;
		case DOWN_KEY:
			WriteConsoleOutputCharacterA(handle, "��", 2, pos, &unuse);
			FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);
			break;
		case LEFT_KEY:
			WriteConsoleOutputCharacterA(handle, "��", 2, pos, &unuse);
			FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);
			break;
		case RIGHT_KEY:
			WriteConsoleOutputCharacterA(handle, "��", 2, pos, &unuse);
			FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);
			break;
		default:
			buf[0] = static_cast<char>(key);
			buf[1] = '\0';
			WriteConsoleOutputCharacterA(handle, buf, 1, pos, &unuse);
			FillConsoleOutputAttribute(handle, color, 1, pos, &unuse);
	}
}