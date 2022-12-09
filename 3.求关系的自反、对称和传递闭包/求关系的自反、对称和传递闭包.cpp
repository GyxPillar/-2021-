// 2053385 ������ //
#include <iostream>
#include <cstring>
#include <iomanip>
#include "matrix.h"
#include "input_tools.h"
using namespace std;

// ����˵���ѡ������հ����ͣ�1Ϊ�Է��հ���2Ϊ�ԳƱհ���3Ϊ���ݱհ����ѱ�֤��׳��
const int Menu()
{
    cout << endl << "�������ѡ���Ӧ�㷨��" << endl;
    cout << "1.�Է��հ�" << endl;
    cout << "2.�ԳƱհ�" << endl;
    cout << "3.���ݱհ�" << endl;
    cout << "�����룺";
    int ret = getint(1, 3, "�������������������룺");
    return ret;
}
int main()
{
    // �õ���ϵ���󶥵������ͨ��getint������֤�˽�׳��
    cout << "�������ϵ���󶥵����(0,1000): ";
    int vertexNumber;
    vertexNumber = getint(1, 999, "������������������������:");

    // ���ù�ϵ�����ڲ���Ϣ��ͨ��SetMatrix������֤�˽�׳��
    RelationMatrix m(vertexNumber);
    m.SetMatrix();

    RelationMatrix m1;

    // ����˵�ѡ������հ�
    switch (Menu())
    {
    case 1:
        m1 = m.ReflexiveClosure(); // 1 �Է��հ�
        break;
    case 2:
        m1 = m.SymmetricClosure(); // 2 �ԳƱհ�
        break;
    case 3:
        m1 = m.TransitiveClosure();// 3 ���ݱհ�
        break;
    default:
        cout << "�������д���";
        exit(-1);
    }
    cout << endl << "�����ϵ�հ�Ϊ��" << endl;
    m1.PrintMatrix();

    return 0;
}