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
				cout << "无效的关键字" << endl;
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
	cout << "现在输入你的矩阵，输入EOF结束:" << endl;
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
		cout << "你的输入不是一个规则的矩阵" << endl;
	}
	Mc.ShowMatrix();
}

void NewMatrix(Arg args)
{
	if (args.size() != 1) {
		cout << "参数数量不匹配" << endl;
		return;
	}
	else if (KeyWord.find(args[0]) != KeyWord.end()) {
		cout << "名称不能是关键字" << endl;
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
		cout << "参数数量不匹配" << endl;
		return;
	}

	if (UseNameSpace.find(args[0]) == UseNameSpace.end()) {
		cout << "指定对象不存在" << endl;
		return;
	}

	GlobalObjectName = args[0];




		
}
