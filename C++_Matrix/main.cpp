#include "Matrix.h"
#include "Handler.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <conio.h>
#define MAX_PSW_SIZE 50


using std::string; using std::istringstream;
using std::vector;
using std::map; using std::set;
using std::cin; using std::cout; using std::endl; using std::cerr;


extern map<string, Handler*> handlers;


void Initilize();
string Welcome();
void PrintPrompt();


int main()
{
	Initilize();
	UserName = Welcome();
	PrintPrompt();
	

	string cmdline;
	while (std::getline(cin, cmdline)) {
		istringstream cmdin(cmdline);
		string cmd;
		cmdin >> cmd;
		if (cmd == "") {
			PrintPrompt();
			continue;
		}


		vector<string> args;
		string temp;
		while (cmdin >> temp) {
			args.push_back(temp);
		}

		if (handlers.find(cmd) != handlers.end()) {
			handlers[cmd]->doCmd(args);
		}
	PrintPrompt();
	}
}

string Welcome()
{
	string id;
	char cpassword[MAX_PSW_SIZE];

	cout << "LAR Super Compile System 1.0.01" << endl;
	cout << "Username：";
	std::getline(std::cin, id);
	cout << "Password：";
	char ch;
	int i = 0;
	while ((ch = _getch()) != '\r')
	{
		if (ch != 8)//不是回撤就录入
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

void PrintPrompt()
{
	std::cout << UserName << "@" << ComputerName << "~:";
}

void Initilize()
{
	handlers["Matrix"] = new HandlerNew;
	handlers["append"] = new HandlerAppend;
	handlers["ls"] = new HandlerLook;
	handlers["reduce"] = new HandlerReduce;
	handlers["det"] = new HandlerDet;
	handlers["cls"] = new HandlerClean;
	handlers["+"] = new HandlerAdd;
	handlers["-"] = new HandlerSub;
	handlers["*"] = new HandlerMult;
}



