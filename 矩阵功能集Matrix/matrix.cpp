// 2053385 ������ //
#include <iostream>
#include <cstring>
#include <iomanip>
#include "matrix.h"
#include "input_tools.h"
using namespace std;
/* ����Matrix����ʵ�� */

// Ĭ�Ϲ��캯�������ݸ�����������Ϊ��ά���鿪�ٿռ䣬ͬʱ��ʼ��Ϊ0
Matrix::Matrix(const int n, const int m) :row(n), column(m)
{
    nearArray = new int* [row];                         // Ϊ��ά����ָ������һά�ռ�

    FOR(i, 0, row)
    {
        nearArray[i] = new int[column];                 // Ϊÿ��һά���鿪�ٿռ�
        memset(nearArray[i], 0, sizeof(int) * column);  // �����ʼֵ��Ϊ0
    }
}

// ���ƹ��캯��
Matrix::Matrix(const Matrix& currentMatrix)
{
    if (currentMatrix.nearArray == nearArray) return;   // ���ƶ���Ϊ����

    row = currentMatrix.row;                            // ���и���
    column = currentMatrix.column;

    nearArray = new int* [row];                         // ����ռ䣬���
    FOR(i, 0, row)
        nearArray[i] = new int[column];

    FOR(i, 0, row)                                      // �ڲ���Ϣ����
        FOR(j, 0, column)
        nearArray[i][j] = currentMatrix.nearArray[i][j];
}

// ��ֵ���캯��
Matrix& Matrix::operator=(const Matrix& currentMatrix)
{
    if (currentMatrix.nearArray == nearArray) return *this;

    // �ڸ�ֵǰ�Ƚ�ԭ���Ŀռ��ͷţ����ⷢ���ڴ涪ʧ����
    FOR(i, 0, row)
        delete[] nearArray[i];

    delete[] nearArray;

    row = currentMatrix.row;                                // ���и�ֵ
    column = currentMatrix.column;

    nearArray = new int* [row];                             // �ռ�����
    FOR(i, 0, row)
        nearArray[i] = new int[column];


    FOR(i, 0, row)
        FOR(j, 0, column)
        nearArray[i][j] = currentMatrix.nearArray[i][j];// �ڲ���Ϣ����

    return *this;
}

// ��������
Matrix::~Matrix()
{
    // �ͷ�����Ŀռ䣬���ⷢ���ڴ涪ʧ����
    FOR(i, 0, row)
        delete[] nearArray[i];

    delete[] nearArray;
}

// ���ó�ʼ��Ϣ
void Matrix::SetMatrix()
{
    cout << endl << "���������" << endl;
    FOR(i, 0, row)
    {
        cout << endl << "����������" << i << "��(�Կո�ָ�)��" << endl;
        FOR(j, 0, column)
        {
            string errorTips = "��";
            errorTips += char(i + '0');
            errorTips += "��";
            errorTips += char(j + '0');
            errorTips += "�����������Ӵ˴���ʼ�������뱾��Ԫ��:";
            errorTips += '\n';// �õ���ǰ����Ԫ����������Ӧ��ʾ
            FOR(k, 0, j)
            {
                errorTips += char(nearArray[i][k] + '0');
                errorTips += ' ';
            }
            nearArray[i][j] = getint(INT_MIN, INT_MAX, errorTips);        // ��ϵ�����е�ֵΪ0/1��ͨ������getint�Զ��庯����������
        }
    }
    cout << endl << "���ý�������ǰ����Ϊ��" << endl;
    this->PrintMatrix();
}

// ���������Ϣ
void Matrix::PrintMatrix()
{
    FOR(i, 0, row)
    {
        FOR(j, 0, column)
            cout << setiosflags(ios::left) << setw(2) << nearArray[i][j];
        cout << endl;
    }
}




/* ������Relation����ʵ�� */

// ���ƹ��캯��
RelationMatrix::RelationMatrix(const RelationMatrix& currentMatrix) :Matrix(currentMatrix)
{
    vertexNumber = currentMatrix.vertexNumber;    // ����������ƣ�������Ա��ͨ�����ิ��
}

// ��ֵ���캯��
RelationMatrix& RelationMatrix::operator=(const RelationMatrix& currentMatrix)
{
    Matrix::operator=(currentMatrix);             // ������ʾ���û��ำֵ���캯��������������Ա

    vertexNumber = currentMatrix.vertexNumber;    // ����������ƣ�������Ա��ͨ�����ิ��

    return *this;
}

// ���ó�ʼ��Ϣ
void RelationMatrix::SetMatrix()
{
    cout << endl << "�������ϵ����" << endl;
    FOR(i, 0, vertexNumber)
    {
        cout << endl << "����������" << i << "��(�Կո�ָ�)��" << endl;
        FOR(j, 0, vertexNumber)
        {
            string errorTips = "��";
            errorTips += char(i + '0');
            errorTips += "��";
            errorTips += char(j + '0');
            errorTips += "�����������Ӵ˴���ʼ�������뱾��Ԫ��:";
            errorTips += '\n';// �õ���ǰ����Ԫ����������Ӧ��ʾ
            FOR(k, 0, j)
            {
                errorTips += char(nearArray[i][k] + '0');
                errorTips += ' ';
            }
            nearArray[i][j] = getint(0, 1, errorTips);        // ��ϵ�����е�ֵΪ0/1��ͨ������getint�Զ��庯����������
        }
    }
    cout << endl << "���ý�������ǰ����Ϊ��" << endl;
    this->PrintMatrix();
}
// ���Է��հ�
RelationMatrix RelationMatrix::ReflexiveClosure()
{
    RelationMatrix ret = *this;

    FOR(i, 0, vertexNumber)
        ret.nearArray[i][i] = 1;    // ���Է��հ�������ϵ����Խ�����Ϊ1

    return ret;
}

// ��ԳƱհ�
RelationMatrix RelationMatrix::SymmetricClosure()
{
    RelationMatrix ret = *this;

    FOR(i, 0, vertexNumber)
        FOR(j, 0, vertexNumber)
        ret.nearArray[i][j] = ret.nearArray[i][j] | ret.nearArray[j][i];// ��ԳƱհ�������ϵ�������ת�þ������߼�������

    return ret;
}

// �󴫵ݱհ�( �����㷨���Ӷ�O��n^4��������ʵ����Warshall�㷨 O��n^3���󴫵ݱհ� )
RelationMatrix RelationMatrix::TransitiveClosure()
{
    RelationMatrix ret = *this;
    RelationMatrix currentDegree = *this;          // ��¼��ǰ��ϵ����R��x�η�

    FOR(k, 0, vertexNumber)
    {
        FOR(i, 0, vertexNumber)
            FOR(j, 0, vertexNumber)
            ret.nearArray[i][j] = ret.nearArray[i][j] | currentDegree.nearArray[i][j];// ret = ret + R^k ,���� + Ϊ�߼���

        currentDegree = currentDegree * (*this);   // currentDegree =  currentDegree * R ,��¼Ϊ R^k ������ * ����Ϊ�ϳɲ���
    }
    return ret;
}

// ����*�������ʵ�ֹ�ϵ����ϳ�����
RelationMatrix RelationMatrix::operator*(const RelationMatrix& otherMatrix)
{
    RelationMatrix ret(vertexNumber);

    FOR(i, 0, vertexNumber)
        FOR(j, 0, vertexNumber)
        FOR(k, 0, vertexNumber)
        ret.nearArray[i][j] = ret.nearArray[i][j] | nearArray[i][k] & otherMatrix.nearArray[k][j];

    return ret;
}

// Warshall�㷨O��n^3���󴫵ݱհ�
RelationMatrix RelationMatrix::Warshall()
{
    RelationMatrix ret = *this;

    FOR(j, 0, vertexNumber)             // ��j��
        FOR(i, 0, vertexNumber)         // ��i��
        if (ret.nearArray[i][j])    // ����j�е�i��Ԫ��Ϊ��
        {
            FOR(k, 0, vertexNumber) // ʹ������k��[0,vertexNumber)�ϣ������������
                ret.nearArray[i][k] = ret.nearArray[i][k] | ret.nearArray[j][k];
        }

    return ret;
}