#include <map>
#include "Code.h"

using std::map;

static map<string, Instruction> stringToInstruction =
{
	{"Start",		Instruction::Start},
	{"End",			Instruction::End},

	{"Return",		Instruction::Return},

	{"PrintNumber",	Instruction::PrintNumber},
	{"PrintChar",	Instruction::PrintChar},
	{"Enter",		Instruction::Enter},

	{"Jump",		Instruction::Jump},
	{"IsZero",		Instruction::IsZero},

	{"Add",			Instruction::Add},
	{"Multiply",	Instruction::Multiply},

	{"GetVariable",	Instruction::GetVariable},
	{"SetVariable", Instruction::SetVariable},

	{"PushNumber",	Instruction::PushNumber},
	{"PopOperand",	Instruction::PopOperand},
};

static const auto instructionToString = []
{
	map<Instruction, string> result;
	for (auto& [key, value] : stringToInstruction)
	{
		result[value] = key;
	}

	return result;
}();

auto toString(Instruction instruction) -> string
{
	if (instructionToString.count(instruction))
	{
		return instructionToString.at(instruction);
	}
	return "";
}