#include "VirtualMachine.h"

using std::tuple;
using std::get;
using std::any;
using std::vector;
using std::cout;
using std::cin;
using std::any_cast;

VirtualMachine::VirtualMachine(tuple<vector<Code>, vector<size_t>> objectCode)
{
	auto tmp1 = get<0>(objectCode);
	auto tmp2 = get<1>(objectCode);
	codeList = tmp1;
	lineIndex = tmp2;
	int variables[11] = { 0 };
	callStack.operandStack.clear();
}

auto VirtualMachine::execute() -> void
{
	while (true)
	{
		auto code = codeList[callStack.instructionPointer];
		switch (code.instruction)
		{
			case Instruction::Start:
			{
				break;
			}

			case Instruction::End:
			{
				callStack.operandStack.clear();
				return;
			}

			case Instruction::Return:
			{
				
				callStack.operandStack.clear();
				return;
			}

			case Instruction::PrintNumber:
			{
				auto value = any_cast<int>(popOperand());
				cout << value;
				break;
			}

			case Instruction::PrintChar:
			{
				auto value = any_cast<int>(popOperand());
				cout << static_cast<char>(value);
				break;
			}

			case Instruction::Enter:
			{
				int value = 0;
				cin >> value;
				pushOperand(value);
				break;
			}

			case Instruction::Jump:
			{
				if (code.operand.type() == typeid(size_t))
				{
					callStack.instructionPointer = any_cast<size_t>(code.operand);
				}
				else
				{
					auto index = any_cast<int>(popOperand());
					callStack.instructionPointer = lineIndex[index];
				}
				
				continue;
			}

			case Instruction::IsZero:
			{
				auto value = any_cast<int>(popOperand());
				if (value == 0)
				{
					callStack.instructionPointer += 1;
				}
				break;
			}

			case Instruction::Add:
			{
				int lhs = any_cast<int>(popOperand());
				int rhs = any_cast<int>(popOperand());
				pushOperand(lhs + rhs);
				break;
			}

			case Instruction::Multiply:
			{
				int lhs = any_cast<int>(popOperand());
				int rhs = any_cast<int>(popOperand());
				pushOperand(lhs * rhs);
				break;
			}

			case Instruction::GetVariable:
			{
				auto value = any_cast<int>(code.operand);
				pushOperand(callStack.variables[value]);
				break;
			}

			case Instruction::SetVariable:
			{
				int value = any_cast<int>(peekOperand());
				callStack.variables[any_cast<int>(code.operand)] = value;
				
				break;
			}

			case Instruction::PushNumber:
			{
				pushOperand(code.operand);
				break;
			}

			case Instruction::PopOperand:
			{
				popOperand();
				break;
			}
		}
		callStack.instructionPointer += 1;
	}
}

auto VirtualMachine::popOperand() -> any
{
	auto value = callStack.operandStack.back();
	callStack.operandStack.pop_back();
	return value;
}

auto VirtualMachine::pushOperand(any value) -> void
{
	callStack.operandStack.push_back(value);
}

auto VirtualMachine::peekOperand() -> any
{
	return callStack.operandStack.back();
}