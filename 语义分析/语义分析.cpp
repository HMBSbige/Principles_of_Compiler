#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;
int flag = 1, j = 0, k = 0, sum, no = 1, _j, mark, s = 0;
stack <string> temp;
stack <int> chain;
int w;
string T = "T1";
int t = 1;
const string ReservedWord[13] = { "program", "var", "procedure", "begin", "end", "if", "then", "else", "while", "do", "call", "integer", "real" };
char token[10];
string str;
char ch, ch1;
int x = 1;
struct re
{
	string op, arg1, arg2, result;
}num[100000];
string IDentifier[50];
struct wtf
{
	int tc;
	int fc;
}ck;


template<class T = int>
string ToString(const T& t)//鏁板瓧杞瓧绗︿覆
{
	ostringstream oss;
	oss << t;
	return oss.str();
}

template<class T = int>
T StringToNum(const string& s)//瀛楃涓茶浆鏁板瓧
{
	if (s == "")
		return 0;
	T num;
	stringstream ss(s);
	ss >> num;
	return num;
}
void addT()
{
	++t;
	string q = ToString(t);
	string p("T");
	T = p + q;
}
void LexicalAnalysis()//璇嶆硶
{
	for (int i = 0; i < 10; i++)
		token[i] = '\0';
	ch = str[j++];
	while (ch == ' ' || ch == '\t' || ch == '\n')
	{
		ch = str[j];
		j++;
	}
	_j = j - 1;
	int i;
	if (ch >= 'A'&&ch <= 'Z' || ch >= 'a'&&ch <= 'z')
	{
		i = 0;
		while (ch >= 'A'&&ch <= 'Z' || ch >= 'a'&&ch <= 'z' || ch >= '0'&&ch <= '9')
		{
			token[i++] = ch;
			//j++;
			ch = str[j++];
		}
		//j--;
		token[i] = '\0';
		if (i > 8)
		{
			flag = -1;
			return;
		}
		flag = 1;
		j--;
		for (i = 0; i < 13; i++)
		{
			if (ReservedWord[i] == token)
			{
				flag = i + 3;
				return;
			}
		}
		for (int m = 1; m < 50; m++)
		{
			string temp(token);
			if (IDentifier[m].length() == 0)
			{
				IDentifier[m] = temp;
				k = m;
				break;
			}
			if (IDentifier[m].compare(temp) == 0)
			{
				k = m;
				break;
			}
		}
	}
	else if (ch >= '0'&&ch <= '9')
	{
		i = 0;
		while (ch >= '0'&&ch <= '9' || ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
		{
			token[i++] = ch;
			//j++;
			ch = str[j++];
			//j++;
			if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
				flag = -1;
		}
		token[i] = '\0';
		if (flag == -1)
		{
			j--;
			return;
		}
		flag = 2;
		j--;
		for (i = 0, sum = 0; token[i] != '\0'; i++)
		{
			sum = sum * 10 + (token[i] - '0');
		}
	}
	else
	{
		switch (ch)
		{
		case '/':
		{
			ch = str[j++];
			if (ch == '/')
			{
				flag = -2;
				while (str[j] != '\n'&&str[j] != EOF)
				{
					j++;
				}
			}
			else if (ch == '*')
			{
				flag = -2;
				x = 0;
				while ((str[j] != '*' || str[j + 1] != '/') && str[j] != EOF)
					j++;
				//ch=str[j];
				if (str[j] == EOF)
				{
					j--;
					flag = 19;
					token[0] = '/';
				}
			}
			else
			{
				j--;
				flag = 19;
				token[0] = '/';
			}
			break;

		}
		case '<':
		{
			ch = str[j++];
			if (ch == '=')
			{
				flag = 24;
				token[0] = '<';
				token[1] = '=';

			}
			else if (ch == '>')
			{
				flag = 28;
				token[0] = '<';
				token[1] = '>';

			}
			else
			{
				j--;
				flag = 23;
				token[0] = '<';

			}
			break;
		}
		case '>':
		{
			ch = str[j++];
			if (ch == '=')
			{
				flag = 26;
				token[0] = '>';
				token[1] = '=';

			}
			else
			{
				j--;
				flag = 25;
				token[0] = '>';

			}
			break;
		}
		case '&':
		{
			ch = str[j++];
			if (ch == '&')
			{
				flag = 21;
				token[0] = '&';
				token[1] = '&';

			}
			else
				flag = -1;
			break;
		}
		case '|':
		{
			ch = str[j++];
			if (ch == '|')
			{
				flag = 22;
				token[0] = '|';
				token[1] = '|';

			}
			else
				flag = -1;
			break;
		}
		case '+':
		{
			flag = 16;
			token[0] = '+';

			break;
		}
		case '-':
		{
			flag = 17;
			token[0] = '-';

			break;
		}
		case '*':
		{
			ch = str[j++];
			if (ch == '/')
			{
				if (x == 0)
				{
					flag = -2;
					j++;
					x = 1;
				}
				else
				{
					j--;
					flag = 18;
					token[0] = '*';

				}
			}
			else
			{
				j--;
				flag = 18;
				token[0] = '*';
			}
			break;
		}
		case '!':
		{
			flag = 20;
			token[0] = '!';

			break;
		}
		case '=':
		{
			flag = 27;
			token[0] = '=';

			break;
		}
		case ':':
		{
			ch = str[j++];
			if (ch == '=')
			{
				flag = 29;
				token[0] = ':';
				token[1] = '=';

			}
			else
			{
				j--;
				flag = 35;
				token[0] = ':';
			}
			break;
		}
		case ';':
		{
			flag = 30;
			token[0] = ';';

			break;
		}
		case '.':
		{
			flag = 31;
			token[0] = '.';

			break;
		}
		case ',':
		{
			flag = 32;
			token[0] = ',';

			break;
		}
		case '(':
		{
			flag = 33;
			token[0] = '(';

			break;
		}
		case ')':
		{
			flag = 34;
			token[0] = ')';

			break;
		}
		case EOF:
		{
			flag = 0;
			token[0] = ch;
			break;
		}
		default:
		{
			flag = -1;
			token[0] = ch;
			break;
		}
		}

	}

}
int Phrase();
void Item();
void program()
{
	LexicalAnalysis();//program
	LexicalAnalysis();//abc
	LexicalAnalysis();//;
}

void Table()//鍙橀噺琛?
{
	LexicalAnalysis();
	LexicalAnalysis();//,
	if (flag == 32)
		Table();
	else
		j = _j;
}
void Type()//绫诲瀷
{
	LexicalAnalysis();//integer
}
void Vartable()//鍙橀噺澹版槑琛?
{
	Table();
	LexicalAnalysis();//:
	Type();
	LexicalAnalysis();//;
	if (flag == 30)
	{
		LexicalAnalysis();
		if (flag == 1)
		{
			Vartable();
		}
		else
			j = _j;

	}
}
void Var()//鍙橀噺澹版槑
{
	LexicalAnalysis();//var
	Vartable();
}
int CompoundStatement()//澶嶅悎
{
	LexicalAnalysis();
	if (flag != 6)
	{
		j = _j;
		return 0;
	}
	mark = 1;
	int x = Phrase();
	while (LexicalAnalysis(), flag == 30)
	{

		if (x == 2)
		{
			if (chain.top() != 0)
			{
				num[chain.top()].result = ToString(no);
				chain.pop();
			}
		}
		ck.tc = ck.fc = 0;
		x = Phrase();
	}
	j = _j;
	LexicalAnalysis();//end
	return 1;
}
void Expression()  //琛ㄨ揪寮?
{
	Item();

	LexicalAnalysis();
	while (flag == 16 || flag == 17)//+/-
	{
		temp.push(token);
		Item();
		num[no].arg2 = temp.top();
		temp.pop();
		num[no].op = temp.top();
		temp.pop();
		num[no].arg1 = temp.top();
		temp.pop();
		num[no++].result = T;
		temp.push(T);
		addT();
		LexicalAnalysis();
	}
	j = _j;//;
}
bool Bracket()//鎷彿
{
	LexicalAnalysis();
	if (flag != 33)//(
	{
		j = _j;
		return false;
	}
	Expression();
	LexicalAnalysis();
	return true;
}
void Factor()//鍥犲瓙
{
	LexicalAnalysis();
	if (flag == 1 || flag == 2)
		temp.push(token);
	if (flag != 1 && flag != 2)
	{
		j = _j;
		if (!Bracket())
			return;
	}
}
void Item()//椤?
{
	Factor();

	LexicalAnalysis();
	while (flag == 18 || flag == 19)//*,/
	{
		temp.push(token);
		Factor();
		num[no].arg2 = temp.top();
		temp.pop();
		num[no].op = temp.top();
		temp.pop();
		num[no].arg1 = temp.top();
		temp.pop();
		num[no++].result = T;
		temp.push(T);
		addT();
		LexicalAnalysis();
	}
	j = _j;//;

}
bool Relation()//鍏崇郴
{
	LexicalAnalysis();
	if (flag >= 23 && flag <= 28)
		temp.push(token);
	else
	{
		j = _j;
		temp.push(" ");
		return false;
	}
	return true;

}
void RelationExpression()//鍏崇郴琛ㄨ揪寮?
{
	Expression();
	if (Relation())
		Expression();
	else
		temp.push(" ");
}
void BoolExpression()  //甯冨皵琛ㄨ揪寮?
{
	LexicalAnalysis();
	if (flag == 20)//!
	{
		BoolExpression();
		swap(ck.tc, ck.fc);
	}
	else if (flag == 33)//(
	{
		if (mark == 22)
		{
			w = ck.fc;
			BoolExpression();
			LexicalAnalysis();
			num[ck.fc].result = ToString(w);
		}
		else if (mark == 21)
		{
			w = ck.tc;
			BoolExpression();
		}
	}
	else
	{
		j = _j;

		RelationExpression();

		if (mark == 1)
		{
			num[no].arg2 = temp.top();
			temp.pop();
			num[no].op = temp.top();
			temp.pop();
			num[no].arg1 = temp.top();
			temp.pop();
			num[no].result = ToString(ck.tc);
			ck.tc = no++;

			num[no].arg2 = " ";
			num[no].op = "j";
			num[no].arg1 = " ";
			num[no].result = ToString(ck.fc);

			ck.fc = no++;
			if (s == 1)
				chain.push(ck.fc);
		}
		else if (mark == 21)//&&
		{

			num[no].arg2 = temp.top();
			temp.pop();
			num[no].op = temp.top();
			temp.pop();
			num[no].arg1 = temp.top();

			temp.pop();
			string tem = num[ck.tc].result;

			num[ck.tc].result = ToString(no);
			num[no].result = tem;

			ck.tc = no++;


			num[no].arg2 = " ";
			num[no].op = "j";
			num[no].arg1 = " ";
			num[no].result = ToString(ck.fc);

			if (s == 1)
				chain.push(ck.fc);
			ck.fc = no;


			no++;

		}
		else if (mark == 22)//||
		{
			//鍥炲～鍓嶉潰鐨?&

			num[no].arg2 = temp.top();
			temp.pop();
			num[no].op = temp.top();
			temp.pop();
			num[no].arg1 = temp.top();
			temp.pop();
			string tem = num[ck.fc].result;
			num[ck.fc].result = ToString(no);
			num[no].result = tem;
			num[no].result = ToString(ck.tc);
			ck.tc = no++;

			num[no].arg2 = " ";
			num[no].op = "j";
			num[no].arg1 = " ";
			ck.fc = no++;
		}

		LexicalAnalysis();

		if (flag == 22)//||
		{
			mark = 22;
			BoolExpression();
		}
		else if (flag == 21)//&&
		{
			mark = 21;
			BoolExpression();
		}
		else j = _j;
	}
}
int Assignment()//璧嬪€?
{
	LexicalAnalysis();
	if (flag != 1)
	{
		j = _j;
		return 0;
	}
	temp.push(token);
	LexicalAnalysis();
	temp.push(token);

	Expression();
	num[no].arg2 = " ";
	num[no].arg1 = temp.top();
	temp.pop();
	num[no].op = temp.top();
	temp.pop();
	num[no++].result = temp.top();
	temp.pop();
	return 1;

}
int ConditionalStatement()//鏉′欢璇彞
{
	LexicalAnalysis();//if
	if (flag != 8)
	{
		j = _j;
		return 0;
	}
	s = 0;
	BoolExpression();
	while (ck.tc != 0)
	{
		int tem = StringToNum(num[ck.tc].result);
		num[ck.tc].result = ToString(no);
		ck.tc = tem;
	}
	while (ck.fc != 0)
	{
		chain.push(ck.fc);
		ck.fc = StringToNum(num[ck.fc].result);//褰掗浂
											   // cout<<ck.fc<<endl;
	}
	LexicalAnalysis();//then
	mark = 22;
	Phrase();
	LexicalAnalysis();//else
	if (flag == 10)
	{
		num[chain.top()].result = ToString(no + 1);
		chain.pop();

		num[no].arg2 = " ";
		num[no].op = "j";
		num[no].arg1 = " ";
		chain.push(no);
		no++;

		while (ck.fc != 0)//else if
		{
			int tem = StringToNum(num[ck.fc].result);
			num[ck.fc].result = ToString(no);
			ck.fc = tem;
		}
		Phrase();
	}
	else
		j = _j;

	return 1;
}
int CircularStatement()//寰幆璇彞
{
	LexicalAnalysis();//while
	if (flag != 11)
	{
		j = _j;//while
		return 0;
	}
	s = 1;
	int op = no;//18
	BoolExpression();
	while (ck.fc != 0)
	{
		chain.push(ck.fc);
		ck.fc = StringToNum(num[ck.fc].result);
	}
	int nc = chain.size();
	while (ck.tc != 0)
	{
		int tem = StringToNum(num[ck.tc].result);
		num[ck.tc].result = ToString(no);
		ck.tc = tem;
	}

	LexicalAnalysis();//do
	Phrase();

	nc = chain.size() - nc;
	while (nc--)
	{
		num[chain.top()].result = ToString(op);
		chain.pop();
	}

	num[no].arg1 = " ";
	num[no].op = "j";
	num[no].arg2 = " ";
	num[no++].result = ToString(op);

	return 1;
}
int Phrase()//璇彞
{
	mark = 1;
	if (CompoundStatement())
		return 1;
	if (Assignment())
		return 1;
	if (ConditionalStatement())
		return 2;
	if (CircularStatement())
		return 2;
	return 0;
}
void StatementBlock()//璇彞涓?
{
	Phrase();
	while (LexicalAnalysis(), flag == 30)
	{
		if (chain.top() != 0)//鍥炲～
		{
			num[chain.top()].result = ToString(no);
			chain.pop();
		}
		ck.tc = 0;
		Phrase();
	}
	j = _j;  //;
}
void programbody()
{
	Var();
	LexicalAnalysis();//begin
	StatementBlock();

	while (chain.top() != 0)
	{
		num[chain.top()].result = ToString(no);
		chain.pop();
	}
	num[no].arg2 = " ";
	num[no].op = "ret";
	num[no].arg1 = " ";
	num[no++].result = "0";

	LexicalAnalysis();//end
	LexicalAnalysis();//.
}
int main()
{
	ifstream fp(R"(C:\Users\Bruce Wayne\Desktop\in.txt)");
	ostringstream ss;
	ss << fp.rdbuf();
	str = ss.str();
	ofstream result(R"(C:\Users\Bruce Wayne\Desktop\result.txt)", std::ios::trunc);

	j = 0;
	chain.push(0);
	program();
	programbody();

	for (int i = 1; i < no; ++i)
		if (num[i].op == ">" || num[i].op == "<" || num[i].op == "<>")
			result << i << ". (j" << num[i].op << ", " << num[i].arg1 << ", " << num[i].arg2 << ", " << num[i].result << ")" << endl;
		else if (num[i].op == " ")
			result << i << ". (jz," << num[i].arg1 << ", " << num[i].arg2 << ", " << num[i].result << ")" << endl;
		else
			result << i << ". (" << num[i].op << ", " << num[i].arg1 << ", " << num[i].arg2 << ", " << num[i].result << ")" << endl;

	result.close();
	return 0;
}