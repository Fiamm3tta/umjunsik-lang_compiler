#include <iostream>
#include "Node.h"

using std::cout;
static auto indent(int) -> void;

auto printSyntaxTree(Program* syntaxtree) -> void
{
	for (int i = 0; i < syntaxtree->lines.size(); i++)
	{
		cout << i << " ";
		syntaxtree->lines[i]->print(0);
	}
}

auto CodeLine::print(int depth) -> void
{
	cout << "CODELINE:" << "\n";
	for (auto& node : nodes)
	{
		node->print(depth + 2);
	}
}

auto SetVariable::print(int depth) -> void
{
	indent(depth);
	cout << "SET VAR " << index << ":" << "\n";
	expression->print(depth + 1);
}

auto GetVariable::print(int depth) -> void
{
	indent(depth);
	cout << "GET VAR" << index << "\n";
}

auto If::print(int depth) -> void
{
	indent(depth);
	cout << "CONDITION:" << "\n";
	condition->print(depth + 1);
	indent(depth);
	cout << "TODO: " << "\n";
	for (auto& node : todo)
	{
		node->print(depth + 1);
	}
}

auto Jump::print(int depth) -> void
{
	indent(depth);
	cout << "JUMPTO:" << "\n";
	expression->print(depth + 1);
}

auto Print::print(int depth) -> void
{
	indent(depth);
	cout << "PRINT ";
	if (isint)
	{
		cout << " NUMBER:" << "\n";
	}
	else
	{
		cout << "STRING:" << "\n";
	}

	argument->print(depth + 1);
}

auto Return::print(int depth) -> void
{
	indent(depth);
	cout << "RETURN: " << "\n";
	expression->print(depth + 1);
}

auto Arithmetic::print(int depth) -> void
{
	indent(depth);
	if (isplus)
	{
		cout << "PLUS:" << "\n";
	}
	else
	{
		cout << "MULTIPLY:" << "\n";
	}

	lhs->print(depth + 1);
	rhs->print(depth + 1);
}

auto ExpressionStatement::print(int depth) -> void
{
	indent(depth);
	expression->print(depth);
}

auto Number::print(int depth) -> void
{
	indent(depth);
	cout << value << "\n";
}

auto CodeStart::print(int depth) -> void
{
	indent(depth);
	cout << "CODESTART!" << "\n";
}

auto CodeEnd::print(int depth) -> void
{
	indent(depth);
	cout << "CODEEND!" << "\n";
}

auto Enter::print(int depth) -> void
{
	indent(depth);
	cout << "ENTER ANY INTEGAR NUMBER" << "\n";
}

auto indent(int depth) -> void
{
	cout << string(static_cast<size_t>(depth + 2), ' ');
}