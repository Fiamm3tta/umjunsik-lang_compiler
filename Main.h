#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <iomanip>
#include <tuple>
#include "stdlib.h" 
#include "Node.h"
#include "Code.h"
#include "VirtualMachine.h"

using std::wfstream;
using std::cout;
using std::wcout;
using std::string;
using std::wstring;
using std::vector;
using std::locale;
using std::setw;
using std::left;
using std::right;
using std::tuple;
using std::get;

auto scan(wstring sourceCode) -> vector<vector<wstring>>;
auto parse(vector<vector<wstring>> tokens) -> Program*;
auto printSyntaxTree(Program* syntaxtree) -> void;
auto generate(Program* program) -> tuple<vector<Code>, vector<size_t>>;