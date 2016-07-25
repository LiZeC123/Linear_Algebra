#include "matrix.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>


#include <conio.h>
#define MAX_PSW_SIZE 20

using std::string; using std::istringstream;
using std::vector;
using std::map; using std::set;
using std::cin; using std::cout; using std::endl; using std::cerr;

using  Arg = std::vector<std::string>;

string Welcome();
std::istream & Append(std::istream & in, Arg args);
std::istream &_Append(std::istream & in, Matrix & Mc);
void PrintPrompt();
void NewMatrix(Arg args);
void IOclean();
void ls(Arg args);
void Reduce(Arg args);
void Det(Arg args);
void Clear(Arg args);
string UserName = "~";
string ComputerName = "TK-S300";

vector<Matrix> UserValueSpace;
map<string, int> UserNameSpace;
set<string> KeyWord = {"ls","reduce","det" ,"Matrix" ,"append","cls","reset" };


int main()
{
	UserName = Welcome();
	PrintPrompt();

	string cmdline;
	while (std::getline(cin, cmdline)) {
		istringstream cmdin(cmdline);
		string cmd;
		cmdin >> cmd;
		if (KeyWord.find(cmd) == KeyWord.end()) {
			if (cmd != "") {
				cout << "��Ч�Ĺؼ���" << endl;
			}
			else {
				PrintPrompt();
				continue;
			}
		}
		else {
			vector<string> args;
			string temp;
			while (cmdin >> temp) {
				args.push_back(temp);
			}
			if (cmd == "Matrix") {
				NewMatrix(args);
			}
			else if (cmd == "append") {
				Append(cin, args);
			}
			else if (cmd == "ls") {
				ls(args);
			}
			else if (cmd == "reduce") {
				Reduce(args);
			}
			else if (cmd == "det") {
				Det(args);
			}
			else if (cmd == "cls") {
				Clear(args);
			}
		}
		IOclean();
		PrintPrompt();
	}
}

string Welcome()
{
	string id;
	char cpassword[MAX_PSW_SIZE];

	cout << "LAR Super Compile System 1.0.01" << endl;
	cout << "Username��";
	std::getline(std::cin, id);
	cout << "Password��";
	char ch;
	int i = 0;
	while ((ch = _getch()) != '\r')
	{
		if (ch != 8)//���ǻس���¼��
		{
			cpassword[i] = ch;
			++i;
		}
		else
		{
			--i;
		}
	}
	cpassword[i] = '\0';
	cout << std::endl;
	string password = cpassword;
	return id;
}

std::istream & Append(std::istream & in, Arg args)
{
	for (const auto & name : args) {
		if (UserNameSpace.find(name) == UserNameSpace.end()) {
			cerr << name << "�����ڻ��޷�����" << endl;
		}
		else {
			_Append(in, UserValueSpace[UserNameSpace[name]]);
		}
	}
	return in;
}


std::istream & _Append(std::istream & in ,Matrix & Mc)
{
	cout << "�����������׷����ľ�������EOF����:" << endl;
	string s;
	while (std::getline(in, s)) {
		istringstream sin(s);
		int temp;
		while (sin >> temp) {
			Mc.GetOne(temp);
		}
		Mc.ReFlash();
	}
	if (!Mc.IsRegular()) {
		cout << "������벻��һ������ľ���" << endl;

	}

	if (!in) {
		in.clear();
	}

	Mc.ShowMatrix();

	return in;
}

void PrintPrompt()
{
	cout << UserName << "@" << ComputerName << "~:";
}

void NewMatrix(Arg args)
{
	for (auto & i : args) {
		if (KeyWord.find(i) != KeyWord.end()) {
			cerr << i << "�ǹؼ��֣�������Ϊ��ʶ��" << endl;
			return;
		}
	}
	for(auto &i : args){
		Matrix NewM;
		UserValueSpace.push_back(NewM);
		UserNameSpace[i] = UserValueSpace.size() - 1;
	}
}

void IOclean()
{
	if (!cin.good()) {
		cin.clear();
	}
}

void ls(Arg args)
{
	for (const auto & name : args) {
		if (UserNameSpace.find(name) == UserNameSpace.end()) {
			cerr << name << "�����ڻ��޷�����" << endl;
		}
		else {
			UserValueSpace[UserNameSpace[name]].ShowMatrix();
			cout << endl;
		}
	}
}

void Reduce(Arg args)
{
	for (const auto & name : args) {
		if (UserValueSpace[UserNameSpace[name]].IsEmpty()) {
			cerr << name << "Ϊ�գ��Ըþ���Ļ�����ֹͣ" << endl;
		}
		else {
			UserValueSpace[UserNameSpace[name]].RowReduce();
		}
	}
}

void Det(Arg args)
{
	for (const auto & name : args) {
		if (UserValueSpace[UserNameSpace[name]].IsEmpty()) {
			cerr << name << "Ϊ�գ��Ը�����ʽ�ļ�����ֹͣ" << endl;
		}
		else {
			UserValueSpace[UserNameSpace[name]].det().ShowFraction();
		}
	}
}

void Clear(Arg args)
{
	for (const auto & name : args) {
		if (UserNameSpace.find(name) == UserNameSpace.end()) {
			cerr << name << "�����ڻ��޷�����" << endl;
		}
		else {
			UserValueSpace[UserNameSpace[name]].Clear();
		}
	}
}



