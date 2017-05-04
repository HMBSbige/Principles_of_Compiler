#include <fstream> 
#include <sstream> 
#include <iostream> 
#include <string>
#include <vector>
using namespace std;
struct eryuan
{
	size_t a, b;
	string s;
	eryuan(size_t _a, size_t _b, string _s) : a(_a), b(_b), s(_s) {}
	friend bool operator ==(const eryuan&a, const eryuan& b)
	{
		return a.a == b.a && a.b == b.b && a.s == b.s;
	}
	friend bool operator !=(const eryuan&a, const eryuan& b)
	{
		return !(a == b);
	}
};
vector<eryuan> data1;
bool isStatementBlock();
bool isExpression();
bool isPhrase();

bool isTable()//变量表
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (it->a != 1)
		return false;
	data1.erase(it);
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it == eryuan(32, 0, ","))
	{
		data1.erase(it);
		return isTable();
	}
	return true;
}

bool isType()//类型
{
	//?(14,0)integer
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(14, 0, "integer"))
		return false;
	data1.erase(it);
	return true;
}

bool isVartable()//变量声明表
{
	if (!isTable())//变量表
		return false;
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(35, 0, ":"))
		return false;
	data1.erase(it);
	if (!isType())//类型
		return false;
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(30, 0, ";"))
		return false;
	data1.erase(it);
	//?(4,0)var isVartable();
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(6, 0, "begin"))//(6,0)begin
		return isVartable();
	return true;
}

bool isVar()//变量声明
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(4, 0, "var"))
		return false;
	data1.erase(it);
	return isVartable();//变量声明表
}

bool isCom()//复合语句
{
	//?(6,0)begin
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	data1.erase(it);
	if(!isStatementBlock())//语句串
		return false;
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(7, 0, "end"))
		return false;
	data1.erase(it);
	return true;
}

bool isfact()//因子
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (it->a == 1 || it->a == 2)
	{
		data1.erase(it);
		return true;
	}
	if (*it == eryuan(33, 0, "(")) // (33, 0)(
	{
		data1.erase(it);
		if (!isExpression())
			return false;
		it = data1.begin();
		if (it == data1.end())
			return false;
		if (*it != eryuan(34, 0, ")"))//(34,0)){
		{
			return false;
		}
			data1.erase(it);
			return true;
	}
	return isExpression();
}

bool isItem()//项
{
	if(!isfact())
		return false;
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it == eryuan(18, 0, "*"))//(18,0)*
	{
		data1.erase(it);
		return isItem();
	}
	return true;
}
bool isExpression()//表达式
{

	if (!isItem())
		return false;
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it == eryuan(16, 0, "+"))//(16, 0)+
	{
		data1.erase(it);
		return isExpression();
	}
	return true;
}

bool isAssignment()//赋值
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	data1.erase(it);
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(29, 0, ":="))//?(29,0):=
		return false;
	data1.erase(it);
	return isExpression();
}

bool isRE()
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(23, 0, "<") || *it != eryuan(24, 0, "<=") || *it != eryuan(25, 0, ">") ||
		*it != eryuan(26, 0, ">=") || *it != eryuan(27, 0, "=") || *it != eryuan(28, 0, "<>") )
	{
		data1.erase(it);
		return true;
	}
	return false;
}

bool isRelation()
{
	if (!isExpression())
		return false;
	if (!isRE())
		return false;
	if (!isExpression())
		return false;
	return true;
}

bool isboolExre()//布尔表达式
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it == eryuan(20, 0, "!"))//?(20, 0)!
	{
		data1.erase(it);
		return isRelation();
	}
	if(!isRelation())
		return false;
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it == eryuan(21, 0, "&&") || *it == eryuan(22, 0, "||"))//?(21,0)&& (22,0)||
	{
		data1.erase(it);
		return isboolExre();
	}
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it == eryuan(9, 0, "then") || *it == eryuan(12, 0, "do"))
		return true;
	return false;
}

bool isCon()//条件
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	data1.erase(it);
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (!isboolExre())
		return false;
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(9, 0, "then"))//?(9,0)then
		return false;
	data1.erase(it);
	if (!isPhrase())
		return false;
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it == eryuan(10, 0,"else")) // (10, 0)else
	{
		data1.erase(it);
		return  isPhrase();
	}
	return true;
}

bool isCycle()//循环
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	data1.erase(it);
	if (!isboolExre())
		return false;
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(12, 0, "do"))//?(12,0)do
		return false;
	data1.erase(it);
	return isPhrase();
}

bool isPhrase()//语句
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it == eryuan(6, 0, "begin"))//(6,0)begin
		return isCom();
	if (it->a == 1)
		return isAssignment();
	if (*it == eryuan(8, 0, "if"))
		return isCon();
	if(*it == eryuan(11, 0, "while"))
		return isCycle();
	return false;
}

bool isStatementBlock()//语句串
{
	if(!isPhrase())//语句
		return false;
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if(*it == eryuan(30, 0, ";"))
	{
		data1.erase(it);
		return isStatementBlock();
	}
	return true;
}

bool isProgram()
{
	if (!isVar())//?变量声明
		return false;
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(6, 0, "begin"))//(6,0)begin
		return false;
	data1.erase(it);
	if (!isStatementBlock())//语句串
		return false;

	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(7, 0, "end"))
		return false;
	data1.erase(it);
	
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(31, 0, ".") && it!= data1.end())//(31, 0).
		return false;
	data1.erase(it);
	return true;
}

bool isPro()
{
	auto it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(3, 0, "program"))
		return false;
	data1.erase(it);
	it = data1.begin();
	if (it == data1.end())
		return false;
	if(it->a!=1)
		return false;
	data1.erase(it);
	it = data1.begin();
	if (it == data1.end())
		return false;
	if (*it != eryuan(30, 0, ";"))
		return false;
	data1.erase(it);
	return isProgram();
}

template<class T>
T StringToNum(const string& s)//字符串转数字
{
	T num;
	stringstream ss(s);
	ss >> num;
	return num;
}

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
	std::ifstream fs(R"(C:\Users\Bruce Wayne\Desktop\out.txt)");
	string strTemp;
	while(getline(fs,strTemp,'\n'))
	{
		int i;
		string str = "";
		for (i = 1; strTemp[i] != ','; ++i)
			str += strTemp[i];
		auto a = StringToNum<size_t>(str);
		++i;
		str = "";
		for (; strTemp[i] != ')'; ++i)
			str += strTemp[i];
		auto b = StringToNum<size_t>(str);
		++i;
		str = strTemp.substr(i);
		data1.push_back(eryuan(a, b, str));
	}
	if (isPro())
		cout << "True" << endl;
	else
		cout << "False" << endl;
	system("pause");
	return 0;
}
