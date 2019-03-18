//************************************************************
//���ļ������궨�塢ȫ�ֳ�����ö�����ͺ�ȫ�ֺ����Ķ���
//************************************************************
#pragma once
#include<Windows.h>

//���幦�ܼ�
#define UP_KEY (-1)			//�����Ϸ����
#define DOWN_KEY (-2)		//�����·����
#define LEFT_KEY (-3)		//���������
#define RIGHT_KEY (-4)		//�����ҷ����
//�����ַ���
#define PAUSE_KEY 13			//������ͣ��
#define QUIT_KEY 27		//�����˳�������esc���˳���
#define SPACE_KEY ' '		//����ո��
#define CHEAT_KEY '4'		//�������׼�
#define LEVELUP_KEY '5'		//���塰һ����������
#define ENTER_KEY 13		//����س���
#define PLAYER1_STRIP1_KEY '1'	//���1ʹ�õ���1��
#define PLAYER1_STRIP2_KEY '2'	//���1ʹ�õ���2��
#define PLAYER1_STRIP3_KEY '3'	//���1ʹ�õ���3��
#define PLAYER2_STRIP1_KEY '8'	//���2ʹ�õ���1��
#define PLAYER2_STRIP2_KEY '9'	//���2ʹ�õ���2��
#define PLAYER2_STRIP3_KEY '0'	//���2ʹ�õ���3��

#define FULL_CELL true		//��������ϵĸ�������״̬
#define EMPTY_CELL false		//��������ϵĸ��ӿյ�״̬

#define PLAYER1 true		//���1
#define PLAYER2 false		//���2

using CellType = bool;		//�����ϵĸ��ӵ�״̬
using Player = bool;		//���ѡ��

const int WIDTH{ 20 };		//����Ŀ�ȣ�����ȣ�
const int HEIGHT{ 23 };		//����ĸ߶�
const int BOARD_X{ 8 };	//���ƽ������ʼx���꣨������Ϊ���20ʱ�Ļ��ƽ�����ʼx���꣩
const int BOARD_Y{ 1 };	//���ƽ������ʼy����

enum BlockType		//���������
{
	B_I,
	B_L,
	B_J,
	B_Z,
	B_S,
	B_T,
	B_O,
	B_BOMB,		//ը��
	B_PIERCE		//���׵�
};

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

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

//enum Method
//{
//	MOVE_LEFT,
//	MOVE_RIGHT,
//	ROTATE
//};

struct Cell
{
	CellType type;
	Color color;
};

//struct BlockState
//{
//	int x_position;
//	Direction dirction;
//};

//����7+2�ַ���4�������ÿ�����ص���뷽�������λ��ƫ��
const int BlockPointOffset[9][4][4][2]
{
	//I�η���
	{
		//UP����
		{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
		//RIGHT����
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },
		//DOWN����
		{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
		//LEFT����
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } }
	},

	//L�η���
	{
		//UP����
		{	{ 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 }	},
		//RIGHT����
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 1 } },
		//DOWN����
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 } },
		//LEFT����
		{ { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } }
	},

	//J�η���
	{
		//UP����
		{ { 1, 0 }, { 1, 1 }, { 0, 2 }, { 1, 2 } },
		//RIGHT����
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } },
		//DOWN����
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 0, 2 } },
		//LEFT����
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 } }
	},

	//Z�η���
	{
		//UP����
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } },
			//RIGHT����
		{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } },
		//DOWN����
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } },
		//LEFT����
		{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } }
	},

	//S�η���
	{
		//UP����
		{ { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } },
		//RIGHT����
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } },
		//DOWN����
		{ { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } },
		//LEFT����
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } }
	},

	//T�η���
	{
		//UP����
		{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } },
		//RIGHT����
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } },
		//DOWN����
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 1, 1 } },
		//LEFT����
		{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } }
	},

	//O�η���
	{
		//UP����
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
		//RIGHT����
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
		//DOWN����
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
		//LEFT����
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } }
	},
	
	//ը��
	{
		//UP����
		{ { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 } },
		//RIGHT����
		{ { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 } },
		//DOWN����
		{ { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 } },
		//LEFT����
		{ { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 } }
	},
	
	//���׵�
	{ { { 0 } } }
};

//ΪSYSTEMTIME�ṹ���ؼ������������ȷ��a>b������·�������ʱ���ĺ����������Ƿ��ص�ֵ���ᳬ��3000����
int operator-(SYSTEMTIME a, SYSTEMTIME b)
{
	if (a.wSecond == b.wSecond)
		return a.wMilliseconds - b.wMilliseconds;
	else if (a.wSecond - b.wSecond == 1 || a.wSecond - b.wSecond == -59)
		return a.wMilliseconds - b.wMilliseconds + 1000;
	else
		return a.wMilliseconds - b.wMilliseconds + 2000;
}

//��ȡһ���������밴�������䷵��
int GetKey()
{
	int key{ _getch() };
	if (key == 0xE0 || key == 0)		//�����õİ���ֵΪ0x0E��0���ʾ�����˹��ܼ�
	{
		switch (_getch())		//�����˹��ܼ���Ҫ�ٴε���_getch����
		{
			case 72: key = UP_KEY; break;
			case 80: key = DOWN_KEY; break;
			case 75: key = LEFT_KEY; break;
			case 77: key = RIGHT_KEY; break;
			default: break;
		}
	}
	if (key>='a' && key<='z')		//���������Сд��ĸ�����Զ�ת���ɴ�д��ĸ
		key -= 32;
	return key;
}

//�����ڼ�λ�趨ʱ�ж��û����µļ��Ƿ�Ϊ�Ƿ�
inline bool IllegalControlKey(int key)
{
	//���û����µļ�Ϊ���еĿ��Ƽ����ASCII���ַ���ʱ���ж�Ϊ�����Ƿ�
	return (key == PAUSE_KEY || key == PLAYER1_STRIP1_KEY || key == PLAYER1_STRIP2_KEY || key == PLAYER1_STRIP3_KEY ||
		key == PLAYER2_STRIP1_KEY || key == PLAYER2_STRIP2_KEY || key == PLAYER2_STRIP3_KEY ||
		key == QUIT_KEY || key =='O' ||key > 127);
}