// 2053385 ������ //
#include <iostream>
#include <iomanip>
#include "input_tools.h"

#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FOR(j,a,b) for(int j=a;j<b;j++)
#define FOR(k,a,b) for(int k=a;k<b;k++)
using namespace std;

// ���������ڵ�
struct HuffmanTreeNode 
{
	string coding = "";   // ����������
	int weight = 0;       // ��Ȩֵ
	HuffmanTreeNode* leftChild = NULL, * rightChild = NULL, * parent = NULL;    // �������������ڵ��ʼ����Ϊ��
	bool operator<(const HuffmanTreeNode& x) { return weight < x.weight; }      // ����С�ںţ���������
	bool operator>(const HuffmanTreeNode& x) { return weight > x.weight; }      // ���ش��ںţ���������

	// ���ؼӺ�
	HuffmanTreeNode operator+(const HuffmanTreeNode& x)
	{
		HuffmanTreeNode ret;
		ret.weight = weight + x.weight;
		return ret;
	}
};

class HuffmanTree
{
public:
	// ���캯��
	HuffmanTree(const int n = 0) :nodeNumber(n) { root = new HuffmanTreeNode; };

	// �����������������ٺ������ͷſռ�
	~HuffmanTree() { DeleteTree(root); }

	// ������������
	void BuildHuffmanTree(const int w[]);	
	
	// �ϲ�hft1 hft2�������洢���½ڵ�parent���Ե�ַ��ʽ����
	void MergeTree(HuffmanTreeNode& hft1, HuffmanTreeNode& hft2, HuffmanTreeNode*& parent);

	// ������currentΪ��ַ�ڵ������
	void DeleteTree(HuffmanTreeNode* current);

	// ���ظ��ڵ��ַ
	HuffmanTreeNode* Root() { return root; }

	// ���ɹ����������
	void GenerateHuffmanTable(HuffmanTreeNode* current);

	// ��������������
	void PrintHuffmanTable(HuffmanTreeNode* current);

	// ����������
	friend void QuickSort(HuffmanTreeNode a[], int l, int r);

private:
	HuffmanTreeNode* root = NULL; // ���ڵ�
	int nodeNumber = 0;           // Ҷ�ڵ���Ŀ
};

// �Ż����������
void QuickSort(HuffmanTreeNode a[], int l, int r)
{
	if (l > r)
		return;
	HuffmanTreeNode mid = a[(l + r) / 2];    // ȡ�м�Ԫ��
	int i = l, j = r;
	while (i < j)
	{
		while (a[i] < mid) i++;              // ������벿�ֱ��м��������
		while (a[j] > mid) j--;              // �����Ұ벿�ֱ��м���С����
		if (i <= j)                          // �����һ�鲻����������������С�Ҵ󣩵���
		{
			swap(a[i], a[j]);                // ����
			i++;
			j--;
		}
	}
	if (l < j) QuickSort(a, l, j);          // �ݹ�������벿��
	if (i < r) QuickSort(a, i, r);          // �ݹ������Ұ벿��
}

// �����������
void HuffmanTree::BuildHuffmanTree(const int w[])
{
	// ���������� 2 * n - 1 ���ڵ㣬������ģ�����
	HuffmanTreeNode* array = new HuffmanTreeNode[2 * nodeNumber];

	// ����ʼ��Ҷ�ӽڵ��������
	FOR(i, 0, nodeNumber)
		array[i].weight = w[i];

	HuffmanTreeNode* ancestor = new HuffmanTreeNode;
	// ��n���ڵ����պϲ�Ϊ1�����ڵ㣬��Ҫn-1�κϲ�
	FOR(i, 0, nodeNumber - 1)
	{
		HuffmanTreeNode* current1 = new HuffmanTreeNode, * current2 = new HuffmanTreeNode, * parent;

		// �Զ���ָ������������򣬱�֤ÿ��ȡ���ĵ���Ȩֵ��С�ĵ�
		QuickSort(array, 2 * i, nodeNumber + i - 1);

		// ȡ����������СԪ�غʹ�СԪ��
		*current1 = array[2 * i], * current2 = array[2 * i + 1];

		// ����СԪ�غʹ�СԪ�غϲ���parent
		MergeTree(*current1, *current2, parent);

		// ���ڵ������
		array[nodeNumber + i] = *parent;

		// �����ڵ�λ�ø���
		root = parent;
	}

	// �ͷ�����ģ�������ʱ����Ŀռ�
	delete[]array;
}

// �ϲ�hf1 hft2���ڵ���parent�ڵ㣬���Ե�ַ��ʽ����
void HuffmanTree::MergeTree(HuffmanTreeNode& hft1, HuffmanTreeNode& hft2, HuffmanTreeNode*& parent)
{
	// ����ռ�
	parent = new HuffmanTreeNode;
	
	// ��������λ������
	parent->leftChild = &hft1, parent->rightChild = &hft2;

	// Ȩ������
	parent->weight = hft1.weight + hft2.weight;
	
	// �����������ڵ�λ������
	hft1.parent = parent, hft2.parent = parent;

}

// ������current��ַΪ�������Ŀռ�
void HuffmanTree::DeleteTree(HuffmanTreeNode* current)
{
	// ����λ�÷���
	if (current == NULL) return;
	
	// �ݹ������ͷſռ�
	DeleteTree(current->leftChild), DeleteTree(current->rightChild);
	
	// �ͷŵ�ǰ�ڵ�Ŀռ�
	delete current;
}

// ���ɹ����������
void HuffmanTree::GenerateHuffmanTable(HuffmanTreeNode* current)
{
	// �Ѿ�������Ҷ�ڵ�֮�£��򷵻�
	if (current == NULL) return;

	// ����ǰ�ڵ㲻��Ҷ�ڵ㣬���������������Ĺ���������
	if (current->leftChild != NULL)
		(current->leftChild)->coding = current->coding + '0';  // �����������ڸ��ڵ�����Ϻ�׺+0
	if (current->rightChild != NULL)
		(current->rightChild)->coding = current->coding + '1'; // �����������ڸ��ڵ�����Ϻ�׺+1

	// ���±���
	GenerateHuffmanTable(current->leftChild);
	GenerateHuffmanTable(current->rightChild);
}

// ��������������
void HuffmanTree::PrintHuffmanTable(HuffmanTreeNode* current)
{
	// �Ѿ�������Ҷ�ڵ�֮�£��򷵻�
	if (current == NULL) return;

	// ����ǰ�ڵ���Ҷ�ڵ㣬�����Ȩ�غ͹���������
	if (current->leftChild == NULL && current->rightChild == NULL)
		cout << setiosflags(ios::left) << setw(6) << current->weight << "��  " << current->coding << endl;

	// ���±���
	PrintHuffmanTable(current->leftChild);
	PrintHuffmanTable(current->rightChild);
}
string to_string(int num)
{
	if (num == 0)
		return " 0 ";

	string str = "";
	int num_ = num > 0 ? num : -1 * num;

	while (num_)
	{
		str = (char)(num_ % 10 + 48) + str;
		num_ /= 10;
	}

	if (num < 0)
		str = " - " + str;

	return str;
}
int main()
{
	// ����ڵ������ͨ��getint��֤��׳��
	int nodeNumber = 0;
	cout << "������Ҷ�ڵ������";
	nodeNumber = getint(1, 100000, "�ڵ��������������������룺");

	// ��������ڵ��Ȩֵ��ͨ��geint��֤��׳��
	int* f = new int[nodeNumber];
	cout << "����������Ҷ�ڵ�Ȩֵ��" << endl;
	FOR(i, 0, nodeNumber)
	{
		string errorTips = "��";
		errorTips += char(i + '0');
		errorTips += "���ڵ�Ȩֵ���������Ӵ��������룺";
		errorTips += '\n';
		FOR(j, 0, i)
		{
			errorTips += to_string(f[j]);
			errorTips += " ";
		}
		f[i] = getint(1, INT_MAX, errorTips);
	}


	// ������������
	HuffmanTree huffmanTree(nodeNumber);
	huffmanTree.BuildHuffmanTree(f);

	// ���ɹ����������
	huffmanTree.GenerateHuffmanTable(huffmanTree.Root());

	// ��������������
	cout << "���ɵ�Ҷ�ӽڵ�������������£�" << endl;
	huffmanTree.PrintHuffmanTable(huffmanTree.Root());

	return 0;
}