#include <string>
#include <vector>
#include <iostream>

using std::wstring;
using std::vector;

enum class CharType
{
	Unknown,
	Newline,
	UM,
	JUN,
	SIK,
	DONGTAN,
	FIGHTING,
	Num,
	Sign,
	E,
};

static auto getCharType(wchar_t wc) -> CharType;
static auto scanUm() -> wstring;
static auto scanJun() -> wstring;
static auto scanSik() -> wstring;
static auto scanDongTan() -> wstring;
static auto scanFighting() -> wstring;
static auto scanNum() -> wstring;
static auto scanE() -> wstring;
static auto scanSign() -> wstring;

static wstring::iterator current;

auto scan(wstring sourceCode) -> vector<vector<wstring>>
{
	vector<vector<wstring>> result;
	vector<wstring> line;
	sourceCode.push_back(L'\n');
	sourceCode.push_back(L'\0');
	current = sourceCode.begin();

	line.push_back(L"StartList");
	line.push_back(L"\0");
	result.push_back(line);
	line.clear();

	while (*current != L'\0')
	{
		switch (getCharType(*current))
		{
			case CharType::Newline:
			{
				line.push_back(L"\0");
				result.push_back(line);
				line.clear();
				current += 1;
				break;
			}
			case CharType::UM:
			{
				line.push_back(scanUm());
				break;
			}
			case CharType::JUN:
			{
				line.push_back(scanJun());
				break;
			}
			case CharType::SIK:
			{
				line.push_back(scanSik());
				break;
			}
			case CharType::DONGTAN:
			{
				line.push_back(scanDongTan());
				break;
			}
			case CharType::FIGHTING:
			{
				line.push_back(scanFighting());
				break;
			}
			case CharType::Num:
			{
				line.push_back(scanNum());
				break;
			}
			case CharType::E:
			{
				line.push_back(scanE());
				break;
			}
			case CharType::Sign:
			{
				line.push_back(scanSign());
				break;
			}
			default:
			{
				std::cout << static_cast<char>(*current) << "는 사용할 수 없는 문자입니다.";
				exit(1);
			}
		}
	}
	return result;
}

static auto scanUm() -> wstring
{
	wstring result;

	if (*current == L'엄')
	{
		current += 1;
		return L"엄";
	}
	
	while (*current == L'어')
	{
		result += *current;
		current += 1;
	}

	if (*current == L'떻')
	{
		current += 2;
		return L"어떻게";
	}

	if (*current == L'엄')
	{
		result += *current;
		current += 1;
		return result;
	}

	return result;
}

static auto scanJun() -> wstring
{
	current += 1;
	return L"준";
}

static auto scanSik() -> wstring
{
	current += 1;
	return L"식";
}

static auto scanDongTan() -> wstring
{
	current += 2;
	return L"동탄";
}

static auto scanFighting() -> wstring
{
	current += 4;
	return L"화이팅!";
}
static auto scanNum() -> wstring
{
	wstring result;
	while (1)
	{
		if(*current == L'.'|| *current == L',')
		{
			result += *current;
			current += 1;
		}
		else
		{
			break;
		}
	}

	return result;
}
static auto scanE() -> wstring
{
	while (*current != L'\n')
	{
		current += 1;
	}
	return L"이 어떻게 사람이름이냐ㅋㅋ";
}
static auto scanSign() -> wstring
{
	wstring result;
	result += *current;
	current += 1;

	return result;
}

static auto getCharType(wchar_t wc) -> CharType
{
	if (wc == L'\n' || wc == L'~')
	{
		return CharType::Newline;
	}

	if (wc == L'어' || wc == L'엄')
	{
		return CharType::UM;
	}

	if (wc == L'준')
	{
		return CharType::JUN;
	}

	if (wc == L'식')
	{
		return CharType::SIK;
	}

	if (wc == L'동')
	{
		return CharType::DONGTAN;
	}

	if (wc == L'화')
	{
		return CharType::FIGHTING;
	}

	if (wc == L'.' || wc == L',')
	{
		return CharType::Num;
	}
	
	if (wc == L' ' || wc == L'!' || wc == L'?' || wc == L'ㅋ')
	{
		return CharType::Sign;
	}
	
	if (wc == L'이')
	{
		return CharType::E;
	}

	return CharType::Unknown;
}