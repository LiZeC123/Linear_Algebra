#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include "Matrix.h"


using  Arg = std::vector<std::string>;



class Handler
{
public:
	virtual void doCmd(Arg args);
};

class HandlerNew : public Handler
{
public:
	void doCmd(Arg args) override;
};

class HandlerLook : public Handler
{
public:
	void doCmd(Arg args) override;
};

class HandlerReduce : public Handler
{
public:
	void doCmd(Arg args) override;
};

class HandlerDet : public Handler
{
public:
	void doCmd(Arg args) override;
};

class HandlerClean : public Handler
{
public:
	void doCmd(Arg args) override;
};

class HandlerAppend : public Handler
{
public:
	void doCmd(Arg args) override;
	void _Append(std::istream & in, Matrix & Mc);
};

class HandlerPrompt : public Handler
{
public:
	void doCmd(Arg args) override;
};

class HandlerAdd : public Handler
{
public:
	void doCmd(Arg args) override;
};

class HandlerSub : public Handler
{
public:
	void doCmd(Arg args) override;
};

class HandlerMult : public Handler
{
public:
	void doCmd(Arg args) override;
};


extern std::string UserName;
extern std::string ComputerName;
extern std::map<std::string, Matrix> UserValueSpace;
extern std::map<std::string, Handler*> handlers;