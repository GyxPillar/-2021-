// 2053385 ������ //
#include <iostream>
#include <cstring>
#include <iomanip>
#include "matrix.h"
#include "input_tools.h"
using namespace std;

int main()
{
    // �õ���ϵ���󶥵������ͨ��getint������֤�˽�׳��
    cout << "�������ϵ���󶥵����(0,1000): ";
    int vertexNumber;
    vertexNumber = getint(1, 999, "������������������������:");

    // ���ù�ϵ�����ڲ���Ϣ��ͨ��SetMatrix������֤�˽�׳��
    RelationMatrix m(vertexNumber);
    m.SetMatrix();

    // ͨ��Warshall�㷨�󴫵ݱհ������
    RelationMatrix m1 = m.Warshall();
    cout << endl << "���ݱհ���Ӧ�Ĺ�ϵ����Ϊ:" << endl;
    m1.PrintMatrix();

    return 0;
}