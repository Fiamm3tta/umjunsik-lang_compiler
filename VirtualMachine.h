#pragma once
#include <any>
#include <vector>
#include <tuple>
#include <iostream>
#include "Code.h"

using std::tuple;
using std::vector;

struct StackFrame
{
	int variables[11];
	vector<any> operandStack;
	size_t instructionPointer = 0;
};

class VirtualMachine
{
public:
	VirtualMachine(tuple<vector<Code>, vector<size_t>> objectCode);

	auto execute() -> void;

private:
	vector<size_t> lineIndex;
	vector<Code> codeList;
	StackFrame callStack;

	auto popOperand() -> any;
	auto pushOperand(any value) -> void;
	auto peekOperand() -> any;
};