#include <conio.h>			//����_kbhit()��_getch()����
#include <windows.h>		//����GetLocalTime()��Sleep()����
#include"UI.h"
#include"Block.h"

int main()
{
	CursorVisible(false);
	CUI ui;
	int key{ 0 }, key2{ 0 };
	SYSTEMTIME temp_time, current_time;
	GetLocalTime(&temp_time);
	ui.ShowInfo();
	ui.DrawBoard();
	while (true)
	{
		if (ui.BlockLandTest(PLAYER1))		//��ǰ����1���ʱ�Ĵ���
		{
			ui.DrawCurrentBlock(PLAYER1);
			ui.ClearLine();
			ui.SetNextBlock(PLAYER1);
			ui.ShowInfo();
			if (ui.GameOver(PLAYER1))			//��Ϸ����ʱ�Ĵ���
			{
				if (ui.ShowGameOver())		//��ʾ��Ϸ����ʱ�Ľ��棬�����������true�����¿�ʼ��Ϸ
				{
					system("cls");
					ui = CUI();			//���¿�ʼ��Ϸ
					ui.ShowInfo();
					ui.DrawBoard();
				}
				else return 0;		//�˳�����
			}
			GetLocalTime(&temp_time);
		}
		if (ui.BlockLandTest(PLAYER2) && ui.DoublePlayer())		//��ǰ����2���ʱ�Ĵ���
		{
			ui.DrawCurrentBlock(PLAYER2);
			ui.ClearLine();
			ui.SetNextBlock(PLAYER2);
			ui.ShowInfo();
			if (ui.GameOver(PLAYER2))			//��Ϸ����ʱ�Ĵ���
			{
				if (ui.ShowGameOver())		//��ʾ��Ϸ����ʱ�Ľ��棬�����������true�����¿�ʼ��Ϸ
				{
					system("cls");
					ui = CUI();			//���¿�ʼ��Ϸ
					ui.ShowInfo();
					ui.DrawBoard();
				}
				else return 0;		//�˳�����
			}
			GetLocalTime(&temp_time);
		}
		ui.DrawCurrentBlock(PLAYER1);
		if (ui.DoublePlayer()) ui.DrawCurrentBlock(PLAYER2);
		while (true)
		{
			GetLocalTime(&current_time);
			if (current_time - temp_time >= ui.GetIntervalTime())		//�����õĵ�ǰʱ���֮ǰ��ʱ��֮������趨��ֵ��ִ��һ������
			{
				temp_time = current_time;
				key = ui.GetDownKey(PLAYER1);
				if (ui.DoublePlayer()) key2 = ui.GetDownKey(PLAYER2);
				break;
			}
			if (_kbhit())		//����а���������
			{
				key= GetKey();
				key2 = 0;
				if (key == QUIT_KEY)
				{
					if (ui.GetAutoSave())
					{
						ui.ClearCurrentBlock(PLAYER1, false);
						ui.ClearCurrentBlock(PLAYER2, false);
						ui.SaveData();		//�Զ�����
					}
					return 0;		//�˳�
				}
				if (key == 'O')
				{
					ui.OptionSettings();
					ui.ShowInfo();
					ui.DrawBoard();
				}
				if (key == 'H')
				{
					ui.ShowHelpInfo();
					ui.ShowInfo();
					ui.DrawBoard();
				}
				if (ui.KeyIsControlKey(key))		//ֻ�а���ָ������Ϸ���Ƽ�����ż���
					break;
			}
			Sleep(20);			//��ʱ�Խ���CPU������
		}
		if (key != PAUSE_KEY)
		{
			ui.ClearCurrentBlock(PLAYER1, true);		//���ƶ�����ת֮ǰ����Ҫ�������ǰ����
			ui.ClearCurrentBlock(PLAYER2, true);
		}
		ui.KeyDetect(key);
		ui.KeyDetect(key2);
	}
}