// 2053385 ������ //
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FOR(j,a,b) for(int j=a;j<b;j++)
#define FOR(k,a,b) for(int k=a;k<b;k++)

#include <iostream>
#include "input_tools.h"
using namespace std;

// �ڽ����� ��
struct Edge
{
	int src = -1;          // ��ʼ����  
	int dst = -1;          // Ŀ������
	int value = 0;         // �߳���Ȩ��
	bool operator<(const Edge& other) { return value < other.value; };// ����С�ڱȽ������
	bool operator>(const Edge& other) { return value > other.value; };// ���ش��ڱȽ������
};

// �ڽ����� ��
struct Vertex
{
	int ancestor;          // ��¼�ڲ��鼯�е�����
};

// �ڽ�����
struct GraphList
{
	// ���캯��
	GraphList(int n = 0, int m = 0);

	// ��������
	~GraphList();

	// ����ͼ
	void SetGraphList();
	 
	// ���鼯Ѱ���ڵ�
	int FindAncestor(int i);

	// Kruskal�㷨�����С������
	void Kruskal();

	int vertexNumber = 0, edgeNumber = 0; // ��¼������������
	Edge* edges = NULL;                   // ��������
	Vertex* vertexs = NULL;               // ������
};

// ���캯��
GraphList::GraphList(int n, int m)
{
	// Ϊ��������������ֵ
	vertexNumber = n, edgeNumber = m;

	// Ϊ�������顢�����鿪�ٿռ�
	vertexs = new Vertex[n + 1], edges = new Edge[m + 1];
}

// ��������
GraphList::~GraphList()
{
	// �ֱ��ͷű�����Ͷ��������ڴ棬�����ڴ�й¶
	delete[]edges;
	delete[]vertexs;
}

// ��ͼ���������ݼ����������ö�������ͱ�������Ϣ
void GraphList::SetGraphList()
{
	// ����߼���Ϣ��ͨ��getint���������˴������룬��֤�˽�׳��
	cout << "����������" << edgeNumber << "���ߵ���㡢�յ㣨��Ŵ�1��ʼ����Ȩ�أ�" << endl;

	FOR(i, 1, edgeNumber + 1)
	{
		string errorTips = "��";
		errorTips += char(i + '0');
		errorTips += "����������������Ӵ˴���ʼ�������뱾��Ԫ�أ�";
		errorTips += '\n';                                         // �õ���ǰ�� ��� ��������Ӧ��ʾ
		edges[i].src = getint(1, vertexNumber, errorTips);

		errorTips = "";
		errorTips += "��";
		errorTips += char(i + '0');
		errorTips += "�����յ����������Ӵ˴���ʼ�������뱾��Ԫ�أ�";
		errorTips += '\n';                                         
		errorTips += char(edges[i].src + '0');
		errorTips += ' ';                                          // �õ���ǰ�� �յ� ��������Ӧ��ʾ
		edges[i].dst = getint(1, vertexNumber, errorTips);

		errorTips = "";
		errorTips += "��";
		errorTips += char(i + '0');
		errorTips += "����Ȩֵ���������Ӵ˴���ʼ�������뱾��Ԫ�أ�";
		errorTips += '\n';
		errorTips += char(edges[i].src + '0');
		errorTips += ' ';                                          
		errorTips += char(edges[i].dst + '0');
		errorTips += ' ';                                          // �õ���ǰ�� Ȩֵ ��������Ӧ��ʾ
		edges[i].value = getint(1, INT_MAX, errorTips);

	}

	FOR(i, 1, vertexNumber + 1)
		vertexs[i].ancestor = i;   // ���鼯��ʼ��
}

// ���鼯Ѱ���ڵ㣬���ü��仯����
int GraphList::FindAncestor(int i)
{
	if (i == vertexs[i].ancestor) return i;
	return vertexs[i].ancestor = FindAncestor(vertexs[i].ancestor);
}

// ��ģ��ʵ���Ż���Ŀ���������������Ϊ[l,r]
template<typename T>void QuickSort(T a[],int l,int r)
{
	if (l > r)
		return;
	T mid = a[(l + r) / 2];      // ȡ�м�Ԫ��
	int i = l, j = r;
	while (i < j)
	{
		while (a[i] < mid) i++;  // ������벿�ֱ��м��������
		while (a[j] > mid) j--;  // �����Ұ벿�ֱ��м���С����
		if (i <= j)              // �����һ�鲻����������������С�Ҵ󣩵���
		{
			swap(a[i], a[j]);    // ����
			i++;
			j--;
		}
	}
	if (l < j) QuickSort(a, l, j);// �ݹ�������벿��
	if (i < r) QuickSort(a, i, r);// �ݹ������Ұ벿��
}

// ʵ��Kruskal̰���㷨������С������
void GraphList::Kruskal()
{
	// ������������[1,edgeNumber]
	QuickSort(edges, 1, edgeNumber);

	// ans��¼��С��������Ȩ֮�ͣ�cnt��¼��ѡ������
	int ans = 0, cnt = 0;
	FOR(i, 1, edgeNumber + 1)
	{
		int f1 = FindAncestor(edges[i].src); // f1Ϊ����������
		int f2 = FindAncestor(edges[i].dst); // f2Ϊ���յ������

		// ���������Ȳ�ͬ���������ͬ����ͨ��֧����Ҫ�ϲ������˱߼�����С������
		if (f1 != f2)
		{
			cnt++;                                     // ��ѡ����+1
			ans += edges[i].value;     // ���ı�Ȩ֮�͸���
			vertexs[f1].ancestor = f2; // f1����������Ϊf2����������ͬһ����ͨ��֧
			cout << "ѡ�����Ϊ" << edges[i].src << " �յ�Ϊ" << edges[i].dst << " ȨֵΪ" << edges[i].value << " �ı�" << endl;
		}
		if (cnt == vertexNumber - 1)                   // ����С����������ѡ����=������-1ʱ����С�������������
		{
			cout << "��С��������С��Ȩ��Ϊ��" << ans << endl;
			return;
		}
	}
	// ��δ��ѡ��vertexNumber-1���ߣ����ܹ�����С������
	cout << "���ϵı߲��ܹ�����С������" << endl;
}

int main()
{
	// ���붥���������������ͨ��getint������֤��׳��
	int vertexNumber, edgeNumber;
	cout << "�����붥����������������";
	vertexNumber = getint(1, 5000, "������������������������붥�������ͱ�������");
	edgeNumber = getint(0, 5000, "����������������������������:");

	// �����ڽӱ�
	GraphList MinSpanningTree(vertexNumber, edgeNumber);

	// �����������Ϣ���й�ͼ
	MinSpanningTree.SetGraphList();
	
	// ��Kruskal̰���㷨������С������
	MinSpanningTree.Kruskal();

	return 0;
}

