#include <boost/spirit.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>

template<class T>
T StringToNum(const std::string& s)//字符串转数字
{
	T num;
	std::stringstream ss(s);
	ss >> num;
	return num;
}

std::map<std::string, size_t > addr;
size_t n = 0;

struct my_grammar
	: public boost::spirit::grammar<my_grammar>
{
	struct print
	{
		void operator()(const char *begin, const char *end) const
		{
			std::string s(begin, end);
			if (s == "program")std::cout << "(3,0)";
			else if (s == "procedure")std::cout << "(5,0)";
			else if (s == "var")std::cout << "(4,0)";
			else if (s == "begin")std::cout << "(6,0)";
			else if (s == "end")std::cout << "(7,0)";
			else if (s == "if")std::cout << "(8,0)";
			else if (s == "then")std::cout << "(9,0)";
			else if (s == "else")std::cout << "(10,0)";
			else if (s == "while")std::cout << "(11,0)";
			else if (s == "do")std::cout << "(12,0)";
			else if (s == "call")std::cout << "(13,0)";
			else if (s == "integer")std::cout << "(14,0)";
			else if (s == "real")std::cout << "(15,0)";
			else if (s == "+") std::cout << "(16,0)";
			else if (s == "-") std::cout << "(17,0)";
			else if (s == "*") std::cout << "(18,0)";
			else if (s == "/") std::cout << "(19,0)";
			else if (s == "!") std::cout << "(20,0)";
			else if (s == "&&") std::cout << "(21,0)";
			else if (s == "||") std::cout << "(22,0)";
			else if (s == "<") std::cout << "(23,0)";
			else if (s == "<=") std::cout << "(24,0)";
			else if (s == ">") std::cout << "(25,0)";
			else if (s == ">=") std::cout << "(26,0)";
			else if (s == "=") std::cout << "(27,0)";
			else if (s == "<>") std::cout << "(28,0)";
			else if (s == ":=") std::cout << "(29,0)";
			else if (s == ";") std::cout << "(30,0)";
			else if (s == ".") std::cout << "(31,0)";
			else if (s == ",") std::cout << "(32,0)";
			else if (s == "(") std::cout << "(33,0)";
			else if (s == ")") std::cout << "(34,0)";
			else if (s == ":") std::cout << "(35,0)";
			else if (s[0] <= '9' && s[0] >= '0')std::cout << "(2," << StringToNum<size_t>(s) << ")";
			else if (s[0] >= 'a' && s[0] <= 'z') {
				if (s.size() > 8)
					std::cout << "error(1)";
				else {
					auto it = addr.find(s);
					if (it == addr.end()) {
						addr[s] = ++n;
						std::cout << "(1," << n << ")";
					}
					else {
						std::cout << "(1," << it->second << ")";
					}
				}
			}
			std::cout << s << std::endl;
		}
	};

	template <typename Scanner>
	struct definition
	{
		boost::spirit::rule<Scanner> 单词符号, 标识符, 正整数, 单分界符, 双分界符, 斜竖, 小于, 大于, 冒号, 字母, 数字, 保留字, wtf, any;

		explicit definition(const my_grammar &self)
		{
			using namespace boost::spirit;
			wtf = *any;
			any = 保留字 | 标识符 | 单词符号 | 正整数 | 双分界符 | 单分界符 | 斜竖 | 小于 | 大于 | 冒号 | 数字 | 字母;
			单词符号 = +字母;
			标识符 = (字母 >> *(数字 | 字母))[print()];
			正整数 = (+数字)[print()];
			单分界符 = (ch_p("+") | ch_p("-") | ch_p("*") | ch_p("/") | ch_p("(") | ch_p(")") | ch_p(";") | ch_p(":") | ch_p(".") | ch_p("!") | ch_p(",") | ch_p("=") | (斜竖 - str_p("/*")) | (小于 - str_p("<=")) | (大于 - str_p(">=")))[print()];
			双分界符 = ((冒号 >> ch_p("=")) | (小于 >> ch_p("=")) | (小于 >> ch_p(">")) | (大于 >> ch_p("=")) | str_p("&&") | str_p("||"))[print()];
			斜竖 = ch_p("/");
			小于 = ch_p("<");
			大于 = ch_p(">");
			冒号 = ch_p(":");
			数字 = digit_p;
			字母 = lower_p;
			保留字 = (str_p("program") | str_p("var") | str_p("procedure") | str_p("begin") | str_p("end") | str_p("if") | str_p("then") | str_p("else") | str_p("while") | str_p("do") | str_p("call") | str_p("real") | str_p("integer"))[print()];
		}

		const boost::spirit::rule<Scanner> &start()
		{
			return wtf;
		}
	};
};

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
	std::ifstream fs(R"(C:\Users\Bruce Wayne\Desktop\in.txt)");//argv[1]
	std::ofstream outfile;
	outfile.open(R"(C:\Users\Bruce Wayne\Desktop\out.txt)", std::ios::trunc);
	std::ostringstream ss;
	ss << fs.rdbuf();
	std::cout.rdbuf(outfile.rdbuf());
	std::string data = ss.str();

	for (size_t i = 0; i < data.size(); ++i) {
		if (data[i] == '/' && data[i - 1] == '/') {
			size_t f = i - 1;
			for (++i; !(data[i] == '\n'); ++i);
			data.erase(f, i - f);
		}
	}
	for (size_t i = 0; i < data.size(); ++i) {
		if (data[i] == '*' && data[i - 1] == '/') {
			size_t f = i - 1;
			for (++i; (!(data[i] == '/' && data[i - 1] == '*')) && (i < data.size()); ++i);
			if (i < data.size())
				data[i] = ' ';
			data.erase(f, i - f);
			i = f - 1;
		}
	}
	my_grammar g;
	boost::spirit::parse_info<> pi = boost::spirit::parse(data.c_str(), g);
	if (pi.hit)
	{
		std::string s = pi.stop;
		while (!pi.full) {
			if (s[0] != ' ' && s[0] != '\n' && s[0] != '\t') {
				std::cout << "error(1)" << s[0] << std::endl;
			}
			s.erase(s.begin());
			pi = boost::spirit::parse(s.c_str(), g);
			s = pi.stop;
		}
		//std::cout << "分析成功！" << std::endl;
	}
	else
		std::cout << "分析失败！ 剩余字符串：\"" << pi.stop << "\"" << std::endl;
	outfile.close();
	system("pause");
	return 0;
}