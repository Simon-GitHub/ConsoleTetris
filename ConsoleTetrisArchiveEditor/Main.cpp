#include <conio.h>	
#include"Define.h"
#include"UI.h"

int main()
{
	system("mode con:cols=80 lines=25");
	CUI ui;
	int key;
	ui.LoadFromFile();	//����ʱ�Զ�����浵
	ui.ShowFixedInfo();
	while (true)
	{
		key = _getch();
		if (key == 0xE0 || key == 0)
		{
			switch (_getch())
			{
				case 72: key = UP_KEY; break;
				case 80: key = DOWN_KEY; break;
				case 75: key = LEFT_KEY; break;
				case 77: key = RIGHT_KEY; break;
				default: break;
			}
		}
		if (key == QUIT_KEY)
		{
			ui.SaveToFile();		//�˳�ʱ�Զ�����浵
			return 0;
		}
		ui.KeyDetect(key);
	}
}