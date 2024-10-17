#include <vector>
#include <tuple>
#include <string>
#include "Node.h"
#include "Code.h"

using std::vector;
using std::tuple;
using std::string;

static vector<Code> codeList;
static vector<size_t> lineIndex;

static auto writeCode(Instruction, any) -> size_t;
static auto writeCode(Instruction instruction) -> size_t;

auto generate(Program* program) -> tuple<vector<Code>, vector<size_t>>
{
	codeList.clear();
	lineIndex.clear();
	lineIndex.push_back(0);
	for (auto& line : program->lines)
	{
		line->generate();
	}

	return { codeList, lineIndex };
}

auto CodeLine::generate() -> void
{
	if (!isEmpty)
	{
		for (auto& node : nodes)
		{
			node->generate();
		}
	}
	lineIndex.push_back(codeList.size());
}
	
auto SetVariable::generate() -> void
{
	expression->generate();
	writeCode(Instruction::SetVariable, index);
	writeCode(Instruction::PopOperand);
}

auto GetVariable::generate() -> void
{
	writeCode(Instruction::GetVariable, index);
}

auto If::generate() -> void
{
	condition->generate();
	writeCode(Instruction::IsZero);
	auto jump = writeCode(Instruction::Jump);
	for (auto& node : todo)
	{
		node->generate();
	}
	codeList[jump].operand = codeList.size();
}

auto Jump::generate() -> void
{
	expression->generate();
	writeCode(Instruction::Jump);
}

auto Print::generate() -> void
{
	argument->generate();
	if (isint)
	{
		writeCode(Instruction::PrintNumber);
	}
	else
	{
		writeCode(Instruction::PrintChar);
	}
}

auto Enter::generate() -> void
{
	writeCode(Instruction::Enter);
}

auto Return::generate() -> void
{
	expression->generate();
	writeCode(Instruction::Return);
}

auto ExpressionStatement::generate() -> void
{
	expression->generate();
	writeCode(Instruction::PopOperand);
}

auto CodeStart::generate() -> void
{
	writeCode(Instruction::Start);
}

auto CodeEnd::generate() -> void
{
	writeCode(Instruction::End);
}

auto Arithmetic::generate() -> void
{
	lhs->generate();
	rhs->generate();

	if (isplus)
	{
		writeCode(Instruction::Add);
	}
	else
	{
		writeCode(Instruction::Multiply);
	}
}

auto Number::generate() -> void
{
	writeCode(Instruction::PushNumber, value);
}

static auto writeCode(Instruction instruction) -> size_t
{
	codeList.push_back({ instruction });
	return codeList.size() - 1;
}

static auto writeCode(Instruction instruction, any operand) -> size_t
{
	codeList.push_back({ instruction, operand });
	return codeList.size() - 1;
}