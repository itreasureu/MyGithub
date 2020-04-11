#include <iostream>
#include<string>
#include<cmath>

using namespace std;
//若要使用洛谷测试，需要改掉一些无关紧要的地方
//因为采取了循环输入，一直计算的输入方式；而且有一些除数据之外的汉字的输出
class Num
{
	string str1, str2;
	//封装
public:
	Num() {};
	Num(string m_str1, char m_ch, string m_str2); //处理数据
	inline int Compare(string str1, string str2); //比较：相等返回0，大于返回1，小于返回-1
	string Subtraction(string str1, string str2);   //减法
	string Addition(string str1, string str2);   //加法
	string Multiplication(string str1, string str2);   //乘法 
	string Divide(string str1, string str2, int flag); //实现除法和取余
	string Division(string str1, string str2); //除法
	string Modular(string str1, string str2);  //取余

	Num(Num& e);  //拷贝构造
	~Num()//析构函数
	{
		cout << "请继续输入算式" << endl;
		cout << "不再计算时ctrl+z即可" << endl;
	}
};

Num::Num(string m_str1, char m_ch, string m_str2)//处理数据，控制进入哪种运算
{
	string m_mult;

	switch (m_ch)
	{
		case'+':
			m_mult = Addition(m_str1, m_str2); break;
		case'-':
			m_mult = Subtraction(m_str1, m_str2); break;
		case'*':
			m_mult = Multiplication(m_str1, m_str2); break;
		case'/':
			m_mult = Division(m_str1, m_str2); break;
		case'%':
			m_mult = Modular(m_str1, m_str2); break;
		default:
			break;
	}
	
	cout << endl;
	cout << m_mult << endl;
}

inline int Num::Compare(string str1, string str2) //相等返回0，大于返回1，小于返回-1
{
	if (str1.size() > str2.size())
		return 1;
	else if (str1.size() < str2.size())
		return -1;
	else return str1.compare(str2);     //若长度相等，则从头到尾按位比较
}

string Num::Addition(string str1, string str2)      
{
	int sign = 1;//sign为符号位，最终用此变量确定是否输出“-”
	string str;
	if (str1[0] == '-')
	{
		if (str2[0] == '-')       //均负
		{
			sign = -1;//在最终答案上添加负号，所以将此变量置为-1
			str = Addition(str1.erase(0, 1), str2.erase(0, 1));//用erase()删除负号
		}
		else             //前负后正，换为减法
		{
			str = Subtraction(str2, str1.erase(0, 1));
		}
	}
	else
	{
		if (str2[0] == '-')        //前正后负，换为减法
		{
			str = Subtraction(str1, str2.erase(0, 1));
		}
		else                    //均正，给短整数前面加0补齐（方便相加）
		{
			string::size_type len_1, len_2;  //这个是我学来的写法，对此函数还不是很了解
			int i;
			len_1 = str1.size();
			len_2 = str2.size();
			if (len_1 < len_2)
			{
				for (i = 0; i < len_2 - len_1; i++)
					str1 = "0" + str1;
			}
			else
			{
				for (i = 0; i < len_1 - len_2; i++)
					str2 = "0" + str2;
			}
			int m_1 = 0, m_2 = 0; //m_2记录进位
			for (i = str1.size() - 1; i >= 0; i--)//从结尾开始算
			{
				m_1 = (int(str1[i]) - '0' + int(str2[i]) - '0' + m_2) % 10;//通过+-‘0’来实现字符和数值的转换
				m_2 = (int(str1[i]) - '0' + int(str2[i]) - '0' + m_2) / 10;
				str = char(m_1 + '0') + str;
			}
			if (m_2 != 0)
			{
				str = char(m_2 + '0') + str;//如果有进位，直接存到前一位（此时前一位什么也没有）
			}
		}
	}
	//运算符处理符号
	if ((sign == -1) && (str[0] != '0'))str = "-" + str;//判断是否需要输出负号
	return str;
}

string Num::Subtraction(string str1, string str2)  
{
	int symbol = 1; //sign为符号位
	string str;
	int i, j;
	if (str2[0] == '-')
	{
		str = Addition(str1, str2.erase(0, 1));//转为加法
	}
	else
	{
		int m = Compare(str1, str2);//调用Compare函数
		if (m == 0)return "0";//完全相同
		if (m < 0)//str2大，结果为负，符号位置-1
		{
			symbol = -1;
			string temp = str1;
			str1 = str2;
			str2 = temp;//减数被减数互换位置
		}
		string::size_type templen;//同上一个同类型用法
		templen = str1.size() - str2.size();//记下位数的差
		for (i = str2.size() - 1; i >= 0; i--)//从末尾开始
		{
			if (str1[i + templen] < str2[i])          //借位
			{
				j = 1;
				while (1)
				{
					if (str1[templen - j + i] == '0')
					{
						str1[i + templen -j] = '9';
						j++;
					}
					else
					{
						str1[i + templen - j] = char(int(str1[i + templen - j]) - 1);
						break;
					}
				}
				str = char(str1[i + templen] - str2[i] + ':') + str;
			}
			else
			{
				str = char(str1[i + templen] - str2[i] + '0') + str;
			}
		}
		for (i = templen - 1; i >= 0; i--)
			str = str1[i] + str;
	}
	//用erase去出结果中多余的0（补在前面的）
	str.erase(0, str.find_first_not_of('0'));
	if (str.empty())str = "0";
	if ((symbol == -1) && (str[0] != '0'))str = "-" + str;
	return str;
}

string Num::Multiplication(string str1, string str2)  
{
	int symbol = 1;
	string str = "0";        //记录当前值
	if (str1[0] == '-')
	{
		symbol *= -1;
		str1 = str1.erase(0, 1);
	}
	if (str2[0] == '-')
	{
		symbol *= -1;//利用俩处 *= 运算符可以得到负负得正的效果
		str2 = str2.erase(0, 1);
	}
	int i, j;
	string::size_type len_1, len_2;
	len_1 = str1.size();
	len_2 = str2.size();
	for (i = len_2 - 1; i >= 0; i--)        //乘法竖式一样，从末位开始
	{
		string tempstr;
		int m_1 = 0, m_2 = 0, m_3 = int(str2[i]) - '0';
		if (m_3 != 0)
		{
			for (j = 1; j <= (int)(len_2 - 1 - i); j++)
				tempstr = "0" + tempstr;
			for (j = len_1 - 1; j >= 0; j--)
			{
				m_1 = (m_3 * (int(str1[j]) - '0') + m_2) % 10;
				m_2 = (m_3 * (int(str1[j]) - '0') + m_2) / 10;
				tempstr = char(m_1 + '0') + tempstr;//同样通过±‘0’来实现数字与字符的转换
			}
			if (m_2 != 0)tempstr = char(m_2 + '0') + tempstr;
		}
		str = Addition(str, tempstr);
	}
	//用erase函数去除结果中多余的0
	str.erase(0, str.find_first_not_of("0"));
	if (str.empty())str = "0";//判断位0的情况
	if ((symbol == -1) && (str[0] != '0'))
	{
		str = "-" + str;//增加负号（如果有必要）
	}
	return str;
}

//参数增加一个flag，使其能同时完成‘/’和‘%’的运算
string Num::Divide(string str1, string str2, int flag) //flag==1,返回商;flag==0时，返回余数
{
	string quotient, remainder;  //定义商和余数
	int symbol_1 = 1, symbol_2 = 1;
	if (str2 == "0")   //若除数为0，输出“error”
	{
		quotient = "ERROR!";
		remainder = "ERROR!";
		if (flag == 1)   
			return quotient;
		else
			return remainder;
	}
	if (str1 == "0")     //若被除数为0，商和余数都是0
	{
		quotient = "0";
		remainder = "0";
	}
	if (str1[0] == '-')
	{
		str1 = str1.erase(0, 1);
		symbol_1 *= -1;//同理减法和乘法“负负得正”
		symbol_2 = -1;
	}
	if (str2[0] == '-')
	{
		str2 = str2.erase(0, 1);
		symbol_1 *= -1;
	}
	int m = Compare(str1, str2);
	if (m < 0)
	{
		quotient = "0";
		remainder = str1;//被除数比除数小，则商位为0，余数为被除数
	}
	else if (m == 0)
	{
		quotient = "1";
		remainder = "0";
	}
	else
	{
		string::size_type len_1, len_2;
		len_1 = str1.size();
		len_2 = str2.size();
		string tempstr;
		tempstr.append(str1, 0, len_2 - 1); //将str1中为值0到len_2-1的字符串追加到tempstr
		for (int i = len_2 - 1; i < len_1; i++)  //模拟手工除法竖式
		{
			tempstr = tempstr + str1[i];
			tempstr.erase(0, tempstr.find_first_not_of('0')); //在字符串中查找第一个与'0'不匹配的字符，返回它的位置
			if (tempstr.empty())tempstr = "0";  //q.empty()，当队列空时，返回true
			for (char ch = '9'; ch >= '0'; ch--) //试商
			{
				string str;
				str = str + ch;
				if (Compare(Multiplication(str2, str), tempstr) <= 0)
				{
					quotient = quotient + ch;
					tempstr = Subtraction(tempstr, Multiplication(str2, str));
					break;
				}
			}
		}
		remainder = tempstr;
	}

	//利用erase函数去掉前面没用的0
	quotient.erase(0, quotient.find_first_not_of("0"));
	if (quotient.empty())quotient = "0";
	if ((symbol_1 == -1) && (quotient[0] != '0'))
	{
		quotient = "-" + quotient;
	}
	if ((symbol_2 == -1) && (remainder[0] != '0'))
	{
		remainder = "-" + remainder;
	}
	if (flag == 1)
		return quotient;
	else
		return remainder;
}

//上面这个除法函数同时得出了商和余数，可同时满足原来的“除法”和“余数”的功能

string Num::Division(string str1, string str2) //返回商
{
	return Divide(str1, str2, 1);
}

string Num::Modular(string str1, string str2)  //返回余数
{
	return Divide(str1, str2, 0);
}

int main()
{
	cout << "欢迎使用" << endl << endl;
	cout << "输入算式时请在数值与符号间添加空格" << endl << endl;

	char ch;//存运算的符号 
	string data1, data2;
	while (cin >> data1 >> ch >> data2)
	{
		Num num(data1 , ch, data2);
	}
	return 0;
}