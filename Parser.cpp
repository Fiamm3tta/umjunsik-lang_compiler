#include <iostream>
#include <string>
#include "Node.h"

using std::wstring;
using std::cout;

static auto parseLine(vector<wstring> line) -> CodeLine*;
static auto parseStatement() -> vector<Statement*>;
static auto parseSetVariable() -> Statement*;
static auto parseJump() -> Statement*;
static auto parsePrint() -> Statement*;
static auto parseEnter() -> Expression*;
static auto parseIf() -> Statement*;
static auto parseReturn() -> Statement*;
static auto parseExpressionStatement() -> Statement*;
static auto parseExpression() -> Expression*;
static auto parseGetVariable() -> Expression*;
static auto parseNumber() -> Expression*;

static vector<wstring>::iterator current;
int count = 0;

auto parse(vector<vector<wstring>> tokens) -> Program*
{
	auto result = new Program();
	for (vector<wstring> line : tokens)
	{
		result->lines.push_back(parseLine(line));
	}

	return result;
}

static auto parseLine(vector<wstring> line) -> CodeLine*
{
	auto result = new CodeLine();
	current = line.begin();
	
	if (*current == L"StartList" || *current == L"\0")
	{
		result->isEmpty = true;
		return result;
	}

	if (*current == L"어떻게")
	{
		auto tmp = new CodeStart();
		result->nodes.push_back(tmp);
		return result;
	}

	if (*current == L"이 어떻게 사람이름이냐ㅋㅋ")
	{
		auto tmp = new CodeEnd();
		result->nodes.push_back(tmp);
		return result;
	}
	
	result->nodes = parseStatement();

	return result;
}

static auto parseStatement() -> vector<Statement*>
{
	vector<Statement*> result;
	while (*current != L"\0")
	{
		if (*current->rbegin() == L'엄')
		{
			result.push_back(parseSetVariable());
		}
		else if (*current == L"준")
		{
			result.push_back(parseJump());
		}
		else if (*current == L"식")
		{
			current += 1;
			result.push_back(parsePrint());
		}
		else if (*current == L"동탄")
		{
			result.push_back(parseIf());
		}
		else if (*current == L"화이팅!")
		{
			result.push_back(parseReturn());
		}
		else
		{
			std::wcout << *current << "\n";
			result.push_back(parseExpressionStatement());
		}
	}

	return result;
}

static auto parseSetVariable() -> Statement*
{
	auto result = new SetVariable();
	wstring tmp = *current;
	result->index = tmp.size();
	current += 1;
	result->expression = parseExpression();

	return result;
}

static auto parseJump() -> Statement*
{
	auto result = new Jump();
	current += 1;
	result->expression = parseExpression();

	return result;
}

static auto parsePrint() -> Statement*
{
	auto result = new Print();
	if (*current == L"ㅋ")
	{
		auto LF = new Number();
		LF->value = 10;
		result->argument = LF;
		result->isint = false;
		current += 1;
		return result;
	}
	else
	{
		result->argument = parseExpression();
	}

	if (*current == L"ㅋ")
	{
		result->isint = false;
	}
	current += 1;
	
	return result;
}

static auto parseEnter() -> Expression*
{
	auto result = new Enter();
	current += 1;

	return result;
}

static auto parseIf() -> Statement*
{
	auto result = new If();
	current += 1;
	result->condition = parseExpression();
	current += 1;
	result->todo = parseStatement();

	return result;
}

static auto parseReturn() -> Statement*
{
	auto result = new Return();
	current += 1;
	result->expression = parseExpression();
	return result;
}

static auto parseExpressionStatement() -> Statement*
{
	auto result = new ExpressionStatement();
	result->expression = parseExpression();
	return result;
}

static auto parseExpression() -> Expression*
{
	Expression* tmp = nullptr;

	if (*current == L"\0")
	{
		auto temp = new Number();
		temp->value = 0;
		return temp;
	}

	if (*current == L"식")
	{
		tmp = parseEnter();
	}

	if (*current->rbegin() == L'어')
	{
		tmp = parseGetVariable();
	}
	else if (*current->begin() == L'.' || *current->begin() == L',')
	{
		tmp = parseNumber();
	}

	current += 1;

	if (*current == L"\0" || *current == L"?" || *current == L"ㅋ" || *current == L"!")
	{
		return tmp;
	}

	auto result = new Arithmetic();

	if (*current == L" ")
	{
		result->isplus = false;
		current += 1;
	}

	result->lhs = tmp; 
	result->rhs = parseExpression();

	return result;
}

static auto parseGetVariable() -> Expression*
{
	auto result = new GetVariable();
	wstring tmp = *current;
	result->index = tmp.size();

	return result;
}

static auto parseNumber() -> Expression*
{
	wstring num = *current;
	auto result = new Number();
	for (wchar_t p : num)
	{
		if (p == L'.')
		{
			result->value += 1;
		}
		else
		{
			result->value -= 1;
		}
	}

	return result;
}