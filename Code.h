#pragma once
#include <any>
#include <string>

using std::any;
using std::string;

enum class Instruction
{
	Start, End,
	Return,
	PrintNumber, PrintChar, Enter,
	Jump, IsZero,
	Add, Multiply,
	GetVariable, SetVariable,
	PushNumber, PopOperand,
};

struct Code
{
	Instruction instruction;
	any operand;
};

auto toString(Instruction) -> string;