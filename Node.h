#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

struct Statement
{
	virtual auto print(int) -> void = 0;
	virtual auto generate() -> void = 0;
};
struct Expression
{
	virtual auto print(int) -> void = 0;
	virtual auto generate() -> void = 0;
};

struct CodeLine
{
	bool isEmpty = false;
	vector<Statement*> nodes;
	auto print(int) -> void;
	auto generate() -> void;
};

struct Program
{
	vector<CodeLine*> lines;
};

struct SetVariable : Statement
{
	int index;
	Expression* expression;
	auto print(int) -> void;
	auto generate() -> void;
};

struct GetVariable : Expression
{
	int index;
	auto print(int) -> void;
	auto generate() -> void;
};

struct If : Statement
{
	Expression* condition;
	vector<Statement*> todo;
	auto print(int) -> void;
	auto generate() -> void;
};

struct Jump : Statement
{
	Expression* expression;
	auto print(int) -> void;
	auto generate() -> void;
};

struct Print : Statement
{
	bool isint = true;
	Expression* argument;
	auto print(int) -> void;
	auto generate() -> void;
};

struct Enter : Expression
{
	auto print(int) -> void;
	auto generate() -> void;
};

struct Return : Statement
{
	Expression* expression;
	auto print(int) -> void;
	auto generate() -> void;
};

struct ExpressionStatement : Statement
{
	Expression* expression;
	auto print(int) -> void;
	auto generate() -> void;
};

struct CodeStart : Statement
{
	auto print(int) -> void;
	auto generate() -> void;
};

struct CodeEnd : Statement
{
	auto print(int) -> void;
	auto generate() -> void;
};

struct Arithmetic : Expression
{
	bool isplus = true;
	Expression* lhs;
	Expression* rhs;
	auto print(int) -> void;
	auto generate() -> void;
};

struct Number : Expression
{
	int value = 0;
	auto print(int) -> void;
	auto generate() -> void;
};