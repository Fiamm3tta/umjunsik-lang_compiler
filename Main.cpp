#include "Main.h"

auto printTokenList(vector<vector<wstring>> tokens) -> void
{
	for (int i = 0; i < tokens.size(); i++)
	{
		cout << setw(5) << left << i;
		for (int j = 0; j < tokens[i].size(); j++)
		{
			wcout << tokens[i][j];
			if (j != tokens[i].size() - 1)
			{
				cout << " / ";
			}
		}
		cout << "\n";
	}
}

auto printObjectCode(tuple<vector<Code>, vector<size_t>> objectCode) -> void
{
	auto codeList = get<0>(objectCode);
	for (int i = 0; i < codeList.size(); i++)
	{
		cout << setw(3) << right << i << " ";
		cout << setw(15) << left << toString(codeList[i].instruction);
		if (codeList[i].operand.type() == typeid(int))
		{
			cout << std::any_cast<int>(codeList[i].operand);
		}
		if (codeList[i].operand.type() == typeid(size_t))
		{
			cout << std::any_cast<size_t>(codeList[i].operand);
		}
		cout << "\n";
	}

	auto lineIndex = get<1>(objectCode);
	for (int i = 0; i < lineIndex.size(); i++)
	{
		cout << setw(3) << right << i << " " << lineIndex[i] << "\n";
	}
}

int main()
{
	// 소스 파일 읽어들이기
	locale::global(locale(".UTF-8"));

	wfstream win(L"SourceCode.txt");
	wstring sourceCode;
	if (win.is_open())
	{
		win.seekg(0, std::ios::end);
		int size = win.tellg();
		sourceCode.resize(size);
		win.seekg(0, std::ios::beg);
		win.read(&sourceCode[0], size);
	}
	else
	{
		cout << "파일을 찾을 수 없습니다!" << "\n";
	}

	auto tokenList = scan(sourceCode);

	// printTokenList(tokenList);
	
	auto syntaxtree = parse(tokenList);

	// printSyntaxTree(syntaxtree);
	
	auto objectCode = generate(syntaxtree);

	// printObjectCode(objectCode);
	
	auto vm = VirtualMachine(objectCode);
	vm.execute();
	
	cout << "\n";
	system("PAUSE");

	return 0;
}