#include <iostream>
#include<string>
#include<cmath>

using namespace std;
//��Ҫʹ����Ȳ��ԣ���Ҫ�ĵ�һЩ�޹ؽ�Ҫ�ĵط�
//��Ϊ��ȡ��ѭ�����룬һֱ��������뷽ʽ��������һЩ������֮��ĺ��ֵ����
class Num
{
	string str1, str2;
	//��װ
public:
	Num() {};
	Num(string m_str1, char m_ch, string m_str2); //��������
	inline int Compare(string str1, string str2); //�Ƚϣ���ȷ���0�����ڷ���1��С�ڷ���-1
	string Subtraction(string str1, string str2);   //����
	string Addition(string str1, string str2);   //�ӷ�
	string Multiplication(string str1, string str2);   //�˷� 
	string Divide(string str1, string str2, int flag); //ʵ�ֳ�����ȡ��
	string Division(string str1, string str2); //����
	string Modular(string str1, string str2);  //ȡ��

	Num(Num& e);  //��������
	~Num()//��������
	{
		cout << "�����������ʽ" << endl;
		cout << "���ټ���ʱctrl+z����" << endl;
	}
};

Num::Num(string m_str1, char m_ch, string m_str2)//�������ݣ����ƽ�����������
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

inline int Num::Compare(string str1, string str2) //��ȷ���0�����ڷ���1��С�ڷ���-1
{
	if (str1.size() > str2.size())
		return 1;
	else if (str1.size() < str2.size())
		return -1;
	else return str1.compare(str2);     //��������ȣ����ͷ��β��λ�Ƚ�
}

string Num::Addition(string str1, string str2)      
{
	int sign = 1;//signΪ����λ�������ô˱���ȷ���Ƿ������-��
	string str;
	if (str1[0] == '-')
	{
		if (str2[0] == '-')       //����
		{
			sign = -1;//�����մ�����Ӹ��ţ����Խ��˱�����Ϊ-1
			str = Addition(str1.erase(0, 1), str2.erase(0, 1));//��erase()ɾ������
		}
		else             //ǰ����������Ϊ����
		{
			str = Subtraction(str2, str1.erase(0, 1));
		}
	}
	else
	{
		if (str2[0] == '-')        //ǰ���󸺣���Ϊ����
		{
			str = Subtraction(str1, str2.erase(0, 1));
		}
		else                    //��������������ǰ���0���루������ӣ�
		{
			string::size_type len_1, len_2;  //�������ѧ����д�����Դ˺��������Ǻ��˽�
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
			int m_1 = 0, m_2 = 0; //m_2��¼��λ
			for (i = str1.size() - 1; i >= 0; i--)//�ӽ�β��ʼ��
			{
				m_1 = (int(str1[i]) - '0' + int(str2[i]) - '0' + m_2) % 10;//ͨ��+-��0����ʵ���ַ�����ֵ��ת��
				m_2 = (int(str1[i]) - '0' + int(str2[i]) - '0' + m_2) / 10;
				str = char(m_1 + '0') + str;
			}
			if (m_2 != 0)
			{
				str = char(m_2 + '0') + str;//����н�λ��ֱ�Ӵ浽ǰһλ����ʱǰһλʲôҲû�У�
			}
		}
	}
	//������������
	if ((sign == -1) && (str[0] != '0'))str = "-" + str;//�ж��Ƿ���Ҫ�������
	return str;
}

string Num::Subtraction(string str1, string str2)  
{
	int symbol = 1; //signΪ����λ
	string str;
	int i, j;
	if (str2[0] == '-')
	{
		str = Addition(str1, str2.erase(0, 1));//תΪ�ӷ�
	}
	else
	{
		int m = Compare(str1, str2);//����Compare����
		if (m == 0)return "0";//��ȫ��ͬ
		if (m < 0)//str2�󣬽��Ϊ��������λ��-1
		{
			symbol = -1;
			string temp = str1;
			str1 = str2;
			str2 = temp;//��������������λ��
		}
		string::size_type templen;//ͬ��һ��ͬ�����÷�
		templen = str1.size() - str2.size();//����λ���Ĳ�
		for (i = str2.size() - 1; i >= 0; i--)//��ĩβ��ʼ
		{
			if (str1[i + templen] < str2[i])          //��λ
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
	//��eraseȥ������ж����0������ǰ��ģ�
	str.erase(0, str.find_first_not_of('0'));
	if (str.empty())str = "0";
	if ((symbol == -1) && (str[0] != '0'))str = "-" + str;
	return str;
}

string Num::Multiplication(string str1, string str2)  
{
	int symbol = 1;
	string str = "0";        //��¼��ǰֵ
	if (str1[0] == '-')
	{
		symbol *= -1;
		str1 = str1.erase(0, 1);
	}
	if (str2[0] == '-')
	{
		symbol *= -1;//�������� *= ��������Եõ�����������Ч��
		str2 = str2.erase(0, 1);
	}
	int i, j;
	string::size_type len_1, len_2;
	len_1 = str1.size();
	len_2 = str2.size();
	for (i = len_2 - 1; i >= 0; i--)        //�˷���ʽһ������ĩλ��ʼ
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
				tempstr = char(m_1 + '0') + tempstr;//ͬ��ͨ������0����ʵ���������ַ���ת��
			}
			if (m_2 != 0)tempstr = char(m_2 + '0') + tempstr;
		}
		str = Addition(str, tempstr);
	}
	//��erase����ȥ������ж����0
	str.erase(0, str.find_first_not_of("0"));
	if (str.empty())str = "0";//�ж�λ0�����
	if ((symbol == -1) && (str[0] != '0'))
	{
		str = "-" + str;//���Ӹ��ţ�����б�Ҫ��
	}
	return str;
}

//��������һ��flag��ʹ����ͬʱ��ɡ�/���͡�%��������
string Num::Divide(string str1, string str2, int flag) //flag==1,������;flag==0ʱ����������
{
	string quotient, remainder;  //�����̺�����
	int symbol_1 = 1, symbol_2 = 1;
	if (str2 == "0")   //������Ϊ0�������error��
	{
		quotient = "ERROR!";
		remainder = "ERROR!";
		if (flag == 1)   
			return quotient;
		else
			return remainder;
	}
	if (str1 == "0")     //��������Ϊ0���̺���������0
	{
		quotient = "0";
		remainder = "0";
	}
	if (str1[0] == '-')
	{
		str1 = str1.erase(0, 1);
		symbol_1 *= -1;//ͬ������ͳ˷�������������
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
		remainder = str1;//�������ȳ���С������λΪ0������Ϊ������
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
		tempstr.append(str1, 0, len_2 - 1); //��str1��Ϊֵ0��len_2-1���ַ���׷�ӵ�tempstr
		for (int i = len_2 - 1; i < len_1; i++)  //ģ���ֹ�������ʽ
		{
			tempstr = tempstr + str1[i];
			tempstr.erase(0, tempstr.find_first_not_of('0')); //���ַ����в��ҵ�һ����'0'��ƥ����ַ�����������λ��
			if (tempstr.empty())tempstr = "0";  //q.empty()�������п�ʱ������true
			for (char ch = '9'; ch >= '0'; ch--) //����
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

	//����erase����ȥ��ǰ��û�õ�0
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

//���������������ͬʱ�ó����̺���������ͬʱ����ԭ���ġ��������͡��������Ĺ���

string Num::Division(string str1, string str2) //������
{
	return Divide(str1, str2, 1);
}

string Num::Modular(string str1, string str2)  //��������
{
	return Divide(str1, str2, 0);
}

int main()
{
	cout << "��ӭʹ��" << endl << endl;
	cout << "������ʽʱ������ֵ����ż���ӿո�" << endl << endl;

	char ch;//������ķ��� 
	string data1, data2;
	while (cin >> data1 >> ch >> data2)
	{
		Num num(data1 , ch, data2);
	}
	return 0;
}