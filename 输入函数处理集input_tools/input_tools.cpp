// 2053385 ������ //
#include <iostream>
#include <cstring>
#include "input_tools.h"
using namespace std;

// �õ�һ��[ minNum��maxNum ]�����֣������������������֤��׳��
int getint(const int minNum, const int maxNum, const string errorTips)
{
    int retNum = INT_MIN;
    while (1)
    {
        cin >> retNum;
        if (cin.fail() || retNum < minNum || retNum > maxNum) // ������������Ͳ�ͬ�����ֲ���Ҫ��Χ��
        {
            cin.clear();
            cin.ignore(1024, '\n');                           // ���������
            cout << errorTips;                                // ���������������ʾ
            continue;
        }
        break;
    }
    return retNum;
}