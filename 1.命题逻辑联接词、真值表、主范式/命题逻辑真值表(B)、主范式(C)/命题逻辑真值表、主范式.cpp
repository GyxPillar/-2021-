// 2053385 ������ //
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FOR(j,a,b) for(int j=a;j<b;j++)
#define FOR(k,a,b) for(int k=a;k<b;k++)

#include <iostream>
#include <iomanip>

using namespace std;

// ��������a��b�η�%c
int QuickPow(int a, int b, int c)
{
	int ret = 1;
	int num = a % c;
	while (b)
	{
		if (b & 1)               // bΪ����
			ret = ret * num % c;
		b = b >> 1;              // b/=2
		num = num * num % c;
	}
	return ret;
}

// ���������Ԫ
struct variable
{
	char name;  // �������� 
    bool value; // ����ֵ
};

// ��ֵ����
class TruthTable
{
public:
	// ���캯������������ı��ʽs����
	TruthTable(const string s = "");

	// �����������ͷ��ڴ棬�����ڴ涪ʧ
	~TruthTable() { delete[]variables, delete[]principalConjunctiveNormalForm, delete[]principalDisjunctiveNormalForm; }

	// �����ֵ��
	void PrintTruthTable();

	// �������ʽ
	void PrintPrincipalNormForms();

private:

	int* principalDisjunctiveNormalForm;// ����ȡ��ʽ
	int* principalConjunctiveNormalForm;// ����ȡ��ʽ
	int variableNumber = 0;             // ��������
	variable* variables;                // �洢���������ƺ����Ӧ��ֵ
	string expression;                  // ���ʽ

	// ��ʮ��������numת��Ϊ���������֣�ͬʱ�����������ְ�λ��ֵ��variable����
	void SetVariablesValue(int num = 0);

	// ���㵱ǰ״̬�±��ʽ��ֵ
	bool CalculateExpressionValue();

	// ���ȫ����������ʽ����
	void PrintVariablesName()const;

	// ���ȫ����������ʽ��ֵ
	void PrintVariablesValue();

	// �����ʽ�еı�����ת��Ϊ����
	string AlphaToNum();

};

// ���캯������������ı��ʽsΪ˽�г�Ա����ֵ
TruthTable::TruthTable(const string s)
{
	variable temp[33];                                 // ��ʱ�洢����
	int cnt = 0;                                       // ��������
	FOR(i, 0, s.length())
	{
	judge:if (isalpha(s[i]))                           // �����ʽ��ĳλΪ��ĸ���򽫸���ĸ�������
	{
		FOR(j, 0, cnt)
			if (s[i] == temp[j].name)                  // �ظ����ֵı�����������
			{
				i++;
				goto judge;
			}

		temp[cnt].name = s[i], temp[cnt].value = false;// �³��ֵı������������м�¼��ͬʱ��ʼֵ��0
		cnt++;
	}
	}
	printf("\n��ʽ���еı�������Ϊ:%d\n", cnt);        // �����������

	// ����TruthTable���˽�г�Ա
	variableNumber = cnt;
	expression = s;
	variables = new variable[cnt];
	principalConjunctiveNormalForm = new int[QuickPow(2, cnt, INT_MAX)];// ����ȡ��ʽ�������2��n�η���������
	principalDisjunctiveNormalForm = new int[QuickPow(2, cnt, INT_MAX)];// ����ȡ��ʽ�������2��n�η�����С��
	FOR(i, 0, cnt)
		variables[i] = temp[i];
}

// �����ֵ��
void TruthTable::PrintTruthTable()
{
	// ���������������Ϊ��ͷ
	PrintVariablesName();

	// ��ֵ��2��n�η��У���lines��������
	int n = variableNumber;
	int lines = QuickPow(2, n, INT_MAX);
	FOR(i, 0, lines)
	{
		SetVariablesValue(i);  // ��������i�Ķ���������Ϊ��ǰ��������ֵ
		PrintVariablesValue(); // �����������ֵ����ǰ��ֵ״̬�±��ʽ��ֵ
	}
}

// �������ʽ
void TruthTable::PrintPrincipalNormForms()
{
	// ���ݲ�ͬ��ֵ����С���뼫����ĺ���2��n�η���
	int n = variableNumber;
	int lines = QuickPow(2, n, INT_MAX);
	
	// �ֱ��¼����ȡ��ʽ�м��������Ŀ������ȡ��ʽ�м�С�����Ŀ
	int principalConjunctiveNormalFormNumber = 0, principalDisjunctiveNormalFormNumber = 0;

	// ��2��n�η���������б���
	FOR(i, 0, lines)
	{
		SetVariablesValue(i);                                                                                       // ��������i�Ķ���������Ϊ��ǰ��������ֵ
		if (CalculateExpressionValue()) principalDisjunctiveNormalForm[principalDisjunctiveNormalFormNumber++] = i; // ����ǰ��ֵʹ�ù�ʽ����ֵΪ1����Ϊ��С���������ȡ��ʽ
		else principalConjunctiveNormalForm[principalConjunctiveNormalFormNumber++] = i;                            // ����ǰ��ֵʹ�ù�ʽ����ֵΪ0����Ϊ�������������ȡ��ʽ
	}

	// �������ȡ��ʽ
	if (principalConjunctiveNormalFormNumber)
	{
		printf("\n�����⹫ʽ������ȡ��ʽ:\n\t");
		FOR(i, 0, principalConjunctiveNormalFormNumber - 1)
			cout << "M(" << principalConjunctiveNormalForm[i] << ")\\/";
		cout << "M(" << principalConjunctiveNormalForm[principalConjunctiveNormalFormNumber - 1] << ')' << endl;
	}
	else printf("\n�����⹫ʽ����������ȡ��ʽ.\n");

	// �������ȡ��ʽ
	if (principalDisjunctiveNormalFormNumber)
	{
		printf("\n�����⹫ʽ������ȡ��ʽ:\n\t");
		FOR(i, 0, principalDisjunctiveNormalFormNumber - 1)
			cout << "M(" << principalDisjunctiveNormalForm[i] << ")/\\";
		cout << "M(" << principalDisjunctiveNormalForm[principalDisjunctiveNormalFormNumber - 1] << ')' << endl;
	}
	else printf("\n�����⹫ʽ����������ȡ��ʽ.\n");
}

// ��ʮ��������numת��Ϊ���������֣�ͬʱ�����������ְ�λ��ֵ��variable����
void TruthTable::SetVariablesValue(int num)
{
	int cnt = variableNumber;
	// ��Ϊcnt��������ֵ������cnt��
	while (cnt)
	{
		variables[cnt - 1].value = num % 2; // ��ת����Ķ��������ְ�λ�ѱ����� �Ӻ���ǰ ��ֵ
		num /= 2;
		cnt--;
	}
}

// ���ȫ�������ͱ��ʽ����
void TruthTable::PrintVariablesName()const
{
	FOR(i, 0, variableNumber)
		cout << setiosflags(ios::right) << setw(3) << variables[i].name;  // �����������
	cout << "  " << expression << endl << endl;                           // ������ʽ����
}

// ���ȫ�������ͱ��ʽ��ֵ
void TruthTable::PrintVariablesValue()
{
	FOR(i, 0, variableNumber)
		cout << setiosflags(ios::right) << setw(3) << variables[i].value;  // ���������ֵ
	cout << "  " << CalculateExpressionValue() << endl << endl;            // ������ʽ��ֵ
}

// ����ʽexpression�е��������ת��Ϊ���Ӧ��ֵ������ĸ�������֣�����׺���ʽ
// ����!a & b (a=0,b=1) ת��Ϊ !0 & 1
string TruthTable::AlphaToNum()
{
	string ret = expression;
	FOR(i, 0, expression.length())
	{
		// ����ǰ�ַ�Ϊ��ĸ������Ϊ����������ת��Ϊ�����ַ�
		if (isalpha(expression[i]))
		{
			FOR(j, 0, variableNumber)
			{
				// ��cnt���ַ����ҵ���Ӧ�����ĸ�ֵ
				if (variables[j].name == expression[i])
				{
					ret[i] = variables[j].value + '0';
					break;
				}
			}
		}
	}
	return ret;
}

// �Ƚ���������ȼ���˳��Ϊ ( ) ! & | ^ ~ ������ �� ��ȡ ��ȡ �̺� ��ֵ
// ����ֵ-1Ϊ a < b
// ����ֵ 1Ϊ a >= b
// ����ֵ 0Ϊ����������������η���Ϊ���������η񶨲���
int CompareOperator(const char a, const char b)
{
	if (a == '!')
	{
		if (b == '(') return -1;
		else if (b == '!') return 0;
		else return 1;
	}
	else if (a == '&')
	{
		if ((b == '(' || b == '!')) return -1;
		else return 1;
	}
	else if (a == '|')
	{
		if ((b == '&' || b == '(' || b == '!')) return -1;
		else return 1;
	}
	else if (a == '^')
	{
		if ((b == '&' || b == '(' || b == '|' || b == '!')) return -1;
		else return 1;
	}
	else if (a == '~')
	{
		if ((b == '~' || b == ')')) return 1;
		else return -1;
	}
	else if (a == '(')  return -1;
}

//  &    |     ^    ~
// ��ȡ ��ȡ �̺� ��ֵ ��������
bool CalcuateValue(const bool a, const char c, const bool  b) 
{
	if (c == '&') return a & b;    // ��ȡ 
	if (c == '|') return a | b;    // ��ȡ
	if (c == '^') return (!a) | b; // �̺�
	if (c == '~') return a == b;   // ��ֵ
}

// ���㵱ǰ�����������ֵ����µı��ʽ��ֵ
bool TruthTable::CalculateExpressionValue()
{
	bool stack1[33];        // ������ֵ�ջ
	char stack2[33];        // ����������ջ 
	int top1 = 0, top2 = 0; // ջ��
	string s = AlphaToNum();// ����ĸ����ת��Ϊ���ֺ�Ĺ�ʽ

	// ģ�⽫���ʽ��������ţ����жϽ�����־
	s += ')';
	stack2[top2++] = '(';
	FOR(i, 0, s.length())
	{
		// ���ʽ��λ��Ϊ0/1��ֱ����ջ
		if (isdigit(s[i])) stack1[top1++] = s[i] - '0';

		// ���ʽ��λ��Ϊ�����
		else
		{
			// ����������ֱ����ջ
			if (s[i] == '(') stack2[top2++] = s[i];

			// �����������򵯳�ջ����������������㣬ֱ������������Ϊֹ
			else if (s[i] == ')')
			{
				// ջΪ�գ���ֱ�ӽ�����һ��ѭ�������ؽ���������ƥ��
				if (!top2) continue;

				// ����ջ�������ֱ��ƥ�䵽������
				while (stack2[top2 - 1] != '(')
				{
					// !�ǵ�Ԫ���������Ҫ����
					if (stack2[top2 - 1] == '!')
					{
						// ȡ��ջ��Ԫ�ؽ���ȡ�������Ż���ջ
						bool a = stack1[--top1];
						if (a == 1) stack1[top1++] = 0;
						else stack1[top1++] = 1;

						// ����ջ����!����
						top2--, i--;
					}

					// �����Ԫ���������
					else
					{
						// ȡbΪջ����aΪջ�ζ�Ԫ�أ����ж�Ԫ����
						bool b = stack1[--top1];
						bool a = stack1[--top1];
						stack1[top1++] = CalcuateValue(a, stack2[--top2], b);
					}
				}
				top2--; // �����ų�ջ
			}

			else if (CompareOperator(stack2[top2 - 1], s[i]) == -1) stack2[top2++] = s[i];// ջ��Ԫ�����ȼ�С�ڵ�ǰԪ�أ���ǰԪ����ջ
			else if (CompareOperator(stack2[top2 - 1], s[i]) == 0) top2--;                // ����������������������֣�ֱ�ӳ�ջ
			else if (CompareOperator(stack2[top2 - 1], s[i]) == 1)                        // ջ��Ԫ�����ȼ����ڵ�ǰԪ�أ���ջ
			{
				// ���������⴦��
				if (stack2[top2 - 1] == '!')
				{
					bool a = stack1[--top1];
					if (a == 1) stack1[top1++] = 0;
					else stack1[top1++] = 1;
					top2--, i--;
				}
				// ������Ԫ���������
				else
				{
					bool b = stack1[--top1];
					bool a = stack1[--top1];
					stack1[top1++] = CalcuateValue(a, stack2[--top2], b);
					stack2[top2++] = s[i];
				}
			}
		}
	}
	// ������ջ�н�����һ�����֣�������������
	return stack1[top1 - 1];
}

// ������Titleչʾ
void PrintMenu ()
{
	printf("***************************************\n");
	printf("**                                   **\n");
	printf("**         ��ӭ�����߼��������      **\n");
	printf("**   (��������ֵ��,����ʽ,֧������)  **\n");
	printf("**                                   **\n");
	printf("**              ��!��ʾ��            **\n");
	printf("**              ��&��ʾ��            **\n");
	printf("**              ��|��ʾ��            **\n");
	printf("**             ��^��ʾ�̺�           **\n");
	printf("**             ��~��ʾ��ֵ           **\n");
	printf("**                                   **\n");
	printf("***************************************\n\n");
	printf("������һ���Ϸ������⹫ʽ�������Ԫ���ƴ�Сд���У���ʹ��Ӣ�����ţ�:\n");

}

int main()
{
	// ������titleչʾ
	PrintMenu();

	// �������⹫ʽ
	string expression;
	cin >> expression;

	// ������ֵ�����
	TruthTable truthTable(expression);

	// �����ֵ��
	printf("\n�����ֵ������:\n \n");
	truthTable.PrintTruthTable();

	// �������ʽ
	truthTable.PrintPrincipalNormForms();

	return 0;
}