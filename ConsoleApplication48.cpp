#include<iostream>
#include<windows.h>
#include"TextEditor.h"
using namespace std;
void CheckPassword(string FileName,string password)
{
	while (true)
	{
		if (password=="Pakistan123")
		{
			break;
		}
		else
		{
			system("cls");
			cout << "Please enter valid password : ";
			cin >> password;
		}
	}
}
void OpenFile(string& FileName, string password)
{
	cout << "Please enter the name of file you want to open : ";
	cin >> FileName;
	cout << "Please enter the password of " << FileName << " : ";
	cin >> password;
	CheckPassword(FileName, password);
}
int main()
{
	string FileName,password;
	OpenFile(FileName, password);
	TextEditor TE(FileName);
	TE.Editing();
	return 0;
}