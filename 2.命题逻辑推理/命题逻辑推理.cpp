// 2053385 ������ //

#include <iostream>
using namespace std;

int main()
{
	cout << "�������£�" << endl;
	cout << "��1��ӪҵԱA��B͵���ֱ�" << endl;
	cout << "��2����A����������������Ӫҵʱ��" << endl;
	cout << "��3����B�ṩ��֤����ȷ�������δ����" << endl;
	cout << "��4����B�ṩ��֤�ݲ���ȷ��������������Ӫҵʱ��" << endl;
	cout << "��5������������" << endl;

	cout << endl << "�������Ԫ��ʾ���£�" << endl;
	cout << "a : ӪҵԱA͵���ֱ�" << endl;
	cout << "b : ӪҵԱB͵���ֱ�" << endl;
	cout << "c : ��������Ӫҵʱ��" << endl;
	cout << "d : B�ṩ��֤����ȷ" << endl;
	cout << "e : ����δ����" << endl;

	cout << endl << "�����������Ԫ�Ķ�Ӧ��ʾΪ��" << endl;
	cout << "��1��ӪҵԱA��B͵���ֱ�                         ->   a  | b " << endl;
	cout << "��2����A����������������Ӫҵʱ��                ->   a -> c" << endl;
	cout << "��3����B�ṩ��֤����ȷ�������δ����            ->   d -> e" << endl;
	cout << "��4����B�ṩ��֤�ݲ���ȷ��������������Ӫҵʱ��  ->   !d->!c" << endl;
	cout << "��5������������                                 ->   !e" << endl;

	for (int a = 0; a<=1; a++)
		for (int b= 0; b<=1 ;b++)
			for (int c = 0; c<=1 ; c++)
				for (int d = 0; d<=1 ; d++)
					for (int e = 0; e<=1 ; e++)
						if ((a | b) & (!a | c) & (!d | e) & (d | !c) & (!e))  // �ڼ���ʱ��a->bת��Ϊ!a|b
						{
							cout << endl << "a=" << a << "��b=" << b << "ʱ����������ȫ������" << endl;
							cout << "������������";
							a ? cout << "A͵���ֱ�" : cout << "Aû��͵�ֱ�";  // ��a��=0,��A͵���ֱ�����Aû��͵
							cout << "    ";
							b ? cout << "B͵���ֱ�" : cout << "Bû��͵�ֱ�";  // ��b��=0,��B͵���ֱ�����Bû��͵
							cout << endl;
						}

	return 0;

}