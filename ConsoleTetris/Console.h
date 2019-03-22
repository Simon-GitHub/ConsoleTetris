//************************************************************
//				���ļ�Ϊ����̨���ȫ�ֺ����Ķ���
//************************************************************
#pragma once
#include<Windows.h>
#include"Define.h"

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

//����һ�����ֽ��ַ����ĳ���ռ�õİ���ַ���
size_t WcharStrHalfWidthLen(const wchar_t* str)
{
	size_t size{ 0 };
	const size_t length{ wcslen(str) };
	for (int i{ 0 }; i < length; i++)
	{
		if (str[i] >= 0 && str[i] < 128)
			size++;		//���һ��Unicode�ַ�������0~127��Χ�ڣ���ռһ������ַ����
		else
			size += 2;		//������ռ��������ַ����
	}
	return size;
}

//��x,y���괦�������ĸ���
void PrintCell(Cell cell, short x, short y)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	if (cell.type == FULL_CELL)
	{
		WriteConsoleOutputCharacterW(handle, L"��", 1, pos, &unuse);
		FillConsoleOutputAttribute(handle, cell.color, 2, pos, &unuse);
	}
	else
	{
		WriteConsoleOutputCharacterW(handle, L"��", 1, pos, &unuse);
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
		WriteConsoleOutputCharacterW(handle, L"��", 1, pos, &unuse);
	else
		WriteConsoleOutputCharacterW(handle, L"��", 1, pos, &unuse);
	FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);
}


//�ڽ����x,y���괦���һ������
void PrintInt(int num, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	wchar_t str[20];
	_itow_s(num, str, 10);
	size_t len{ wcslen(str) };
	WriteConsoleOutputCharacterW(handle, str, len, pos, &unuse);		//����ַ�
	FillConsoleOutputAttribute(handle, color, len, pos, &unuse);		//������ɫ
}

//�ڽ����x,y���괦���һ���ַ���
void PrintString(const wchar_t *str, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	size_t len{ wcslen(str) };
	size_t len_halfwidth{ WcharStrHalfWidthLen(str) };	//�ַ���ռ�ð���ַ���
	WriteConsoleOutputCharacterW(handle, str, len, pos, &unuse);
	FillConsoleOutputAttribute(handle, color, len_halfwidth, pos, &unuse);		//������ɫ
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
	switch (color)
	{
		case WHITE: PrintString(L"��ɫ  ", x, y, color); break;
		case RED: PrintString(L"��ɫ  ", x, y, color); break;
		case GREEN: PrintString(L"��ɫ  ", x, y, color); break;
		case BLUE: PrintString(L"��ɫ  ", x, y, color); break;
		case YELLOW: PrintString(L"��ɫ  ", x, y, color); break;
		case CYAN: PrintString(L"����ɫ", x, y, color); break;
		case PURPLE: PrintString(L"��ɫ  ", x, y, color); break;
		case GRAY:PrintString(L"��ɫ  ", x, y, color); break;
		default: break;
	}
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
	wchar_t buf[2];
	/*if (IllegalControlKey(key))
	{
		WriteConsoleOutputCharacterW(handle, "�����Ƿ���", 10, pos, &unuse);
		FillConsoleOutputAttribute(handle, RED, 10, pos, &unuse);
	}*/
	if(key != UP_KEY && key != DOWN_KEY && key != LEFT_KEY && key != RIGHT_KEY && (key>127 || key<=0))
	{
		PrintString(L"δ�趨", x, y, RED);
		return;
	}
	switch (key)
	{
		case ENTER_KEY:
			PrintString(L"�س���", x, y, color);
			break;
		case ' ':
			PrintString(L"�ո��", x, y, color);
			break;
		case 9:
			PrintString(L"Tab��", x, y, color);
			break;
		case UP_KEY:
			PrintString(L"��", x, y, color);
			break;
		case DOWN_KEY:
			PrintString(L"��", x, y, color);
			break;
		case LEFT_KEY:
			PrintString(L"��", x, y, color);
			break;
		case RIGHT_KEY:
			PrintString(L"��", x, y, color);
			break;
		default:
			buf[0] = static_cast<char>(key);
			buf[1] = '\0';
			PrintString(buf, x, y, color);
	}
}