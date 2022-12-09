#pragma once
// 2053385 ������ //
#ifndef MATRIX_H_
#define MATRIX_H_

#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FOR(j,a,b) for(int j=a;j<b;j++)
#define FOR(k,a,b) for(int k=a;k<b;k++)

// ���� ����
class Matrix
{
public:
    // Ĭ�Ϲ��캯��
    Matrix(const int x = 0, const int y = 0);

    // ���ƹ��캯��
    Matrix(const Matrix& currentMatrix);

    // ��ֵ���캯��
    Matrix& operator=(const Matrix& currentMatrix);

    // ��������
    ~Matrix();

    // ���þ����ʼ��Ϣ
    void SetMatrix();

    // ���������Ϣ
    void PrintMatrix();
protected:
    // ���������Ϣ�Ķ�ά����ָ��
    int** nearArray = NULL;
private:
    // ������
    int row = 0;

    // ������
    int column = 0;
};

// ��ϵ���� ������
class RelationMatrix :public Matrix
{
public:
    // Ĭ�Ϲ��캯��
    RelationMatrix(const int n = 0) :Matrix(n, n), vertexNumber(n) {};

    // ���ƹ��캯��
    RelationMatrix(const RelationMatrix& currentMatrix);

    // ��ֵ���캯��
    RelationMatrix& operator=(const RelationMatrix& currentMatrix);

    // ��������     ϵͳ���Զ����û������������ͷ��ڴ棬�ʲ�����д
    ~RelationMatrix() {};

    // ���þ����ʼ��Ϣ
    void SetMatrix();

    // ���Է��հ�
    RelationMatrix ReflexiveClosure();

    // ��ԳƱհ�
    RelationMatrix SymmetricClosure();

    // �󴫵ݱհ�( ���ظ��Ӷ�O��n^4��������ʵ����Warshall�㷨 O��n^3���󴫵ݱհ� )
    RelationMatrix TransitiveClosure();

    // *��������أ�ʵ�ֺϳ�����
    RelationMatrix operator*(const RelationMatrix& otherMatrix);

    // Warshall�㷨�󴫵ݱհ�
    RelationMatrix Warshall();
private:
    // ��������
    int vertexNumber = 0;
};

#endif