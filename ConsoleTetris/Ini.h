#pragma once
#include <windows.h>

//��ȡҪ�����ini�ļ���·��
/* void GetIniPath(char* path)
{
	GetModuleFileName(NULL, path, 256);	//��õ�ǰexe�ļ��ľ���·��
	char temp[12] {"\\config.ini"};
	int idx{255};
	while (path[idx] != '\\')		//����·�����һ����б�ܵ�λ��
		idx--;
	for(int i{ idx }, j{ 0 }; j<12; i++, j++)		//�����һ����б�ܴ�����"\\config.ini"
		path[i] = temp[j];
}
 */
//��ini�ļ�д��һ��int����
inline void WriteIntToIni(char* AppName, char* KeyName, int value)
{
	char buff[11];
	_itoa_s(value, buff, 10);
	WritePrivateProfileStringA(AppName,KeyName,buff, "./config.ini");
}

//��ini�ļ���ȡһ��int����
inline int GetIntFromIni(char* AppName, char* KeyName, int Default)
{
	return GetPrivateProfileIntA(AppName, KeyName, Default, "./config.ini");
}