#include "matrix.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using std::string; using std::istringstream;
using std::vector;
using std::map; using std::set;
using std::cin; using std::cout; using std::endl;

using  Arg = vector<string>;

void Input(Matrix & Mc);
void NewMatrix(Arg args);
void IOclean();
void ChangeMatrix(Arg args);


string GlobalObjectName = "~";
vector<Matrix> UseValueSpace;
map<string, int> UseNameSpace;
set<string> KeyWord = { "cd","ls","reduce","det" ,"Matrix" ,"input"};


int main()
{
	string cmdline;
	cout << GlobalObjectName << ">";
	while (std::getline(cin, cmdline)) {
		istringstream cmdin(cmdline);
		string cmd;
		cmdin >> cmd;
		if (KeyWord.find(cmd) == KeyWord.end()) {
			if (cmd != "") {
				cout << "��Ч�Ĺؼ���" << endl;
			}
			else {
				cout << GlobalObjectName << ">";
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
			else if (cmd == "input") {		
				Input(UseValueSpace[UseNameSpace[GlobalObjectName]]);
			}
			else if (cmd == "ls") {
				UseValueSpace[UseNameSpace[GlobalObjectName]].ShowMatrix();
			}
			else if (cmd == "cd") {
				ChangeMatrix(args);
			}
			else if (cmd == "reduce") {
				UseValueSpace[UseNameSpace[GlobalObjectName]].RowReduce();
			}
			else if (cmd == "det") {
				UseValueSpace[UseNameSpace[GlobalObjectName]].det().ShowFraction();
			}
		}
		IOclean();
		cout << GlobalObjectName << ">";
	}
}


void Input(Matrix & Mc)
{
	cout << "����������ľ�������EOF����:" << endl;
	string s;
	while (std::getline(cin, s)) {
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
	Mc.ShowMatrix();
}

void NewMatrix(Arg args)
{
	if (args.size() != 1) {
		cout << "����������ƥ��" << endl;
		return;
	}
	else if (KeyWord.find(args[0]) != KeyWord.end()) {
		cout << "���Ʋ����ǹؼ���" << endl;
	}
	else {
		Matrix NewM;
		UseValueSpace.push_back(NewM);
		UseNameSpace[args[0]] = UseValueSpace.size() - 1;
		GlobalObjectName = args[0];
	}
}

void IOclean()
{
	if (!cin.good()) {
		cin.clear();
	}
}

void ChangeMatrix(Arg args)
{
	if (args.size() != 1) {
		cout << "����������ƥ��" << endl;
		return;
	}

	if (UseNameSpace.find(args[0]) == UseNameSpace.end()) {
		cout << "ָ�����󲻴���" << endl;
		return;
	}

	GlobalObjectName = args[0];




		
}
